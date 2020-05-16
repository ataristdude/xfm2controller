/*
 * XFM2 Synth Controller
 *
 * This is a user-friendly controller for the excellent XFM2 synth hardware designed by Futur3soundz
 * https://www.futur3soundz.com/xfm2
 *
 *
 * This file is part of the XFM2Controller distribution (https://github.com/ataristdude/xfm2controller).
 * Copyright (c) 2020 Don Fletcher
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "SynthModel.h"
#include <QDebug>
#include <string.h>

/*
 * SERIALPORT is the serial port to access.  We assume ttyUSB1 but it
 * will need to be changed to suit your setup.
 *
 * PATCHFILE is a file that holds a list of patch names.  On Linux the default
 * location is /opt/xfm2/bin/patchnames.txt.  On Windows we assume the file
 * is in the current working directory for the application.
 *
 * You will need to edit both of these parameters to suit your own configuration.
 */

#ifdef Q_OS_WIN
#define SERIALPORT "COM4"
#define PATCHFILE ".\\patchnames.txt"
#else
#define SERIALPORT  "ttyUSB1"
#define PATCHFILE "/opt/xfm2/bin/patchnames.txt"
#endif

// Initialise the model
SynthModel::SynthModel(QObject *parent) : QObject(parent)
{
    // Allow for 128 patch names
    m_patchNames.resize(128);
    m_patchnumber=-1;
    m_initialised=false;

    // Set up the serial port
    m_port=new QSerialPort(this);
    m_port->setPortName(SERIALPORT);
    m_port->setBaudRate(500000);
    m_port->setDataBits(QSerialPort::Data8);
    m_port->setStopBits(QSerialPort::StopBits::OneStop);
    m_port->setParity(QSerialPort::Parity::NoParity);

    // See if we can connect and read the initial patch into memory
    m_port->open(QIODevice::ReadWrite);

    m_isconnected=m_port->isOpen();
    if (!m_isconnected) {
        qDebug() << "Cannot open USB0 for read/write";
        m_patchnumber=0;
    } else {
        setPatchNumber(0);
    }

    loadPatchNames();
}

// Returns true if we're connected
bool SynthModel::isConnected() const
{
    return m_isconnected;
}

// Initialize the patch buffer by calling the init synth API
// and then read synth parameters back into memory
bool SynthModel::initPatchBuffer()
{
    if (!m_isconnected) {
        return false;
    }

    char bf[5];

    bf[0]='i';

    m_port->clear();
    m_port->write(bf, 1);
    m_port->flush();

    m_port->waitForReadyRead();
    m_port->read(&bf[0], 1);

    readPatchBuffer();

    m_patchNameBuffer="Untitled";
    emit patchNumberChanged();

    return true;
}

// Read the synth parameters
bool SynthModel::readPatchBuffer()
{
    if (!m_isconnected) {
        return false;
    }

    if (!m_port->isOpen()) {
        m_initialised=true;
        return false;
    }

    m_port->clear();
    m_port->write("d", 1);
    m_port->flush();

    qint64 bytesread=0;

    while (bytesread < 512) {
        m_port->waitForReadyRead();

        qint64 avail=m_port->bytesAvailable();

        if (bytesread+avail > 512) {
            avail=512-bytesread;
        }

        m_port->read(reinterpret_cast<char *>(&m_xfm2[bytesread]), avail);
        bytesread+=avail;
    }

    qDebug() << "read patch buffer (" << m_patchnumber<< ")";
    m_initialised=true;
    return true;
}

// Get the current patch number
int SynthModel::patchNumber() const
{
    return m_patchnumber;
}

// Set the current patch number and read it into memory
void SynthModel::setPatchNumber(int p)
{
    if (p != m_patchnumber) {
        if (p < 0) p=0;
        if (p > 127) p=127;

        m_patchnumber=p;
        m_patchNameBuffer=m_patchNames[m_patchnumber];

        if (m_isconnected) {
            char bf[5];

            bf[0]='r';
            bf[1]=static_cast<char>(p);

            m_port->clear();
            m_port->write(bf, 2);
            m_port->flush();

            m_port->waitForReadyRead();
            m_port->read(&bf[0], 1);

            readPatchBuffer();
        }

        emit patchNumberChanged();
    }
}

// Reload the current patch
bool SynthModel::reloadPatch()
{
    m_patchNameBuffer=m_patchNames[m_patchnumber];

    if (m_isconnected) {
        char bf[5];

        bf[0]='r';
        bf[1]=static_cast<char>(m_patchnumber);

        m_port->clear();
        m_port->write(bf, 2);
        m_port->flush();

        m_port->waitForReadyRead();
        m_port->read(&bf[0], 1);

        readPatchBuffer();
    }

    emit patchNumberChanged();
    return true;
}

// Write the current patch buffer.  This
// saves the current memory to a patch for later recall.
// Assumption is that the synth is already synchronised
// with the buffer we have in memory
bool SynthModel::writePatchBuffer(int toPatch/*=-1*/)
{
    if (toPatch >= 0) {
        if (toPatch > 127) {
            return false;
        }

        m_patchnumber=toPatch;
    }

    if (!m_isconnected) {
        if (toPatch >= 0) {
            emit patchNumberChanged();
        }
        return true;
    }

    char bf[5];

    bf[0]='w';
    bf[1]=static_cast<char>(m_patchnumber);
    m_port->clear();
    m_port->write(bf, 2);
    m_port->waitForBytesWritten();

    m_port->waitForReadyRead();
    m_port->read(&bf[0], 1);

    m_patchNames[m_patchnumber]=m_patchNameBuffer;
    savePatchNames();

    readPatchBuffer();

    if (toPatch >= 0) {
        emit patchNumberChanged();
    }

    return true;
}

// Read a single parameter.
// The useCache argument determines if the synth should be queried.  If set to true then
// the parameter will be read from our memory buffer without accessing the hardware.
// If false then the synth is read first so we get the current parameter value directly from
// the hardware.
unsigned char SynthModel::readMemoryLocation(XFM2Parameter offset, bool useCache/*=true*/)
{
    if ((!useCache || !m_initialised) && m_isconnected) {
        unsigned char bf[5];

        m_port->clear();

        bf[0]='g';
        if (offset < 256) {
            bf[1]=static_cast<unsigned char>(offset);
            m_port->write(reinterpret_cast<char *>(bf), 2);
            m_port->waitForBytesWritten();
        } else {
            bf[1]=0xff;
            bf[2]=static_cast<unsigned char>(offset-256);
            m_port->write(reinterpret_cast<char *>(bf), 3);
            m_port->waitForBytesWritten();
        }

        m_port->waitForReadyRead();
        m_port->read(reinterpret_cast<char *>(&bf[0]), 1);
        m_xfm2[offset]=bf[0];
    }

    return m_xfm2[offset];
}

// Write a single parameter.
// The model implements a write-through cache.  Parameters are always written
// directly to the synth but also copied into our memory buffer.
// However a parameter is only written if it is different to the copy in memory, for faster performance.
bool SynthModel::writeMemoryLocation(XFM2Parameter offset, unsigned char data)
{
    if (data == m_xfm2[offset]) {
        return true;
    }

    m_xfm2[offset]=data;

    if (!m_isconnected || !m_initialised) {
        return true;
    }

    unsigned char bf[5];

    m_port->clear();

    bf[0]='s';
    if (offset < 256) {
        bf[1]=static_cast<unsigned char>(offset);
        bf[2]=data;
        m_port->write(reinterpret_cast<char *>(bf), 3);
        m_port->waitForBytesWritten();
    } else {
        bf[1]=0xff;
        bf[2]=static_cast<unsigned char>(offset-256);
        bf[3]=data;
        m_port->write(reinterpret_cast<char *>(bf), 4);
        m_port->waitForBytesWritten();
    }

    return true;
}

int SynthModel::operatorSync()
{
    return static_cast<int>(readMemoryLocation(OP_SYNC));
}

void SynthModel::setOperatorSync(int v)
{
    unsigned char vv=static_cast<unsigned char>(v);
    if (vv != readMemoryLocation(OP_SYNC)) {
        writeMemoryLocation(OP_SYNC, vv);
        emit operatorSyncChanged();
    }
}

int SynthModel::operatorMode()
{
    return static_cast<int>(readMemoryLocation(OP_MODE));
}

void SynthModel::setOperatorMode(int v)
{
    unsigned char vv=static_cast<unsigned char>(v);
    if (vv != readMemoryLocation(OP_MODE)) {
        writeMemoryLocation(OP_MODE, vv);
        emit operatorModeChanged();
    }
}

int SynthModel::pitchEG_L0()
{
    return static_cast<int>(readMemoryLocation(PITCH_EG_L0));
}

void SynthModel::setPitchEG_L0(int v)
{
    unsigned char vv=static_cast<unsigned char>(v);
    if (vv != readMemoryLocation(PITCH_EG_L0)) {
        writeMemoryLocation(PITCH_EG_L0, vv);
        emit pitchEG_L0Changed();
    }
}

int SynthModel::pitchEG_L1()
{
    return static_cast<int>(readMemoryLocation(PITCH_EG_L1));
}

void SynthModel::setPitchEG_L1(int v)
{
    unsigned char vv=static_cast<unsigned char>(v);
    if (vv != readMemoryLocation(PITCH_EG_L1)) {
        writeMemoryLocation(PITCH_EG_L1, vv);
        emit pitchEG_L1Changed();
    }
}

int SynthModel::pitchEG_L2()
{
    return static_cast<int>(readMemoryLocation(PITCH_EG_L2));
}

void SynthModel::setPitchEG_L2(int v)
{
    unsigned char vv=static_cast<unsigned char>(v);
    if (vv != readMemoryLocation(PITCH_EG_L2)) {
        writeMemoryLocation(PITCH_EG_L2, vv);
        emit pitchEG_L2Changed();
    }
}

int SynthModel::pitchEG_L3()
{
    return static_cast<int>(readMemoryLocation(PITCH_EG_L3));
}

void SynthModel::setPitchEG_L3(int v)
{
    unsigned char vv=static_cast<unsigned char>(v);
    if (vv != readMemoryLocation(PITCH_EG_L3)) {
        writeMemoryLocation(PITCH_EG_L3, vv);
        emit pitchEG_L3Changed();
    }
}

int SynthModel::pitchEG_L4()
{
    return static_cast<int>(readMemoryLocation(PITCH_EG_L4));
}

void SynthModel::setPitchEG_L4(int v)
{
    unsigned char vv=static_cast<unsigned char>(v);
    if (vv != readMemoryLocation(PITCH_EG_L4)) {
        writeMemoryLocation(PITCH_EG_L4, vv);
        emit pitchEG_L4Changed();
    }
}

int SynthModel::pitchEG_L5()
{
    return static_cast<int>(readMemoryLocation(PITCH_EG_L5));
}

void SynthModel::setPitchEG_L5(int v)
{
    unsigned char vv=static_cast<unsigned char>(v);
    if (vv != readMemoryLocation(PITCH_EG_L5)) {
        writeMemoryLocation(PITCH_EG_L5, vv);
        emit pitchEG_L5Changed();
    }
}


int SynthModel::pitchEG_R0()
{
<<<<<<< HEAD
    return static_cast<int>(readMemoryLocation(PITCH_EG_DELAY));
=======
    return static_cast<int>(255-readMemoryLocation(PITCH_EG_DELAY));
>>>>>>> 5f1b6151ec4d2bf472cad1981025fb954064533c
}

void SynthModel::setPitchEG_R0(int v)
{
<<<<<<< HEAD
=======
    v=255-v;
>>>>>>> 5f1b6151ec4d2bf472cad1981025fb954064533c
    unsigned char vv=static_cast<unsigned char>(v);
    if (vv != readMemoryLocation(PITCH_EG_DELAY)) {
        writeMemoryLocation(PITCH_EG_DELAY, vv);
        emit pitchEG_R0Changed();
    }
}

int SynthModel::pitchEG_R1()
{
    return static_cast<int>(255-readMemoryLocation(PITCH_EG_R1));
}

void SynthModel::setPitchEG_R1(int v)
{
    v=255-v;
    unsigned char vv=static_cast<unsigned char>(v);
    if (vv != readMemoryLocation(PITCH_EG_R1)) {
        writeMemoryLocation(PITCH_EG_R1, vv);
        emit pitchEG_R1Changed();
    }
}

int SynthModel::pitchEG_R2()
{
    return static_cast<int>(255-readMemoryLocation(PITCH_EG_R2));
}

void SynthModel::setPitchEG_R2(int v)
{
    v=255-v;
    unsigned char vv=static_cast<unsigned char>(v);
    if (vv != readMemoryLocation(PITCH_EG_R2)) {
        writeMemoryLocation(PITCH_EG_R2, vv);
        emit pitchEG_R2Changed();
    }
}

int SynthModel::pitchEG_R3()
{
    return static_cast<int>(255-readMemoryLocation(PITCH_EG_R3));
}

void SynthModel::setPitchEG_R3(int v)
{
    v=255-v;
    unsigned char vv=static_cast<unsigned char>(v);
    if (vv != readMemoryLocation(PITCH_EG_R3)) {
        writeMemoryLocation(PITCH_EG_R3, vv);
        emit pitchEG_R3Changed();
    }
}

int SynthModel::pitchEG_R4()
{
    return static_cast<int>(255-readMemoryLocation(PITCH_EG_R4));
}

void SynthModel::setPitchEG_R4(int v)
{
    v=255-v;
    unsigned char vv=static_cast<unsigned char>(v);
    if (vv != readMemoryLocation(PITCH_EG_R4)) {
        writeMemoryLocation(PITCH_EG_R4, vv);
        emit pitchEG_R4Changed();
    }
}

int SynthModel::pitchEG_R5()
{
    return static_cast<int>(255-readMemoryLocation(PITCH_EG_R5));
}

void SynthModel::setPitchEG_R5(int v)
{
    v=255-v;
    unsigned char vv=static_cast<unsigned char>(v);
    if (vv != readMemoryLocation(PITCH_EG_R5)) {
        writeMemoryLocation(PITCH_EG_R5, vv);
        emit pitchEG_R5Changed();
    }
}

int SynthModel::pitchEG_Range()
{
    return static_cast<int>(readMemoryLocation(PITCH_EG_RANGE));
}

void SynthModel::setPitchEG_Range(int v)
{
    unsigned char vv=static_cast<unsigned char>(v);
    if (vv != readMemoryLocation(PITCH_EG_RANGE)) {
        writeMemoryLocation(PITCH_EG_RANGE, vv);
        emit pitchEG_RangeChanged();
    }
}

int SynthModel::pitchEG_Velocity()
{
    return static_cast<int>(readMemoryLocation(PITCH_EG_VELO));
}

void SynthModel::setPitchEG_Velocity(int v)
{
    unsigned char vv=static_cast<unsigned char>(v);
    if (vv != readMemoryLocation(PITCH_EG_VELO)) {
        writeMemoryLocation(PITCH_EG_VELO, vv);
        emit pitchEG_VelocityChanged();
    }
}

int SynthModel::pitchEG_RateKey()
{
    return static_cast<int>(readMemoryLocation(PITCH_EG_RATE_KEY));
}

void SynthModel::setPitchEG_RateKey(int v)
{
    unsigned char vv=static_cast<unsigned char>(v);
    if (vv != readMemoryLocation(PITCH_EG_RATE_KEY)) {
        writeMemoryLocation(PITCH_EG_RATE_KEY, vv);
        emit pitchEG_RateKeyChanged();
    }
}

int SynthModel::lfoDepthPitch()
{
    return static_cast<int>(readMemoryLocation(LFO_DEPTH_PITCH));
}

void SynthModel::setLFODepthPitch(int v)
{
    unsigned char vv=static_cast<unsigned char>(v);
    if (vv != readMemoryLocation(LFO_DEPTH_PITCH)) {
        writeMemoryLocation(LFO_DEPTH_PITCH, vv);
        emit lfoDepthPitchChanged();
    }
}

int SynthModel::lfoDepthAmplitude()
{
    return static_cast<int>(readMemoryLocation(LFO_DEPTH_AMP));
}

void SynthModel::setLFODepthAmplitude(int v)
{
    unsigned char vv=static_cast<unsigned char>(v);
    if (vv != readMemoryLocation(LFO_DEPTH_AMP)) {
        writeMemoryLocation(LFO_DEPTH_AMP, vv);
        emit lfoDepthAmplitudeChanged();
    }
}

int SynthModel::lfoSpeed()
{
    return static_cast<int>(readMemoryLocation(LFO_SPEED));
}

void SynthModel::setLFOSpeed(int v)
{
    unsigned char vv=static_cast<unsigned char>(v);
    if (vv != readMemoryLocation(LFO_SPEED)) {
        writeMemoryLocation(LFO_SPEED, vv);
        emit lfoSpeedChanged();
    }
}

int SynthModel::lfoSync()
{
    return static_cast<int>(readMemoryLocation(LFO_SYNC));
}

void SynthModel::setLFOSync(int v)
{
    unsigned char vv=static_cast<unsigned char>(v);
    if (vv != readMemoryLocation(LFO_SYNC)) {
        writeMemoryLocation(LFO_SYNC, vv);
        emit lfoSyncChanged();
    }
}

int SynthModel::lfoWave()
{
    return static_cast<int>(readMemoryLocation(LFO_WAVE));
}

void SynthModel::setLFOWave(int v)
{
    unsigned char vv=static_cast<unsigned char>(v);
    if (vv != readMemoryLocation(LFO_WAVE)) {
        writeMemoryLocation(LFO_WAVE, vv);
        emit lfoWaveChanged();
    }
}

int SynthModel::lfoFade()
{
    return static_cast<int>(readMemoryLocation(LFO_FADE));
}

void SynthModel::setLFOFade(int v)
{
    unsigned char vv=static_cast<unsigned char>(v);
    if (vv != readMemoryLocation(LFO_FADE)) {
        writeMemoryLocation(LFO_FADE, vv);
        emit lfoFadeChanged();
    }
}

int SynthModel::modPitchLFOWheel()
{
    return static_cast<int>(readMemoryLocation(MOD_PITCH_LFO_WHEEL));
}

void SynthModel::setModPitchLFOWheel(int v)
{
    unsigned char vv=static_cast<unsigned char>(v);
    if (vv != readMemoryLocation(MOD_PITCH_LFO_WHEEL)) {
        writeMemoryLocation(MOD_PITCH_LFO_WHEEL, vv);
        emit modPitchLFOWheelChanged();
    }
}

int SynthModel::modPitchLFOBreath()
{
    return static_cast<int>(readMemoryLocation(MOD_PITCH_LFO_BREATH));
}

void SynthModel::setModPitchLFOBreath(int v)
{
    unsigned char vv=static_cast<unsigned char>(v);
    if (vv != readMemoryLocation(MOD_PITCH_LFO_BREATH)) {
        writeMemoryLocation(MOD_PITCH_LFO_BREATH, vv);
        emit modPitchLFOBreathChanged();
    }
}

int SynthModel::modPitchLFOFoot()
{
    return static_cast<int>(readMemoryLocation(MOD_PITCH_LFO_FOOT));
}

void SynthModel::setModPitchLFOFoot(int v)
{
    unsigned char vv=static_cast<unsigned char>(v);
    if (vv != readMemoryLocation(MOD_PITCH_LFO_FOOT)) {
        writeMemoryLocation(MOD_PITCH_LFO_FOOT, vv);
        emit modPitchLFOFootChanged();
    }
}

int SynthModel::modAmpLFOWheel()
{
    return static_cast<int>(readMemoryLocation(MOD_AMP_LFO_WHEEL));
}

void SynthModel::setModAmpLFOWheel(int v)
{
    unsigned char vv=static_cast<unsigned char>(v);
    if (vv != readMemoryLocation(MOD_AMP_LFO_WHEEL)) {
        writeMemoryLocation(MOD_AMP_LFO_WHEEL, vv);
        emit modAmpLFOWheelChanged();
    }
}

int SynthModel::modAmpLFOBreath()
{
    return static_cast<int>(readMemoryLocation(MOD_AMP_LFO_BREATH));
}

void SynthModel::setModAmpLFOBreath(int v)
{
    unsigned char vv=static_cast<unsigned char>(v);
    if (vv != readMemoryLocation(MOD_AMP_LFO_BREATH)) {
        writeMemoryLocation(MOD_AMP_LFO_BREATH, vv);
        emit modAmpLFOBreathChanged();
    }
}

int SynthModel::modAmpLFOFoot()
{
    return static_cast<int>(readMemoryLocation(MOD_AMP_LFO_FOOT));
}

void SynthModel::setModAmpLFOFoot(int v)
{
    unsigned char vv=static_cast<unsigned char>(v);
    if (vv != readMemoryLocation(MOD_AMP_LFO_FOOT)) {
        writeMemoryLocation(MOD_AMP_LFO_FOOT, vv);
        emit modAmpLFOFootChanged();
    }
}


int SynthModel::modPitchLFOAftertouch()
{
    return static_cast<int>(readMemoryLocation(MOD_PITCH_LFO_AFTER));
}

void SynthModel::setModPitchLFOAftertouch(int v)
{
    unsigned char vv=static_cast<unsigned char>(v);
    if (vv != readMemoryLocation(MOD_PITCH_LFO_AFTER)) {
        writeMemoryLocation(MOD_PITCH_LFO_AFTER, vv);
        emit modPitchLFOAftertouchChanged();
    }
}


int SynthModel::modAmpLFOAftertouch()
{
    return static_cast<int>(readMemoryLocation(MOD_AMP_LFO_AFTER));
}

void SynthModel::setModAmpLFOAftertouch(int v)
{
    unsigned char vv=static_cast<unsigned char>(v);
    if (vv != readMemoryLocation(MOD_AMP_LFO_AFTER)) {
        writeMemoryLocation(MOD_AMP_LFO_AFTER, vv);
        emit modAmpLFOAftertouchChanged();
    }
}

int SynthModel::masterPitchBendUp()
{
    return static_cast<int>(readMemoryLocation(MASTER_PITCHBEND_UP));
}

void SynthModel::setMasterPitchBendUp(int v)
{
    unsigned char vv=static_cast<unsigned char>(v);
    if (vv != readMemoryLocation(MASTER_PITCHBEND_UP)) {
        writeMemoryLocation(MASTER_PITCHBEND_UP, vv);
        emit masterPitchBendUpChanged();
    }
}

int SynthModel::masterPitchBendDown()
{
    return static_cast<int>(readMemoryLocation(MASTER_PITCHBEND_DOWN));
}

void SynthModel::setMasterPitchBendDown(int v)
{
    unsigned char vv=static_cast<unsigned char>(v);
    if (vv != readMemoryLocation(MASTER_PITCHBEND_DOWN)) {
        writeMemoryLocation(MASTER_PITCHBEND_DOWN, vv);
        emit masterPitchBendDownChanged();
    }
}

int SynthModel::masterTranspose()
{
    return static_cast<int>(readMemoryLocation(MASTER_TRANSPOSE));
}

void SynthModel::setMasterTranspose(int v)
{
    unsigned char vv=static_cast<unsigned char>(v);
    if (vv != readMemoryLocation(MASTER_TRANSPOSE)) {
        writeMemoryLocation(MASTER_TRANSPOSE, vv);
        emit masterTransposeChanged();
    }
}


int SynthModel::masterVolume()
{
    return static_cast<int>(readMemoryLocation(MASTER_VOLUME));
}

void SynthModel::setMasterVolume(int v)
{
    unsigned char vv=static_cast<unsigned char>(v);
    if (vv != readMemoryLocation(MASTER_VOLUME)) {
        writeMemoryLocation(MASTER_VOLUME, vv);
        emit masterVolumeChanged();
    }
}

int SynthModel::masterPan()
{
    return static_cast<int>(readMemoryLocation(MASTER_PAN));
}

void SynthModel::setMasterPan(int v)
{
    unsigned char vv=static_cast<unsigned char>(v);
    if (vv != readMemoryLocation(MASTER_PAN)) {
        writeMemoryLocation(MASTER_PAN, vv);
        emit masterPanChanged();
    }
}

int SynthModel::masterLegato()
{
    return static_cast<int>(readMemoryLocation(MASTER_LEGATO));
}

void SynthModel::setMasterLegato(int v)
{
    unsigned char vv=static_cast<unsigned char>(v);
    if (vv != readMemoryLocation(MASTER_LEGATO)) {
        writeMemoryLocation(MASTER_LEGATO, vv);
        emit masterLegatoChanged();
    }
}

int SynthModel::masterVelocityOffset()
{
    return static_cast<int>(readMemoryLocation(MASTER_VELOCITY_OFFSET));
}

void SynthModel::setMasterVelocityOffset(int v)
{
    unsigned char vv=static_cast<unsigned char>(v);
    if (vv != readMemoryLocation(MASTER_VELOCITY_OFFSET)) {
        writeMemoryLocation(MASTER_VELOCITY_OFFSET, vv);
        emit masterVelocityOffsetChanged();
    }
}

int SynthModel::masterTuning()
{
    return static_cast<int>(readMemoryLocation(MASTER_TUNING));
}

void SynthModel::setMasterTuning(int v)
{
    unsigned char vv=static_cast<unsigned char>(v);
    if (vv != readMemoryLocation(MASTER_TUNING)) {
        writeMemoryLocation(MASTER_TUNING, vv);
        emit masterTuningChanged();
    }
}


int SynthModel::modEnvelopeBiasAftertouch()
{
    return static_cast<int>(readMemoryLocation(MOD_EG_BIAS_AFTER));
}

void SynthModel::setModEnvelopeBiasAftertouch(int v)
{
    unsigned char vv=static_cast<unsigned char>(v);
    if (vv != readMemoryLocation(MOD_EG_BIAS_AFTER)) {
        writeMemoryLocation(MOD_EG_BIAS_AFTER, vv);
        emit modEnvelopeBiasAftertouchChanged();
    }
}

int SynthModel::modEnvelopeBiasWheel()
{
    return static_cast<int>(readMemoryLocation(MOD_EG_BIAS_WHEEL));
}

void SynthModel::setModEnvelopeBiasWheel(int v)
{
    unsigned char vv=static_cast<unsigned char>(v);
    if (vv != readMemoryLocation(MOD_EG_BIAS_WHEEL)) {
        writeMemoryLocation(MOD_EG_BIAS_WHEEL, vv);
        emit modEnvelopeBiasWheelChanged();
    }
}

int SynthModel::modEnvelopeBiasBreath()
{
    return static_cast<int>(readMemoryLocation(MOD_EG_BIAS_BREATH));
}

void SynthModel::setModEnvelopeBiasBreath(int v)
{
    unsigned char vv=static_cast<unsigned char>(v);
    if (vv != readMemoryLocation(MOD_EG_BIAS_BREATH)) {
        writeMemoryLocation(MOD_EG_BIAS_BREATH, vv);
        emit modEnvelopeBiasBreathChanged();
    }
}

int SynthModel::modEnvelopeBiasFoot()
{
    return static_cast<int>(readMemoryLocation(MOD_EG_BIAS_FOOT));
}

void SynthModel::setModEnvelopeBiasFoot(int v)
{
    unsigned char vv=static_cast<unsigned char>(v);
    if (vv != readMemoryLocation(MOD_EG_BIAS_FOOT)) {
        writeMemoryLocation(MOD_EG_BIAS_FOOT, vv);
        emit modEnvelopeBiasFootChanged();
    }
}

int SynthModel::modPitchAftertouch()
{
    return static_cast<int>(readMemoryLocation(MOD_PITCH_AFTER));
}

void SynthModel::setModPitchAftertouch(int v)
{
    unsigned char vv=static_cast<unsigned char>(v);
    if (vv != readMemoryLocation(MOD_PITCH_AFTER)) {
        writeMemoryLocation(MOD_PITCH_AFTER, vv);
        emit modPitchAftertouchChanged();
    }
}

int SynthModel::modPitchBreath()
{
    return static_cast<int>(readMemoryLocation(MOD_PITCH_BREATH));
}

void SynthModel::setModPitchBreath(int v)
{
    unsigned char vv=static_cast<unsigned char>(v);
    if (vv != readMemoryLocation(MOD_PITCH_BREATH)) {
        writeMemoryLocation(MOD_PITCH_BREATH, vv);
        emit modPitchBreathChanged();
    }
}

int SynthModel::modPitchFoot()
{
    return static_cast<int>(readMemoryLocation(MOD_PITCH_FOOT));
}

void SynthModel::setModPitchFoot(int v)
{
    unsigned char vv=static_cast<unsigned char>(v);
    if (vv != readMemoryLocation(MOD_PITCH_FOOT)) {
        writeMemoryLocation(MOD_PITCH_FOOT, vv);
        emit modPitchFootChanged();
    }
}

int SynthModel::modPitchRandom()
{
    return static_cast<int>(readMemoryLocation(MOD_PITCH_RANDOM));
}

void SynthModel::setModPitchRandom(int v)
{
    unsigned char vv=static_cast<unsigned char>(v);
    if (vv != readMemoryLocation(MOD_PITCH_RANDOM)) {
        writeMemoryLocation(MOD_PITCH_RANDOM, vv);
        emit modPitchRandomChanged();
    }
}

int SynthModel::portamentoMode()
{
    return static_cast<int>(readMemoryLocation(MASTER_PORTAMENTO_MODE));
}

void SynthModel::setPortamentoMode(int v)
{
    unsigned char vv=static_cast<unsigned char>(v);
    if (vv != readMemoryLocation(MASTER_PORTAMENTO_MODE)) {
        writeMemoryLocation(MASTER_PORTAMENTO_MODE, vv);
        emit portamentoModeChanged();
    }
}

int SynthModel::portamentoTime()
{
    return static_cast<int>(readMemoryLocation(MASTER_PORTAMENTO_TIME));
}

void SynthModel::setPortamentoTime(int v)
{
    unsigned char vv=static_cast<unsigned char>(v);
    if (vv != readMemoryLocation(MASTER_PORTAMENTO_TIME)) {
        writeMemoryLocation(MASTER_PORTAMENTO_TIME, vv);
        emit portamentoTimeChanged();
    }
}

int SynthModel::envelopeLoop()
{
    return static_cast<int>(readMemoryLocation(OP_EG_LOOP));
}

void SynthModel::setEnvelopeLoop(int v)
{
    unsigned char vv=static_cast<unsigned char>(v);
    if (vv != readMemoryLocation(OP_EG_LOOP)) {
        writeMemoryLocation(OP_EG_LOOP, vv);
        emit envelopeLoopChanged();
    }
}

int SynthModel::envelopeLoopSegment()
{
    return static_cast<int>(readMemoryLocation(OP_EG_LOOP_SEG));
}

void SynthModel::setEnvelopeLoopSegment(int v)
{
    unsigned char vv=static_cast<unsigned char>(v);
    if (vv != readMemoryLocation(OP_EG_LOOP_SEG)) {
        writeMemoryLocation(OP_EG_LOOP_SEG, vv);
        emit envelopeLoopSegmentChanged();
    }
}

int SynthModel::envelopeRestart()
{
    return static_cast<int>(readMemoryLocation(MASTER_EG_RESTART));
}

void SynthModel::setEnvelopeRestart(int v)
{
    unsigned char vv=static_cast<unsigned char>(v);
    if (vv != readMemoryLocation(MASTER_EG_RESTART)) {
        writeMemoryLocation(MASTER_EG_RESTART, vv);
        emit envelopeRestartChanged();
    }
}

int SynthModel::outputLevel()
{
    return static_cast<int>(readMemoryLocation(MASTER_OUTPUT));
}

void SynthModel::setOutputLevel(int v)
{
    unsigned char vv=static_cast<unsigned char>(v);
    if (vv != readMemoryLocation(MASTER_OUTPUT)) {
        writeMemoryLocation(MASTER_OUTPUT, vv);
        emit outputLevelChanged();
    }
}

int SynthModel::arpeggiatorMode()
{
    return static_cast<int>(readMemoryLocation(ARPEGGIATOR_MODE));
}

void SynthModel::setArpeggiatorMode(int v)
{
    unsigned char vv=static_cast<unsigned char>(v);
    if (vv != readMemoryLocation(ARPEGGIATOR_MODE)) {
        writeMemoryLocation(ARPEGGIATOR_MODE, vv);
        emit arpeggiatorModeChanged();
    }
}

int SynthModel::arpeggiatorTempo()
{
    return static_cast<int>(readMemoryLocation(ARPEGGIATOR_TEMPO));
}

void SynthModel::setArpeggiatorTempo(int v)
{
    unsigned char vv=static_cast<unsigned char>(v);
    if (vv != readMemoryLocation(ARPEGGIATOR_TEMPO)) {
        writeMemoryLocation(ARPEGGIATOR_TEMPO, vv);
        emit arpeggiatorTempoChanged();
    }
}


int SynthModel::arpeggiatorTempoMultiplier()
{
    return static_cast<int>(readMemoryLocation(ARPEGGIATOR_MUL));
}

void SynthModel::setArpeggiatorTempoMultiplier(int v)
{
    unsigned char vv=static_cast<unsigned char>(v);
    if (vv != readMemoryLocation(ARPEGGIATOR_MUL)) {
        writeMemoryLocation(ARPEGGIATOR_MUL, vv);
        emit arpeggiatorTempoMultiplierChanged();
    }
}


int SynthModel::arpeggiatorOctaveRange()
{
    return static_cast<int>(readMemoryLocation(ARPEGGIATOR_OCTAVES));
}

void SynthModel::setArpeggiatorOctaveRange(int v)
{
    unsigned char vv=static_cast<unsigned char>(v);
    if (vv != readMemoryLocation(ARPEGGIATOR_OCTAVES)) {
        writeMemoryLocation(ARPEGGIATOR_OCTAVES, vv);
        emit arpeggiatorOctaveRangeChanged();
    }
}

int SynthModel::fxBitCrushDepth()
{
    return static_cast<int>(readMemoryLocation(FX_BITCRUSHER_DEPTH));
}

void SynthModel::setFxBitCrushDepth(int v)
{
    unsigned char vv=static_cast<unsigned char>(v);
    if (vv != readMemoryLocation(FX_BITCRUSHER_DEPTH)) {
        writeMemoryLocation(FX_BITCRUSHER_DEPTH, vv);
        emit fxBitCrushDepthChanged();
    }
}

int SynthModel::fxDecimator()
{
    return static_cast<int>(readMemoryLocation(FX_DECIMATOR_DEPTH));
}

void SynthModel::setFxDecimator(int v)
{
    unsigned char vv=static_cast<unsigned char>(v);
    if (vv != readMemoryLocation(FX_DECIMATOR_DEPTH)) {
        writeMemoryLocation(FX_DECIMATOR_DEPTH, vv);
        emit fxDecimatorChanged();
    }
}

int SynthModel::filterLoCutoff()
{
    return static_cast<int>(readMemoryLocation(FX_FILTER_LO));
}

void SynthModel::setFilterLoCutoff(int v)
{
    unsigned char vv=static_cast<unsigned char>(v);
    if (vv != readMemoryLocation(FX_FILTER_LO)) {
        writeMemoryLocation(FX_FILTER_LO, vv);
        emit filterLoCutoffChanged();
    }
}

int SynthModel::filterHiCutoff()
{
    return static_cast<int>(readMemoryLocation(FX_FILTER_HI));
}

void SynthModel::setFilterHiCutoff(int v)
{
    unsigned char vv=static_cast<unsigned char>(v);
    if (vv != readMemoryLocation(FX_FILTER_HI)) {
        writeMemoryLocation(FX_FILTER_HI, vv);
        emit filterHiCutoffChanged();
    }
}

int SynthModel::fxChorusDry()
{
    return static_cast<int>(readMemoryLocation(FX_CHORUS_DRY));
}

void SynthModel::setFxChorusDry(int v)
{
    unsigned char vv=static_cast<unsigned char>(v);
    if (vv != readMemoryLocation(FX_CHORUS_DRY)) {
        writeMemoryLocation(FX_CHORUS_DRY, vv);
        emit fxChorusDryChanged();
    }
}

int SynthModel::fxChorusWet()
{
    return static_cast<int>(readMemoryLocation(FX_CHORUS_WET));
}

void SynthModel::setFxChorusWet(int v)
{
    unsigned char vv=static_cast<unsigned char>(v);
    if (vv != readMemoryLocation(FX_CHORUS_WET)) {
        writeMemoryLocation(FX_CHORUS_WET, vv);
        emit fxChorusWetChanged();
    }
}

int SynthModel::fxChorusMode()
{
    return static_cast<int>(readMemoryLocation(FX_CHORUS_MODE));
}

void SynthModel::setFxChorusMode(int v)
{
    unsigned char vv=static_cast<unsigned char>(v);
    if (vv != readMemoryLocation(FX_CHORUS_MODE)) {
        writeMemoryLocation(FX_CHORUS_MODE, vv);
        emit fxChorusModeChanged();
    }
}

int SynthModel::fxChorusSpeed()
{
    return static_cast<int>(readMemoryLocation(FX_CHORUS_SPEED));
}

void SynthModel::setFxChorusSpeed(int v)
{
    unsigned char vv=static_cast<unsigned char>(v);
    if (vv != readMemoryLocation(FX_CHORUS_SPEED)) {
        writeMemoryLocation(FX_CHORUS_SPEED, vv);
        emit fxChorusSpeedChanged();
    }
}

int SynthModel::fxChorusDepth()
{
    return static_cast<int>(readMemoryLocation(FX_CHORUS_DEPTH));
}

void SynthModel::setFxChorusDepth(int v)
{
    unsigned char vv=static_cast<unsigned char>(v);
    if (vv != readMemoryLocation(FX_CHORUS_DEPTH)) {
        writeMemoryLocation(FX_CHORUS_DEPTH, vv);
        emit fxChorusDepthChanged();
    }
}

int SynthModel::fxChorusFeedback()
{
    return static_cast<int>(readMemoryLocation(FX_CHORUS_FEEDBACK));
}

void SynthModel::setFxChorusFeedback(int v)
{
    unsigned char vv=static_cast<unsigned char>(v);
    if (vv != readMemoryLocation(FX_CHORUS_FEEDBACK)) {
        writeMemoryLocation(FX_CHORUS_FEEDBACK, vv);
        emit fxChorusFeedbackChanged();
    }
}


int SynthModel::fxChorusPhase()
{
    return static_cast<int>(readMemoryLocation(FX_CHORUS_LRPHASE));
}

void SynthModel::setFxChorusPhase(int v)
{
    unsigned char vv=static_cast<unsigned char>(v);
    if (vv != readMemoryLocation(FX_CHORUS_LRPHASE)) {
        writeMemoryLocation(FX_CHORUS_LRPHASE, vv);
        emit fxChorusPhaseChanged();
    }
}

int SynthModel::fxPhaserDry()
{
    return static_cast<int>(readMemoryLocation(FX_PHASER_DRY));
}

void SynthModel::setFxPhaserDry(int v)
{
    unsigned char vv=static_cast<unsigned char>(v);
    if (vv != readMemoryLocation(FX_PHASER_DRY)) {
        writeMemoryLocation(FX_PHASER_DRY, vv);
        emit fxPhaserDryChanged();
    }
}

int SynthModel::fxPhaserWet()
{
    return static_cast<int>(readMemoryLocation(FX_PHASER_WET));
}

void SynthModel::setFxPhaserWet(int v)
{
    unsigned char vv=static_cast<unsigned char>(v);
    if (vv != readMemoryLocation(FX_PHASER_WET)) {
        writeMemoryLocation(FX_PHASER_WET, vv);
        emit fxPhaserWetChanged();
    }
}

int SynthModel::fxPhaserMode()
{
    return static_cast<int>(readMemoryLocation(FX_PHASER_MODE));
}

void SynthModel::setFxPhaserMode(int v)
{
    unsigned char vv=static_cast<unsigned char>(v);
    if (vv != readMemoryLocation(FX_PHASER_MODE)) {
        writeMemoryLocation(FX_PHASER_MODE, vv);
        emit fxPhaserModeChanged();
    }
}

int SynthModel::fxPhaserSpeed()
{
    return static_cast<int>(readMemoryLocation(FX_PHASER_SPEED));
}

void SynthModel::setFxPhaserSpeed(int v)
{
    unsigned char vv=static_cast<unsigned char>(v);
    if (vv != readMemoryLocation(FX_PHASER_SPEED)) {
        writeMemoryLocation(FX_PHASER_SPEED, vv);
        emit fxPhaserSpeedChanged();
    }
}

int SynthModel::fxPhaserDepth()
{
    return static_cast<int>(readMemoryLocation(FX_PHASER_DEPTH));
}

void SynthModel::setFxPhaserDepth(int v)
{
    unsigned char vv=static_cast<unsigned char>(v);
    if (vv != readMemoryLocation(FX_PHASER_DEPTH)) {
        writeMemoryLocation(FX_PHASER_DEPTH, vv);
        emit fxPhaserDepthChanged();
    }
}

int SynthModel::fxPhaserOffset()
{
    return static_cast<int>(readMemoryLocation(FX_PHASER_OFFSET));
}

void SynthModel::setFxPhaserOffset(int v)
{
    unsigned char vv=static_cast<unsigned char>(v);
    if (vv != readMemoryLocation(FX_PHASER_OFFSET)) {
        writeMemoryLocation(FX_PHASER_OFFSET, vv);
        emit fxPhaserOffsetChanged();
    }
}

int SynthModel::fxPhaserStages()
{
    return static_cast<int>(readMemoryLocation(FX_PHASER_STAGES));
}

void SynthModel::setFxPhaserStages(int v)
{
    unsigned char vv=static_cast<unsigned char>(v);
    if (vv != readMemoryLocation(FX_PHASER_STAGES)) {
        writeMemoryLocation(FX_PHASER_STAGES, vv);
        emit fxPhaserStagesChanged();
    }
}

int SynthModel::fxPhaserFeedback()
{
    return static_cast<int>(readMemoryLocation(FX_PHASER_FEEDBACK));
}

void SynthModel::setFxPhaserFeedback(int v)
{
    unsigned char vv=static_cast<unsigned char>(v);
    if (vv != readMemoryLocation(FX_PHASER_FEEDBACK)) {
        writeMemoryLocation(FX_PHASER_FEEDBACK, vv);
        emit fxPhaserFeedbackChanged();
    }
}

int SynthModel::fxPhaserPhase()
{
    return static_cast<int>(readMemoryLocation(FX_PHASER_LRPHASE));
}

void SynthModel::setFxPhaserPhase(int v)
{
    unsigned char vv=static_cast<unsigned char>(v);
    if (vv != readMemoryLocation(FX_PHASER_LRPHASE)) {
        writeMemoryLocation(FX_PHASER_LRPHASE, vv);
        emit fxPhaserPhaseChanged();
    }
}

int SynthModel::fxDelayDry()
{
    return static_cast<int>(readMemoryLocation(FX_DELAY_DRY));
}

void SynthModel::setFxDelayDry(int v)
{
    unsigned char vv=static_cast<unsigned char>(v);
    if (vv != readMemoryLocation(FX_DELAY_DRY)) {
        writeMemoryLocation(FX_DELAY_DRY, vv);
        emit fxDelayDryChanged();
    }
}

int SynthModel::fxDelayWet()
{
    return static_cast<int>(readMemoryLocation(FX_DELAY_WET));
}

void SynthModel::setFxDelayWet(int v)
{
    unsigned char vv=static_cast<unsigned char>(v);
    if (vv != readMemoryLocation(FX_DELAY_WET)) {
        writeMemoryLocation(FX_DELAY_WET, vv);
        emit fxDelayWetChanged();
    }
}

int SynthModel::fxDelayMode()
{
    return static_cast<int>(readMemoryLocation(FX_DELAY_MODE));
}

void SynthModel::setFxDelayMode(int v)
{
    unsigned char vv=static_cast<unsigned char>(v);
    if (vv != readMemoryLocation(FX_DELAY_MODE)) {
        writeMemoryLocation(FX_DELAY_MODE, vv);
        emit fxDelayModeChanged();
    }
}

int SynthModel::fxDelayTime()
{
    return static_cast<int>(readMemoryLocation(FX_DELAY_TIME));
}

void SynthModel::setFxDelayTime(int v)
{
    unsigned char vv=static_cast<unsigned char>(v);
    if (vv != readMemoryLocation(FX_DELAY_TIME)) {
        writeMemoryLocation(FX_DELAY_TIME, vv);
        emit fxDelayTimeChanged();
    }
}


int SynthModel::fxDelayFeedback()
{
    return static_cast<int>(readMemoryLocation(FX_DELAY_FEEDBACK));
}

void SynthModel::setFxDelayFeedback(int v)
{
    unsigned char vv=static_cast<unsigned char>(v);
    if (vv != readMemoryLocation(FX_DELAY_FEEDBACK)) {
        writeMemoryLocation(FX_DELAY_FEEDBACK, vv);
        emit fxDelayFeedbackChanged();
    }
}

int SynthModel::fxDelayLowPass()
{
    return static_cast<int>(readMemoryLocation(FX_DELAY_LO));
}

void SynthModel::setFxDelayLowPass(int v)
{
    unsigned char vv=static_cast<unsigned char>(v);
    if (vv != readMemoryLocation(FX_DELAY_LO)) {
        writeMemoryLocation(FX_DELAY_LO, vv);
        emit fxDelayLowPassChanged();
    }
}

int SynthModel::fxDelayHighPass()
{
    return static_cast<int>(readMemoryLocation(FX_DELAY_HI));
}

void SynthModel::setFxDelayHighPass(int v)
{
    unsigned char vv=static_cast<unsigned char>(v);
    if (vv != readMemoryLocation(FX_DELAY_HI)) {
        writeMemoryLocation(FX_DELAY_HI, vv);
        emit fxDelayHighPassChanged();
    }
}

int SynthModel::fxDelayTempo()
{
    return static_cast<int>(readMemoryLocation(FX_DELAY_TEMPO));
}

void SynthModel::setFxDelayTempo(int v)
{
    unsigned char vv=static_cast<unsigned char>(v);
    if (vv != readMemoryLocation(FX_DELAY_TEMPO)) {
        writeMemoryLocation(FX_DELAY_TEMPO, vv);
        emit fxDelayTempoChanged();
    }
}

int SynthModel::fxDelayMultiplier()
{
    return static_cast<int>(readMemoryLocation(FX_DELAY_MUL));
}

void SynthModel::setFxDelayMultiplier(int v)
{
    unsigned char vv=static_cast<unsigned char>(v);
    if (vv != readMemoryLocation(FX_DELAY_MUL)) {
        writeMemoryLocation(FX_DELAY_MUL, vv);
        emit fxDelayMultiplierChanged();
    }
}

int SynthModel::fxDelayDivider()
{
    return static_cast<int>(readMemoryLocation(FX_DELAY_DIV));
}

void SynthModel::setFxDelayDivider(int v)
{
    unsigned char vv=static_cast<unsigned char>(v);
    if (vv != readMemoryLocation(FX_DELAY_DIV)) {
        writeMemoryLocation(FX_DELAY_DIV, vv);
        emit fxDelayDividerChanged();
    }
}

int SynthModel::fxAMDepth()
{
    return static_cast<int>(readMemoryLocation(FX_AM_DEPTH));
}

void SynthModel::setFxAMDepth(int v)
{
    unsigned char vv=static_cast<unsigned char>(v);
    if (vv != readMemoryLocation(FX_AM_DEPTH)) {
        writeMemoryLocation(FX_AM_DEPTH, vv);
        emit fxAMDepthChanged();
    }
}

int SynthModel::fxAMSpeed()
{
    return static_cast<int>(readMemoryLocation(FX_AM_SPEED));
}

void SynthModel::setFxAMSpeed(int v)
{
    unsigned char vv=static_cast<unsigned char>(v);
    if (vv != readMemoryLocation(FX_AM_SPEED)) {
        writeMemoryLocation(FX_AM_SPEED, vv);
        emit fxAMSpeedChanged();
    }
}

int SynthModel::fxAMRange()
{
    return static_cast<int>(readMemoryLocation(FX_AM_RANGE));
}

void SynthModel::setFxAMRange(int v)
{
    unsigned char vv=static_cast<unsigned char>(v);
    if (vv != readMemoryLocation(FX_AM_RANGE)) {
        writeMemoryLocation(FX_AM_RANGE, vv);
        emit fxAMRangeChanged();
    }
}

int SynthModel::fxAMPhase()
{
    return static_cast<int>(readMemoryLocation(FX_AM_LRPHASE));
}

void SynthModel::setFxAMPhase(int v)
{
    unsigned char vv=static_cast<unsigned char>(v);
    if (vv != readMemoryLocation(FX_AM_LRPHASE)) {
        writeMemoryLocation(FX_AM_LRPHASE, vv);
        emit fxAMPhaseChanged();
    }
}

int SynthModel::fxReverbDry()
{
    return static_cast<int>(readMemoryLocation(FX_REVERB_DRY));
}

void SynthModel::setFxReverbDry(int v)
{
    unsigned char vv=static_cast<unsigned char>(v);
    if (vv != readMemoryLocation(FX_REVERB_DRY)) {
        writeMemoryLocation(FX_REVERB_DRY, vv);
        emit fxReverbDryChanged();
    }
}

int SynthModel::fxReverbWet()
{
    return static_cast<int>(readMemoryLocation(FX_REVERB_WET));
}

void SynthModel::setFxReverbWet(int v)
{
    unsigned char vv=static_cast<unsigned char>(v);
    if (vv != readMemoryLocation(FX_REVERB_WET)) {
        writeMemoryLocation(FX_REVERB_WET, vv);
        emit fxReverbWetChanged();
    }
}

int SynthModel::fxReverbDamp()
{
    return static_cast<int>(readMemoryLocation(FX_REVERB_DAMP));
}

void SynthModel::setFxReverbDamp(int v)
{
    unsigned char vv=static_cast<unsigned char>(v);
    if (vv != readMemoryLocation(FX_REVERB_DAMP)) {
        writeMemoryLocation(FX_REVERB_DAMP, vv);
        emit fxReverbDampChanged();
    }
}

int SynthModel::fxReverbDecay()
{
    return static_cast<int>(readMemoryLocation(FX_REVERB_DECAY));
}

void SynthModel::setFxReverbDecay(int v)
{
    unsigned char vv=static_cast<unsigned char>(v);
    if (vv != readMemoryLocation(FX_REVERB_DECAY)) {
        writeMemoryLocation(FX_REVERB_DECAY, vv);
        emit fxReverbDecayChanged();
    }
}


int SynthModel::fxReverbMode()
{
    return static_cast<int>(readMemoryLocation(FX_REVERB_MODE));
}

void SynthModel::setFxReverbMode(int v)
{
    unsigned char vv=static_cast<unsigned char>(v);
    if (vv != readMemoryLocation(FX_REVERB_MODE)) {
        writeMemoryLocation(FX_REVERB_MODE, vv);
        emit fxReverbModeChanged();
    }
}

int SynthModel::fxRoute()
{
    return static_cast<int>(readMemoryLocation(FX_ROUTING));
}

void SynthModel::setFxRoute(int v)
{
    unsigned char vv=static_cast<unsigned char>(v);
    if (vv != readMemoryLocation(FX_ROUTING)) {
        writeMemoryLocation(FX_ROUTING, vv);
        emit fxRouteChanged();
    }
}


/* Operator Carrier and Modulation
 * This is a set of functions to do the necessary bit manipulation
 * so that we have a nicer high-level API for getting and
 * setting the carrier modes
 */
bool SynthModel::isOperatorACarrier(int op)
{
    unsigned char a;

    if (op < 0 || op > 5) {
        return false;
    }

    a=readMemoryLocation(static_cast<XFM2Parameter>(ALGO1+op));
    return (a & 1) != 0;
}


bool SynthModel::makeOperatorACarrier(int op, bool enabled)
{
    unsigned char a;

    if (op < 0 || op > 5) {
        return false;
    }

    a=readMemoryLocation(static_cast<XFM2Parameter>(ALGO1+op));
    if (enabled) {
        a=a|1;
    } else {
        if ((a & 1) != 0) a=a ^ 1;
    }
    writeMemoryLocation(static_cast<XFM2Parameter>(ALGO1+op), a);
    emit operatorHasChanged();

    return true;
}

bool SynthModel::isOperatorModulating(int op, int modulatingop)
{
    unsigned char a;

    if (op < 0 || op > 5) {
        return false;
    }

    if (modulatingop < 0 || modulatingop > 5) {
        return false;
    }

<<<<<<< HEAD
    modulatingop++;
    a=readMemoryLocation(static_cast<XFM2Parameter>(ALGO1+op));
    return (a & (1 << modulatingop)) != 0;
=======
    a=readMemoryLocation(static_cast<XFM2Parameter>(ALGO1+op));
    return (a & (2 << modulatingop)) != 0;
>>>>>>> 5f1b6151ec4d2bf472cad1981025fb954064533c
}

bool SynthModel::makeOperatorModulate(int op, int modulatingop, bool enabled)
{
    unsigned char a;

    if (op < 0 || op > 5) {
        return false;
    }

    if (modulatingop < 0 || modulatingop > 5) {
        return false;
    }

<<<<<<< HEAD
    modulatingop++;
    a=readMemoryLocation(static_cast<XFM2Parameter>(ALGO1+op));
    if (enabled) {
        a|=(1 << modulatingop);
    } else {
        if ((a & (1 << modulatingop)) != 0) {
            a^=(1 << modulatingop);
        }
    }
    writeMemoryLocation(static_cast<XFM2Parameter>(ALGO1+op), a);
    emit operatorHasChanged();
=======
    a=readMemoryLocation(static_cast<XFM2Parameter>(ALGO1+op));
    if (enabled) {
        a|=(2 << modulatingop);
    } else {
        if ((a & (2 << modulatingop)) != 0) {
            a^=(2 << modulatingop);
        }
    }
>>>>>>> 5f1b6151ec4d2bf472cad1981025fb954064533c

    return true;
}

/*
 * DX7 Algorithm.
 * Give this function an algorithm number from 1 to 32 and it
 * will set the appropriate operator carrier and
 * modulation bits
 */
bool SynthModel::makeDX7Algorithm(int a)
{
    unsigned char dx7[]={
        // 32 rows.  Each row has 6 operators plus one column that holds the feedback bit
        5, 0, 17, 32, 64, 0,    5,  // 1
        5, 0, 17, 32, 64, 0,    1,  // 2
        5, 8, 0, 33, 64, 0,     5,  // 3
        5, 8, 0, 33, 64, 16,    5,  // 4
        5, 0, 17, 0, 65, 0,     5,  // 5
        1, 4, 17, 0, 65, 32,    5,  // 6
        5, 0, 49, 0, 64, 0,     5,  // 7
        5, 0, 49, 0, 64, 0,     3,  // 8
        5, 0, 49, 0, 64, 0,     1,  // 9
        5, 8, 0, 97, 0, 0,      2,  // 10
        5, 8, 0, 97, 0, 0,      5,  // 11
        5, 0, 113, 0, 0, 0,     1,  // 12
        5, 0, 113, 0, 0, 0,     5,  // 13
        5, 0, 17, 96, 0, 0,     5,  // 14
        5, 0, 17, 96, 0, 0,     1,  // 15
        45, 0, 16, 0, 64, 0,    5,  // 16
        45, 0, 16, 0, 64, 0,    1,  // 17
        29, 0, 0, 32, 64, 0,    2,  // 18
        5, 8, 0, 65, 65, 0,     5,  // 19
        9, 9, 0, 65, 64, 0,     2,  // 20
        9, 9, 0, 65, 65, 0,     2,  // 21
        5, 0, 65, 65, 65, 0,    5,  // 22
        1, 9, 0, 65, 65, 0,     5,  // 23
        1, 1, 65, 65, 65, 0,    5,  // 24
        1, 1, 1, 65, 65, 0,     5,  // 25
        1, 9, 0, 97, 0, 0,      5,  // 26
        1, 9, 0, 97, 0, 0,      2,  // 27
        5, 0, 17, 32, 0, 1,     4,  // 28
        1, 1, 17, 0, 65, 0,     5,  // 29
        1, 1, 17, 32, 0, 1,     4,  // 30
        1, 1, 1, 1, 65, 0,      5,  // 31
        1, 1, 1, 1, 1, 1,       5   // 32
    };

    int offset=a*7;

    for (int i=0; i<6; i++) {
        writeMemoryLocation(static_cast<XFM2Parameter>(ALGO1+i), dx7[offset+i]);
    }

    emit operatorHasChanged();
    return true;
}

/*
 * Copy FM operator parameters into dedicated objects that
 * are easier to work with.  Operator objects can then be
 * manipulated and stored back to the model with a single
 * update
 */
QList<QObject *> SynthModel::fmOperators()
{
    QList<QObject *> oplist;

    for (int op=0; op<6; op++) {
        XFMOperator *o=new XFMOperator(this);

        o->setOperatorNumber(op);

        switch(op) {
            case 0:
                o->setAlgorithm(readMemoryLocation(ALGO1));
                o->setFeedback(readMemoryLocation(OP_FEEDBACK1));
                o->setRatio(readMemoryLocation(OP_RATIO1));
                o->setRatioFine(readMemoryLocation(OP_RATIOFINE1));
                o->setFine(readMemoryLocation(OP_FINE1));
                o->setLevel(readMemoryLocation(OP_LEVEL1));
                o->setVelocitySensitivity(readMemoryLocation(OP_VELO_SENS1));
                o->setKeyboardBreakpoint(readMemoryLocation(OP_KEY_BP1));
                o->setKeyboardScaleLeft(readMemoryLocation(OP_KEY_LDEPTH1));
                o->setKeyboardScaleRight(readMemoryLocation(OP_KEY_RDEPTH1));
                o->setKeyboardCurveLeft(readMemoryLocation(OP_KEY_LCURVE1));
                o->setKeyboardCurveRight(readMemoryLocation(OP_KEY_RCURVE1));
                o->setL0(readMemoryLocation(OP_LEVEL0_1));
                o->setL1(readMemoryLocation(OP_LEVEL1_1));
                o->setL2(readMemoryLocation(OP_LEVEL2_1));
                o->setL3(readMemoryLocation(OP_LEVEL3_1));
                o->setL4(readMemoryLocation(OP_LEVEL4_1));
                o->setL5(readMemoryLocation(OP_LEVEL5_1));
<<<<<<< HEAD
                o->setR0(readMemoryLocation(OP_DELAY_1));
=======
                o->setR0(255-readMemoryLocation(OP_DELAY_1));
>>>>>>> 5f1b6151ec4d2bf472cad1981025fb954064533c
                o->setR1(255-readMemoryLocation(OP_RATE1_1));
                o->setR2(255-readMemoryLocation(OP_RATE2_1));
                o->setR3(255-readMemoryLocation(OP_RATE3_1));
                o->setR4(255-readMemoryLocation(OP_RATE4_1));
                o->setR5(255-readMemoryLocation(OP_RATE5_1));
                o->setRateKey(readMemoryLocation(OP_RATE_KEY1));
                o->setAmplitudeModulationSensitivity(readMemoryLocation(OP_AMS1));
                o->setPitchModulationSensitivity(readMemoryLocation(OP_PMS_1));
                o->setWave1(readMemoryLocation(OP_WAVE1_1));
                o->setWave2(readMemoryLocation(OP_WAVE2_1));
                o->setLevelLeft(readMemoryLocation(OP_LEVEL_LEFT1));
                o->setLevelRight(readMemoryLocation(OP_LEVEL_RIGHT1));
                o->setOscillatorMode(readMemoryLocation(OP_WMODE_1));
                o->setOscillatorRatio(readMemoryLocation(OP_WRATIO_1));
                o->setPhase(readMemoryLocation(OP_PHASE1));
                break;

            case 1:
                o->setAlgorithm(readMemoryLocation(ALGO2));
                o->setFeedback(readMemoryLocation(OP_FEEDBACK2));
                o->setRatio(readMemoryLocation(OP_RATIO2));
                o->setRatioFine(readMemoryLocation(OP_RATIOFINE2));
                o->setFine(readMemoryLocation(OP_FINE2));
                o->setLevel(readMemoryLocation(OP_LEVEL2));
                o->setVelocitySensitivity(readMemoryLocation(OP_VELO_SENS2));
                o->setKeyboardBreakpoint(readMemoryLocation(OP_KEY_BP2));
                o->setKeyboardScaleLeft(readMemoryLocation(OP_KEY_LDEPTH2));
                o->setKeyboardScaleRight(readMemoryLocation(OP_KEY_RDEPTH2));
                o->setKeyboardCurveLeft(readMemoryLocation(OP_KEY_LCURVE2));
                o->setKeyboardCurveRight(readMemoryLocation(OP_KEY_RCURVE2));
                o->setL0(readMemoryLocation(OP_LEVEL0_2));
                o->setL1(readMemoryLocation(OP_LEVEL1_2));
                o->setL2(readMemoryLocation(OP_LEVEL2_2));
                o->setL3(readMemoryLocation(OP_LEVEL3_2));
                o->setL4(readMemoryLocation(OP_LEVEL4_2));
                o->setL5(readMemoryLocation(OP_LEVEL5_2));
<<<<<<< HEAD
                o->setR0(readMemoryLocation(OP_DELAY_2));
=======
                o->setR0(255-readMemoryLocation(OP_DELAY_2));
>>>>>>> 5f1b6151ec4d2bf472cad1981025fb954064533c
                o->setR1(255-readMemoryLocation(OP_RATE1_2));
                o->setR2(255-readMemoryLocation(OP_RATE2_2));
                o->setR3(255-readMemoryLocation(OP_RATE3_2));
                o->setR4(255-readMemoryLocation(OP_RATE4_2));
                o->setR5(255-readMemoryLocation(OP_RATE5_2));
                o->setRateKey(readMemoryLocation(OP_RATE_KEY2));
                o->setAmplitudeModulationSensitivity(readMemoryLocation(OP_AMS2));
                o->setPitchModulationSensitivity(readMemoryLocation(OP_PMS_2));
                o->setWave1(readMemoryLocation(OP_WAVE1_2));
                o->setWave2(readMemoryLocation(OP_WAVE2_2));
                o->setLevelLeft(readMemoryLocation(OP_LEVEL_LEFT2));
                o->setLevelRight(readMemoryLocation(OP_LEVEL_RIGHT2));
                o->setOscillatorMode(readMemoryLocation(OP_WMODE_2));
                o->setOscillatorRatio(readMemoryLocation(OP_WRATIO_2));
                o->setPhase(readMemoryLocation(OP_PHASE2));
                break;

            case 2:
                o->setAlgorithm(readMemoryLocation(ALGO3));
                o->setFeedback(readMemoryLocation(OP_FEEDBACK3));
                o->setRatio(readMemoryLocation(OP_RATIO3));
                o->setRatioFine(readMemoryLocation(OP_RATIOFINE3));
                o->setFine(readMemoryLocation(OP_FINE3));
                o->setLevel(readMemoryLocation(OP_LEVEL3));
                o->setVelocitySensitivity(readMemoryLocation(OP_VELO_SENS3));
                o->setKeyboardBreakpoint(readMemoryLocation(OP_KEY_BP3));
                o->setKeyboardScaleLeft(readMemoryLocation(OP_KEY_LDEPTH3));
                o->setKeyboardScaleRight(readMemoryLocation(OP_KEY_RDEPTH3));
                o->setKeyboardCurveLeft(readMemoryLocation(OP_KEY_LCURVE3));
                o->setKeyboardCurveRight(readMemoryLocation(OP_KEY_RCURVE3));
                o->setL0(readMemoryLocation(OP_LEVEL0_3));
                o->setL1(readMemoryLocation(OP_LEVEL1_3));
                o->setL2(readMemoryLocation(OP_LEVEL2_3));
                o->setL3(readMemoryLocation(OP_LEVEL3_3));
                o->setL4(readMemoryLocation(OP_LEVEL4_3));
                o->setL5(readMemoryLocation(OP_LEVEL5_3));
<<<<<<< HEAD
                o->setR0(readMemoryLocation(OP_DELAY_3));
=======
                o->setR0(255-readMemoryLocation(OP_DELAY_3));
>>>>>>> 5f1b6151ec4d2bf472cad1981025fb954064533c
                o->setR1(255-readMemoryLocation(OP_RATE1_3));
                o->setR2(255-readMemoryLocation(OP_RATE2_3));
                o->setR3(255-readMemoryLocation(OP_RATE3_3));
                o->setR4(255-readMemoryLocation(OP_RATE4_3));
                o->setR5(255-readMemoryLocation(OP_RATE5_3));
                o->setRateKey(readMemoryLocation(OP_RATE_KEY3));
                o->setAmplitudeModulationSensitivity(readMemoryLocation(OP_AMS3));
                o->setPitchModulationSensitivity(readMemoryLocation(OP_PMS_3));
                o->setWave1(readMemoryLocation(OP_WAVE1_3));
                o->setWave2(readMemoryLocation(OP_WAVE2_3));
                o->setLevelLeft(readMemoryLocation(OP_LEVEL_LEFT3));
                o->setLevelRight(readMemoryLocation(OP_LEVEL_RIGHT3));
                o->setOscillatorMode(readMemoryLocation(OP_WMODE_3));
                o->setOscillatorRatio(readMemoryLocation(OP_WRATIO_3));
                o->setPhase(readMemoryLocation(OP_PHASE3));
                break;

            case 3:
                o->setAlgorithm(readMemoryLocation(ALGO4));
                o->setFeedback(readMemoryLocation(OP_FEEDBACK4));
                o->setRatio(readMemoryLocation(OP_RATIO4));
                o->setRatioFine(readMemoryLocation(OP_RATIOFINE4));
                o->setFine(readMemoryLocation(OP_FINE4));
                o->setLevel(readMemoryLocation(OP_LEVEL4));
                o->setVelocitySensitivity(readMemoryLocation(OP_VELO_SENS4));
                o->setKeyboardBreakpoint(readMemoryLocation(OP_KEY_BP4));
                o->setKeyboardScaleLeft(readMemoryLocation(OP_KEY_LDEPTH4));
                o->setKeyboardScaleRight(readMemoryLocation(OP_KEY_RDEPTH4));
                o->setKeyboardCurveLeft(readMemoryLocation(OP_KEY_LCURVE4));
                o->setKeyboardCurveRight(readMemoryLocation(OP_KEY_RCURVE4));
                o->setL0(readMemoryLocation(OP_LEVEL0_4));
                o->setL1(readMemoryLocation(OP_LEVEL1_4));
                o->setL2(readMemoryLocation(OP_LEVEL2_4));
                o->setL3(readMemoryLocation(OP_LEVEL3_4));
                o->setL4(readMemoryLocation(OP_LEVEL4_4));
                o->setL5(readMemoryLocation(OP_LEVEL5_4));
<<<<<<< HEAD
                o->setR0(readMemoryLocation(OP_DELAY_4));
=======
                o->setR0(255-readMemoryLocation(OP_DELAY_4));
>>>>>>> 5f1b6151ec4d2bf472cad1981025fb954064533c
                o->setR1(255-readMemoryLocation(OP_RATE1_4));
                o->setR2(255-readMemoryLocation(OP_RATE2_4));
                o->setR3(255-readMemoryLocation(OP_RATE3_4));
                o->setR4(255-readMemoryLocation(OP_RATE4_4));
                o->setR5(255-readMemoryLocation(OP_RATE5_4));
                o->setRateKey(readMemoryLocation(OP_RATE_KEY4));
                o->setAmplitudeModulationSensitivity(readMemoryLocation(OP_AMS4));
                o->setPitchModulationSensitivity(readMemoryLocation(OP_PMS_4));
                o->setWave1(readMemoryLocation(OP_WAVE1_4));
                o->setWave2(readMemoryLocation(OP_WAVE2_4));
                o->setLevelLeft(readMemoryLocation(OP_LEVEL_LEFT4));
                o->setLevelRight(readMemoryLocation(OP_LEVEL_RIGHT4));
                o->setOscillatorMode(readMemoryLocation(OP_WMODE_4));
                o->setOscillatorRatio(readMemoryLocation(OP_WRATIO_4));
                o->setPhase(readMemoryLocation(OP_PHASE4));
                break;

            case 4:
                o->setAlgorithm(readMemoryLocation(ALGO5));
                o->setFeedback(readMemoryLocation(OP_FEEDBACK5));
                o->setRatio(readMemoryLocation(OP_RATIO5));
                o->setRatioFine(readMemoryLocation(OP_RATIOFINE5));
                o->setFine(readMemoryLocation(OP_FINE5));
                o->setLevel(readMemoryLocation(OP_LEVEL5));
                o->setVelocitySensitivity(readMemoryLocation(OP_VELO_SENS5));
                o->setKeyboardBreakpoint(readMemoryLocation(OP_KEY_BP5));
                o->setKeyboardScaleLeft(readMemoryLocation(OP_KEY_LDEPTH5));
                o->setKeyboardScaleRight(readMemoryLocation(OP_KEY_RDEPTH5));
                o->setKeyboardCurveLeft(readMemoryLocation(OP_KEY_LCURVE5));
                o->setKeyboardCurveRight(readMemoryLocation(OP_KEY_RCURVE5));
                o->setL0(readMemoryLocation(OP_LEVEL0_5));
                o->setL1(readMemoryLocation(OP_LEVEL1_5));
                o->setL2(readMemoryLocation(OP_LEVEL2_5));
                o->setL3(readMemoryLocation(OP_LEVEL3_5));
                o->setL4(readMemoryLocation(OP_LEVEL4_5));
                o->setL5(readMemoryLocation(OP_LEVEL5_5));
<<<<<<< HEAD
                o->setR0(readMemoryLocation(OP_DELAY_5));
=======
                o->setR0(255-readMemoryLocation(OP_DELAY_5));
>>>>>>> 5f1b6151ec4d2bf472cad1981025fb954064533c
                o->setR1(255-readMemoryLocation(OP_RATE1_5));
                o->setR2(255-readMemoryLocation(OP_RATE2_5));
                o->setR3(255-readMemoryLocation(OP_RATE3_5));
                o->setR4(255-readMemoryLocation(OP_RATE4_5));
                o->setR5(255-readMemoryLocation(OP_RATE5_5));
                o->setRateKey(readMemoryLocation(OP_RATE_KEY5));
                o->setAmplitudeModulationSensitivity(readMemoryLocation(OP_AMS5));
                o->setPitchModulationSensitivity(readMemoryLocation(OP_PMS_5));
                o->setWave1(readMemoryLocation(OP_WAVE1_5));
                o->setWave2(readMemoryLocation(OP_WAVE2_5));
                o->setLevelLeft(readMemoryLocation(OP_LEVEL_LEFT5));
                o->setLevelRight(readMemoryLocation(OP_LEVEL_RIGHT5));
                o->setOscillatorMode(readMemoryLocation(OP_WMODE_5));
                o->setOscillatorRatio(readMemoryLocation(OP_WRATIO_5));
                o->setPhase(readMemoryLocation(OP_PHASE5));
                break;

            case 5:
                o->setAlgorithm(readMemoryLocation(ALGO6));
                o->setFeedback(readMemoryLocation(OP_FEEDBACK6));
                o->setRatio(readMemoryLocation(OP_RATIO6));
                o->setRatioFine(readMemoryLocation(OP_RATIOFINE6));
                o->setFine(readMemoryLocation(OP_FINE6));
                o->setLevel(readMemoryLocation(OP_LEVEL6));
                o->setVelocitySensitivity(readMemoryLocation(OP_VELO_SENS6));
                o->setKeyboardBreakpoint(readMemoryLocation(OP_KEY_BP6));
                o->setKeyboardScaleLeft(readMemoryLocation(OP_KEY_LDEPTH6));
                o->setKeyboardScaleRight(readMemoryLocation(OP_KEY_RDEPTH6));
                o->setKeyboardCurveLeft(readMemoryLocation(OP_KEY_LCURVE6));
                o->setKeyboardCurveRight(readMemoryLocation(OP_KEY_RCURVE6));
                o->setL0(readMemoryLocation(OP_LEVEL0_6));
                o->setL1(readMemoryLocation(OP_LEVEL1_6));
                o->setL2(readMemoryLocation(OP_LEVEL2_6));
                o->setL3(readMemoryLocation(OP_LEVEL3_6));
                o->setL4(readMemoryLocation(OP_LEVEL4_6));
                o->setL5(readMemoryLocation(OP_LEVEL5_6));
<<<<<<< HEAD
                o->setR0(readMemoryLocation(OP_DELAY_6));
=======
                o->setR0(255-readMemoryLocation(OP_DELAY_6));
>>>>>>> 5f1b6151ec4d2bf472cad1981025fb954064533c
                o->setR1(255-readMemoryLocation(OP_RATE1_6));
                o->setR2(255-readMemoryLocation(OP_RATE2_6));
                o->setR3(255-readMemoryLocation(OP_RATE3_6));
                o->setR4(255-readMemoryLocation(OP_RATE4_6));
                o->setR5(255-readMemoryLocation(OP_RATE5_6));
                o->setRateKey(readMemoryLocation(OP_RATE_KEY6));
                o->setAmplitudeModulationSensitivity(readMemoryLocation(OP_AMS6));
                o->setPitchModulationSensitivity(readMemoryLocation(OP_PMS_6));
                o->setWave1(readMemoryLocation(OP_WAVE1_6));
                o->setWave2(readMemoryLocation(OP_WAVE2_6));
                o->setLevelLeft(readMemoryLocation(OP_LEVEL_LEFT6));
                o->setLevelRight(readMemoryLocation(OP_LEVEL_RIGHT6));
                o->setOscillatorMode(readMemoryLocation(OP_WMODE_6));
                o->setOscillatorRatio(readMemoryLocation(OP_WRATIO_6));
                o->setPhase(readMemoryLocation(OP_PHASE6));
                break;

            default:
                break;
        }

        oplist.push_back(o);
    }

    return oplist;
}

/*
 * Save an FM Operator back to the main synth
 * model.
 */

bool SynthModel::updateOperator(XFMOperator *op, bool notify/*=false*/)
{
    switch (op->operatorNumber()) {
        case 0:
            writeMemoryLocation(ALGO1, static_cast<unsigned char>(op->algorithm()));
            writeMemoryLocation(OP_FEEDBACK1, static_cast<unsigned char>(op->feedback()));
            writeMemoryLocation(OP_RATIO1, static_cast<unsigned char>(op->ratio()));
            writeMemoryLocation(OP_RATIOFINE1, static_cast<unsigned char>(op->ratioFine()));
            writeMemoryLocation(OP_FINE1, static_cast<unsigned char>(op->fine()));
            writeMemoryLocation(OP_LEVEL1, static_cast<unsigned char>(op->level()));
            writeMemoryLocation(OP_VELO_SENS1, static_cast<unsigned char>(op->velocitySensitivity()));
            writeMemoryLocation(OP_KEY_BP1, static_cast<unsigned char>(op->keyboardBreakpoint()));
            writeMemoryLocation(OP_KEY_LDEPTH1, static_cast<unsigned char>(op->keyboardScaleLeft()));
            writeMemoryLocation(OP_KEY_RDEPTH1, static_cast<unsigned char>(op->keyboardScaleRight()));
            writeMemoryLocation(OP_KEY_LCURVE1, static_cast<unsigned char>(op->keyboardCurveLeft()));
            writeMemoryLocation(OP_KEY_RCURVE1, static_cast<unsigned char>(op->keyboardCurveRight()));
            writeMemoryLocation(OP_LEVEL0_1, static_cast<unsigned char>(op->L0()));
            writeMemoryLocation(OP_LEVEL1_1, static_cast<unsigned char>(op->L1()));
            writeMemoryLocation(OP_LEVEL2_1, static_cast<unsigned char>(op->L2()));
            writeMemoryLocation(OP_LEVEL3_1, static_cast<unsigned char>(op->L3()));
            writeMemoryLocation(OP_LEVEL4_1, static_cast<unsigned char>(op->L4()));
            writeMemoryLocation(OP_LEVEL5_1, static_cast<unsigned char>(op->L5()));
<<<<<<< HEAD
            writeMemoryLocation(OP_DELAY_1, static_cast<unsigned char>(op->R0()));
=======
            writeMemoryLocation(OP_DELAY_1, 255-static_cast<unsigned char>(op->R0()));
>>>>>>> 5f1b6151ec4d2bf472cad1981025fb954064533c
            writeMemoryLocation(OP_RATE1_1, 255-static_cast<unsigned char>(op->R1()));
            writeMemoryLocation(OP_RATE2_1, 255-static_cast<unsigned char>(op->R2()));
            writeMemoryLocation(OP_RATE3_1, 255-static_cast<unsigned char>(op->R3()));
            writeMemoryLocation(OP_RATE4_1, 255-static_cast<unsigned char>(op->R4()));
            writeMemoryLocation(OP_RATE5_1, 255-static_cast<unsigned char>(op->R5()));
            writeMemoryLocation(OP_RATE_KEY1, static_cast<unsigned char>(op->rateKey()));
            writeMemoryLocation(OP_AMS1, static_cast<unsigned char>(op->amplitudeModulationSensitivity()));
            writeMemoryLocation(OP_PMS_1, static_cast<unsigned char>(op->pitchModulationSensitivity()));
            writeMemoryLocation(OP_WAVE1_1, static_cast<unsigned char>(op->wave1()));
            writeMemoryLocation(OP_WAVE2_1, static_cast<unsigned char>(op->wave2()));
            writeMemoryLocation(OP_LEVEL_LEFT1, static_cast<unsigned char>(op->levelLeft()));
            writeMemoryLocation(OP_LEVEL_RIGHT1, static_cast<unsigned char>(op->levelRight()));
            writeMemoryLocation(OP_WMODE_1, static_cast<unsigned char>(op->oscillatorMode()));
            writeMemoryLocation(OP_WRATIO_1, static_cast<unsigned char>(op->oscillatorRatio()));
            writeMemoryLocation(OP_PHASE1, static_cast<unsigned char>(op->phase()));
            break;

        case 1:
            writeMemoryLocation(ALGO2, static_cast<unsigned char>(op->algorithm()));
            writeMemoryLocation(OP_FEEDBACK2, static_cast<unsigned char>(op->feedback()));
            writeMemoryLocation(OP_RATIO2, static_cast<unsigned char>(op->ratio()));
            writeMemoryLocation(OP_RATIOFINE2, static_cast<unsigned char>(op->ratioFine()));
            writeMemoryLocation(OP_FINE2, static_cast<unsigned char>(op->fine()));
            writeMemoryLocation(OP_LEVEL2, static_cast<unsigned char>(op->level()));
            writeMemoryLocation(OP_VELO_SENS2, static_cast<unsigned char>(op->velocitySensitivity()));
            writeMemoryLocation(OP_KEY_BP2, static_cast<unsigned char>(op->keyboardBreakpoint()));
            writeMemoryLocation(OP_KEY_LDEPTH2, static_cast<unsigned char>(op->keyboardScaleLeft()));
            writeMemoryLocation(OP_KEY_RDEPTH2, static_cast<unsigned char>(op->keyboardScaleRight()));
            writeMemoryLocation(OP_KEY_LCURVE2, static_cast<unsigned char>(op->keyboardCurveLeft()));
            writeMemoryLocation(OP_KEY_RCURVE2, static_cast<unsigned char>(op->keyboardCurveRight()));
            writeMemoryLocation(OP_LEVEL0_2, static_cast<unsigned char>(op->L0()));
            writeMemoryLocation(OP_LEVEL1_2, static_cast<unsigned char>(op->L1()));
            writeMemoryLocation(OP_LEVEL2_2, static_cast<unsigned char>(op->L2()));
            writeMemoryLocation(OP_LEVEL3_2, static_cast<unsigned char>(op->L3()));
            writeMemoryLocation(OP_LEVEL4_2, static_cast<unsigned char>(op->L4()));
            writeMemoryLocation(OP_LEVEL5_2, static_cast<unsigned char>(op->L5()));
<<<<<<< HEAD
            writeMemoryLocation(OP_DELAY_2, static_cast<unsigned char>(op->R0()));
=======
            writeMemoryLocation(OP_DELAY_2, 255-static_cast<unsigned char>(op->R0()));
>>>>>>> 5f1b6151ec4d2bf472cad1981025fb954064533c
            writeMemoryLocation(OP_RATE1_2, 255-static_cast<unsigned char>(op->R1()));
            writeMemoryLocation(OP_RATE2_2, 255-static_cast<unsigned char>(op->R2()));
            writeMemoryLocation(OP_RATE3_2, 255-static_cast<unsigned char>(op->R3()));
            writeMemoryLocation(OP_RATE4_2, 255-static_cast<unsigned char>(op->R4()));
            writeMemoryLocation(OP_RATE5_2, 255-static_cast<unsigned char>(op->R5()));
            writeMemoryLocation(OP_RATE_KEY2, static_cast<unsigned char>(op->rateKey()));
            writeMemoryLocation(OP_AMS2, static_cast<unsigned char>(op->amplitudeModulationSensitivity()));
            writeMemoryLocation(OP_PMS_2, static_cast<unsigned char>(op->pitchModulationSensitivity()));
            writeMemoryLocation(OP_WAVE1_2, static_cast<unsigned char>(op->wave1()));
            writeMemoryLocation(OP_WAVE2_2, static_cast<unsigned char>(op->wave2()));
            writeMemoryLocation(OP_LEVEL_LEFT2, static_cast<unsigned char>(op->levelLeft()));
            writeMemoryLocation(OP_LEVEL_RIGHT2, static_cast<unsigned char>(op->levelRight()));
            writeMemoryLocation(OP_WMODE_2, static_cast<unsigned char>(op->oscillatorMode()));
            writeMemoryLocation(OP_WRATIO_2, static_cast<unsigned char>(op->oscillatorRatio()));
            writeMemoryLocation(OP_PHASE2, static_cast<unsigned char>(op->phase()));
            break;

        case 2:
            writeMemoryLocation(ALGO3, static_cast<unsigned char>(op->algorithm()));
            writeMemoryLocation(OP_FEEDBACK3, static_cast<unsigned char>(op->feedback()));
            writeMemoryLocation(OP_RATIO3, static_cast<unsigned char>(op->ratio()));
            writeMemoryLocation(OP_RATIOFINE3, static_cast<unsigned char>(op->ratioFine()));
            writeMemoryLocation(OP_FINE3, static_cast<unsigned char>(op->fine()));
            writeMemoryLocation(OP_LEVEL3, static_cast<unsigned char>(op->level()));
            writeMemoryLocation(OP_VELO_SENS3, static_cast<unsigned char>(op->velocitySensitivity()));
            writeMemoryLocation(OP_KEY_BP3, static_cast<unsigned char>(op->keyboardBreakpoint()));
            writeMemoryLocation(OP_KEY_LDEPTH3, static_cast<unsigned char>(op->keyboardScaleLeft()));
            writeMemoryLocation(OP_KEY_RDEPTH3, static_cast<unsigned char>(op->keyboardScaleRight()));
            writeMemoryLocation(OP_KEY_LCURVE3, static_cast<unsigned char>(op->keyboardCurveLeft()));
            writeMemoryLocation(OP_KEY_RCURVE3, static_cast<unsigned char>(op->keyboardCurveRight()));
            writeMemoryLocation(OP_LEVEL0_3, static_cast<unsigned char>(op->L0()));
            writeMemoryLocation(OP_LEVEL1_3, static_cast<unsigned char>(op->L1()));
            writeMemoryLocation(OP_LEVEL2_3, static_cast<unsigned char>(op->L2()));
            writeMemoryLocation(OP_LEVEL3_3, static_cast<unsigned char>(op->L3()));
            writeMemoryLocation(OP_LEVEL4_3, static_cast<unsigned char>(op->L4()));
            writeMemoryLocation(OP_LEVEL5_3, static_cast<unsigned char>(op->L5()));
<<<<<<< HEAD
            writeMemoryLocation(OP_DELAY_3, static_cast<unsigned char>(op->R0()));
=======
            writeMemoryLocation(OP_DELAY_3, 255-static_cast<unsigned char>(op->R0()));
>>>>>>> 5f1b6151ec4d2bf472cad1981025fb954064533c
            writeMemoryLocation(OP_RATE1_3, 255-static_cast<unsigned char>(op->R1()));
            writeMemoryLocation(OP_RATE2_3, 255-static_cast<unsigned char>(op->R2()));
            writeMemoryLocation(OP_RATE3_3, 255-static_cast<unsigned char>(op->R3()));
            writeMemoryLocation(OP_RATE4_3, 255-static_cast<unsigned char>(op->R4()));
            writeMemoryLocation(OP_RATE5_3, 255-static_cast<unsigned char>(op->R5()));
            writeMemoryLocation(OP_RATE_KEY3, static_cast<unsigned char>(op->rateKey()));
            writeMemoryLocation(OP_AMS3, static_cast<unsigned char>(op->amplitudeModulationSensitivity()));
            writeMemoryLocation(OP_PMS_3, static_cast<unsigned char>(op->pitchModulationSensitivity()));
            writeMemoryLocation(OP_WAVE1_3, static_cast<unsigned char>(op->wave1()));
            writeMemoryLocation(OP_WAVE2_3, static_cast<unsigned char>(op->wave2()));
            writeMemoryLocation(OP_LEVEL_LEFT3, static_cast<unsigned char>(op->levelLeft()));
            writeMemoryLocation(OP_LEVEL_RIGHT3, static_cast<unsigned char>(op->levelRight()));
            writeMemoryLocation(OP_WMODE_3, static_cast<unsigned char>(op->oscillatorMode()));
            writeMemoryLocation(OP_WRATIO_3, static_cast<unsigned char>(op->oscillatorRatio()));
            writeMemoryLocation(OP_PHASE3, static_cast<unsigned char>(op->phase()));
            break;

        case 3:
            writeMemoryLocation(ALGO4, static_cast<unsigned char>(op->algorithm()));
            writeMemoryLocation(OP_FEEDBACK4, static_cast<unsigned char>(op->feedback()));
            writeMemoryLocation(OP_RATIO4, static_cast<unsigned char>(op->ratio()));
            writeMemoryLocation(OP_RATIOFINE4, static_cast<unsigned char>(op->ratioFine()));
            writeMemoryLocation(OP_FINE4, static_cast<unsigned char>(op->fine()));
            writeMemoryLocation(OP_LEVEL4, static_cast<unsigned char>(op->level()));
            writeMemoryLocation(OP_VELO_SENS4, static_cast<unsigned char>(op->velocitySensitivity()));
            writeMemoryLocation(OP_KEY_BP4, static_cast<unsigned char>(op->keyboardBreakpoint()));
            writeMemoryLocation(OP_KEY_LDEPTH4, static_cast<unsigned char>(op->keyboardScaleLeft()));
            writeMemoryLocation(OP_KEY_RDEPTH4, static_cast<unsigned char>(op->keyboardScaleRight()));
            writeMemoryLocation(OP_KEY_LCURVE4, static_cast<unsigned char>(op->keyboardCurveLeft()));
            writeMemoryLocation(OP_KEY_RCURVE4, static_cast<unsigned char>(op->keyboardCurveRight()));
            writeMemoryLocation(OP_LEVEL0_4, static_cast<unsigned char>(op->L0()));
            writeMemoryLocation(OP_LEVEL1_4, static_cast<unsigned char>(op->L1()));
            writeMemoryLocation(OP_LEVEL2_4, static_cast<unsigned char>(op->L2()));
            writeMemoryLocation(OP_LEVEL3_4, static_cast<unsigned char>(op->L3()));
            writeMemoryLocation(OP_LEVEL4_4, static_cast<unsigned char>(op->L4()));
            writeMemoryLocation(OP_LEVEL5_4, static_cast<unsigned char>(op->L5()));
<<<<<<< HEAD
            writeMemoryLocation(OP_DELAY_4, static_cast<unsigned char>(op->R0()));
=======
            writeMemoryLocation(OP_DELAY_4, 255-static_cast<unsigned char>(op->R0()));
>>>>>>> 5f1b6151ec4d2bf472cad1981025fb954064533c
            writeMemoryLocation(OP_RATE1_4, 255-static_cast<unsigned char>(op->R1()));
            writeMemoryLocation(OP_RATE2_4, 255-static_cast<unsigned char>(op->R2()));
            writeMemoryLocation(OP_RATE3_4, 255-static_cast<unsigned char>(op->R3()));
            writeMemoryLocation(OP_RATE4_4, 255-static_cast<unsigned char>(op->R4()));
            writeMemoryLocation(OP_RATE5_4, 255-static_cast<unsigned char>(op->R5()));
            writeMemoryLocation(OP_RATE_KEY4, static_cast<unsigned char>(op->rateKey()));
            writeMemoryLocation(OP_AMS4, static_cast<unsigned char>(op->amplitudeModulationSensitivity()));
            writeMemoryLocation(OP_PMS_4, static_cast<unsigned char>(op->pitchModulationSensitivity()));
            writeMemoryLocation(OP_WAVE1_4, static_cast<unsigned char>(op->wave1()));
            writeMemoryLocation(OP_WAVE2_4, static_cast<unsigned char>(op->wave2()));
            writeMemoryLocation(OP_LEVEL_LEFT4, static_cast<unsigned char>(op->levelLeft()));
            writeMemoryLocation(OP_LEVEL_RIGHT4, static_cast<unsigned char>(op->levelRight()));
            writeMemoryLocation(OP_WMODE_4, static_cast<unsigned char>(op->oscillatorMode()));
            writeMemoryLocation(OP_WRATIO_4, static_cast<unsigned char>(op->oscillatorRatio()));
            writeMemoryLocation(OP_PHASE4, static_cast<unsigned char>(op->phase()));
            break;

        case 4:
            writeMemoryLocation(ALGO5, static_cast<unsigned char>(op->algorithm()));
            writeMemoryLocation(OP_FEEDBACK5, static_cast<unsigned char>(op->feedback()));
            writeMemoryLocation(OP_RATIO5, static_cast<unsigned char>(op->ratio()));
            writeMemoryLocation(OP_RATIOFINE5, static_cast<unsigned char>(op->ratioFine()));
            writeMemoryLocation(OP_FINE5, static_cast<unsigned char>(op->fine()));
            writeMemoryLocation(OP_LEVEL5, static_cast<unsigned char>(op->level()));
            writeMemoryLocation(OP_VELO_SENS5, static_cast<unsigned char>(op->velocitySensitivity()));
            writeMemoryLocation(OP_KEY_BP5, static_cast<unsigned char>(op->keyboardBreakpoint()));
            writeMemoryLocation(OP_KEY_LDEPTH5, static_cast<unsigned char>(op->keyboardScaleLeft()));
            writeMemoryLocation(OP_KEY_RDEPTH5, static_cast<unsigned char>(op->keyboardScaleRight()));
            writeMemoryLocation(OP_KEY_LCURVE5, static_cast<unsigned char>(op->keyboardCurveLeft()));
            writeMemoryLocation(OP_KEY_RCURVE5, static_cast<unsigned char>(op->keyboardCurveRight()));
            writeMemoryLocation(OP_LEVEL0_5, static_cast<unsigned char>(op->L0()));
            writeMemoryLocation(OP_LEVEL1_5, static_cast<unsigned char>(op->L1()));
            writeMemoryLocation(OP_LEVEL2_5, static_cast<unsigned char>(op->L2()));
            writeMemoryLocation(OP_LEVEL3_5, static_cast<unsigned char>(op->L3()));
            writeMemoryLocation(OP_LEVEL4_5, static_cast<unsigned char>(op->L4()));
            writeMemoryLocation(OP_LEVEL5_5, static_cast<unsigned char>(op->L5()));
<<<<<<< HEAD
            writeMemoryLocation(OP_DELAY_5, static_cast<unsigned char>(op->R0()));
=======
            writeMemoryLocation(OP_DELAY_5, 255-static_cast<unsigned char>(op->R0()));
>>>>>>> 5f1b6151ec4d2bf472cad1981025fb954064533c
            writeMemoryLocation(OP_RATE1_5, 255-static_cast<unsigned char>(op->R1()));
            writeMemoryLocation(OP_RATE2_5, 255-static_cast<unsigned char>(op->R2()));
            writeMemoryLocation(OP_RATE3_5, 255-static_cast<unsigned char>(op->R3()));
            writeMemoryLocation(OP_RATE4_5, 255-static_cast<unsigned char>(op->R4()));
            writeMemoryLocation(OP_RATE5_5, 255-static_cast<unsigned char>(op->R5()));
            writeMemoryLocation(OP_RATE_KEY5, static_cast<unsigned char>(op->rateKey()));
            writeMemoryLocation(OP_AMS5, static_cast<unsigned char>(op->amplitudeModulationSensitivity()));
            writeMemoryLocation(OP_PMS_5, static_cast<unsigned char>(op->pitchModulationSensitivity()));
            writeMemoryLocation(OP_WAVE1_5, static_cast<unsigned char>(op->wave1()));
            writeMemoryLocation(OP_WAVE2_5, static_cast<unsigned char>(op->wave2()));
            writeMemoryLocation(OP_LEVEL_LEFT5, static_cast<unsigned char>(op->levelLeft()));
            writeMemoryLocation(OP_LEVEL_RIGHT5, static_cast<unsigned char>(op->levelRight()));
            writeMemoryLocation(OP_WMODE_5, static_cast<unsigned char>(op->oscillatorMode()));
            writeMemoryLocation(OP_WRATIO_5, static_cast<unsigned char>(op->oscillatorRatio()));
            writeMemoryLocation(OP_PHASE5, static_cast<unsigned char>(op->phase()));
            break;

        case 5:
            writeMemoryLocation(ALGO6, static_cast<unsigned char>(op->algorithm()));
            writeMemoryLocation(OP_FEEDBACK6, static_cast<unsigned char>(op->feedback()));
            writeMemoryLocation(OP_RATIO6, static_cast<unsigned char>(op->ratio()));
            writeMemoryLocation(OP_RATIOFINE6, static_cast<unsigned char>(op->ratioFine()));
            writeMemoryLocation(OP_FINE6, static_cast<unsigned char>(op->fine()));
            writeMemoryLocation(OP_LEVEL6, static_cast<unsigned char>(op->level()));
            writeMemoryLocation(OP_VELO_SENS6, static_cast<unsigned char>(op->velocitySensitivity()));
            writeMemoryLocation(OP_KEY_BP6, static_cast<unsigned char>(op->keyboardBreakpoint()));
            writeMemoryLocation(OP_KEY_LDEPTH6, static_cast<unsigned char>(op->keyboardScaleLeft()));
            writeMemoryLocation(OP_KEY_RDEPTH6, static_cast<unsigned char>(op->keyboardScaleRight()));
            writeMemoryLocation(OP_KEY_LCURVE6, static_cast<unsigned char>(op->keyboardCurveLeft()));
            writeMemoryLocation(OP_KEY_RCURVE6, static_cast<unsigned char>(op->keyboardCurveRight()));
            writeMemoryLocation(OP_LEVEL0_6, static_cast<unsigned char>(op->L0()));
            writeMemoryLocation(OP_LEVEL1_6, static_cast<unsigned char>(op->L1()));
            writeMemoryLocation(OP_LEVEL2_6, static_cast<unsigned char>(op->L2()));
            writeMemoryLocation(OP_LEVEL3_6, static_cast<unsigned char>(op->L3()));
            writeMemoryLocation(OP_LEVEL4_6, static_cast<unsigned char>(op->L4()));
            writeMemoryLocation(OP_LEVEL5_6, static_cast<unsigned char>(op->L5()));
<<<<<<< HEAD
            writeMemoryLocation(OP_DELAY_6, static_cast<unsigned char>(op->R0()));
=======
            writeMemoryLocation(OP_DELAY_6, 255-static_cast<unsigned char>(op->R0()));
>>>>>>> 5f1b6151ec4d2bf472cad1981025fb954064533c
            writeMemoryLocation(OP_RATE1_6, 255-static_cast<unsigned char>(op->R1()));
            writeMemoryLocation(OP_RATE2_6, 255-static_cast<unsigned char>(op->R2()));
            writeMemoryLocation(OP_RATE3_6, 255-static_cast<unsigned char>(op->R3()));
            writeMemoryLocation(OP_RATE4_6, 255-static_cast<unsigned char>(op->R4()));
            writeMemoryLocation(OP_RATE5_6, 255-static_cast<unsigned char>(op->R5()));
            writeMemoryLocation(OP_RATE_KEY6, static_cast<unsigned char>(op->rateKey()));
            writeMemoryLocation(OP_AMS6, static_cast<unsigned char>(op->amplitudeModulationSensitivity()));
            writeMemoryLocation(OP_PMS_6, static_cast<unsigned char>(op->pitchModulationSensitivity()));
            writeMemoryLocation(OP_WAVE1_6, static_cast<unsigned char>(op->wave1()));
            writeMemoryLocation(OP_WAVE2_6, static_cast<unsigned char>(op->wave2()));
            writeMemoryLocation(OP_LEVEL_LEFT6, static_cast<unsigned char>(op->levelLeft()));
            writeMemoryLocation(OP_LEVEL_RIGHT6, static_cast<unsigned char>(op->levelRight()));
            writeMemoryLocation(OP_WMODE_6, static_cast<unsigned char>(op->oscillatorMode()));
            writeMemoryLocation(OP_WRATIO_6, static_cast<unsigned char>(op->oscillatorRatio()));
            writeMemoryLocation(OP_PHASE6, static_cast<unsigned char>(op->phase()));
            break;

        default:
            break;
    }

    if (notify) {
        emit operatorHasChanged();
    }

    return true;
}

/*
 * Patch names are not handled by the hardware.
 * So we simulate them by maintaining a file that
 * holds a list of the names.  This file is saved and retrieved
 * automatically whenever a patch name changes
 */
void SynthModel::loadPatchNames()
{
    FILE *fp;
    char bf[130];

    fp=fopen(PATCHFILE, "rt");
    if (fp == nullptr) {
        for (int i=0; i<128; i++) {
            m_patchNames[i]="Untitled";
        }

        m_patchNameBuffer="Untitled";
        return;
    }

    while (fgets(bf, 130, fp) != nullptr) {
        char *tk;

        if (bf[0]) {
            tk=&bf[strlen(bf)-1];
            while (*tk == '\n' || *tk == '\r') {
                *tk--=0;
            }
        }

        tk=strchr(bf, '=');
        if (tk == nullptr) {
            continue;
        }

        *tk++=0;
        int p=atoi(bf)-1;

        if (p < 0 || p > 127) {
            continue;
        }

        m_patchNames[p]=tk;
    }

    fclose(fp);

    if (m_patchnumber >= 0 && m_patchnumber < 128) {
        m_patchNameBuffer=m_patchNames[m_patchnumber];
    }
}

void SynthModel::savePatchNames()
{
    FILE *fp;

    fp=fopen(PATCHFILE, "wt");
    if (fp == nullptr) {
        return;
    }

    for (int p=0; p<128; p++) {
        char bf[300];

        sprintf(bf, "%d=%s", p+1, m_patchNames[p].c_str());
        fprintf(fp, "%s\n", bf);
    }

    fclose(fp);
}

QString SynthModel::patchName()
{
    return QString(m_patchNameBuffer.c_str());
}

void SynthModel::setPatchName(const QString &str)
{
    m_patchNameBuffer=str.toStdString();
}

