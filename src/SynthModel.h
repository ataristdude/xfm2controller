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

#ifndef SYNTHMODEL_H
#define SYNTHMODEL_H

#include <QObject>
#include <QString>
#include <QList>
#include <QtSerialPort/QSerialPort>
#include "xfm2.h"
#include "xfmoperator.h"
#include <string>
#include <vector>

/*
 * This is a model for controlling the synth.  It works by using a memory buffer to hold
 * a copy of the synth parameters so they may be queried without having to access the serial
 * port.  This reduces latency.
 *
 * It's not the most efficient interface.  Ideally it would have made sense to create
 * smaller classes for some of the function blocks, e.g. I could have made a PitchEnvelope class
 * instead of a bunch of pitchEG properties.  But in the end I went for simplicity over
 * a complicated class design, just to keep things easy to maintain should additional
 * parameters be added to the synth itself.  I did use a separate class for the Operators
 * in order to reduce the number of duplicate properties and methods.
 *
 */

class SynthModel : public QObject {
    Q_OBJECT

    // Global info
    Q_PROPERTY(bool isConnected READ isConnected)
    Q_PROPERTY(int patchNumber READ patchNumber WRITE setPatchNumber NOTIFY patchNumberChanged)
    Q_PROPERTY(QString patchName READ patchName WRITE setPatchName NOTIFY patchNameChanged)

    // Common
    Q_PROPERTY(int masterPitchBendUp READ masterPitchBendUp WRITE setMasterPitchBendUp NOTIFY masterPitchBendUpChanged)
    Q_PROPERTY(int masterPitchBendDown READ masterPitchBendDown WRITE setMasterPitchBendDown NOTIFY masterPitchBendDownChanged)
    Q_PROPERTY(int masterTranspose READ masterTranspose WRITE setMasterTranspose NOTIFY masterTransposeChanged)
    Q_PROPERTY(int masterVolume READ masterVolume WRITE setMasterVolume NOTIFY masterVolumeChanged)
    Q_PROPERTY(int outputLevel READ outputLevel WRITE setOutputLevel NOTIFY outputLevelChanged)
    Q_PROPERTY(int masterPan READ masterPan WRITE setMasterPan NOTIFY masterPanChanged)
    Q_PROPERTY(int masterLegato READ masterLegato WRITE setMasterLegato NOTIFY masterLegatoChanged)
    Q_PROPERTY(int masterTuning READ masterTuning WRITE setMasterTuning NOTIFY masterTuningChanged)
    Q_PROPERTY(int masterVelocityOffset READ masterVelocityOffset WRITE setMasterVelocityOffset NOTIFY masterVelocityOffsetChanged)

    // Operators
    Q_PROPERTY(QList<QObject *> fmOperators READ fmOperators)
    Q_PROPERTY(int operatorSync READ operatorSync WRITE setOperatorSync NOTIFY operatorSyncChanged)
    Q_PROPERTY(int operatorMode READ operatorMode WRITE setOperatorMode NOTIFY operatorModeChanged)
    Q_PROPERTY(int envelopeLoop READ envelopeLoop WRITE setEnvelopeLoop NOTIFY envelopeLoopChanged)
    Q_PROPERTY(int envelopeLoopSegment READ envelopeLoopSegment WRITE setEnvelopeLoopSegment NOTIFY envelopeLoopSegmentChanged)
    Q_PROPERTY(int envelopeRestart READ envelopeRestart WRITE setEnvelopeRestart NOTIFY envelopeRestartChanged)

    // Pitch EG
    Q_PROPERTY(int pitchEG_L0 READ pitchEG_L0 WRITE setPitchEG_L0 NOTIFY pitchEG_L0Changed)
    Q_PROPERTY(int pitchEG_L1 READ pitchEG_L1 WRITE setPitchEG_L1 NOTIFY pitchEG_L1Changed)
    Q_PROPERTY(int pitchEG_L2 READ pitchEG_L2 WRITE setPitchEG_L2 NOTIFY pitchEG_L2Changed)
    Q_PROPERTY(int pitchEG_L3 READ pitchEG_L3 WRITE setPitchEG_L3 NOTIFY pitchEG_L3Changed)
    Q_PROPERTY(int pitchEG_L4 READ pitchEG_L4 WRITE setPitchEG_L4 NOTIFY pitchEG_L4Changed)
    Q_PROPERTY(int pitchEG_L5 READ pitchEG_L5 WRITE setPitchEG_L5 NOTIFY pitchEG_L5Changed)
    Q_PROPERTY(int pitchEG_R0 READ pitchEG_R0 WRITE setPitchEG_R0 NOTIFY pitchEG_R0Changed)
    Q_PROPERTY(int pitchEG_R1 READ pitchEG_R1 WRITE setPitchEG_R1 NOTIFY pitchEG_R1Changed)
    Q_PROPERTY(int pitchEG_R2 READ pitchEG_R2 WRITE setPitchEG_R2 NOTIFY pitchEG_R2Changed)
    Q_PROPERTY(int pitchEG_R3 READ pitchEG_R3 WRITE setPitchEG_R3 NOTIFY pitchEG_R3Changed)
    Q_PROPERTY(int pitchEG_R4 READ pitchEG_R4 WRITE setPitchEG_R4 NOTIFY pitchEG_R4Changed)
    Q_PROPERTY(int pitchEG_R5 READ pitchEG_R5 WRITE setPitchEG_R5 NOTIFY pitchEG_R5Changed)
    Q_PROPERTY(int pitchEG_Range READ pitchEG_Range WRITE setPitchEG_Range NOTIFY pitchEG_RangeChanged)
    Q_PROPERTY(int pitchEG_Velocity READ pitchEG_Velocity WRITE setPitchEG_Velocity NOTIFY pitchEG_VelocityChanged)
    Q_PROPERTY(int pitchEG_RateKey READ pitchEG_RateKey WRITE setPitchEG_RateKey NOTIFY pitchEG_RateKeyChanged)

    // LFO
    Q_PROPERTY(int lfoDepthPitch READ lfoDepthPitch WRITE setLFODepthPitch NOTIFY lfoDepthPitchChanged)
    Q_PROPERTY(int lfoDepthAmplitude READ lfoDepthAmplitude WRITE setLFODepthAmplitude NOTIFY lfoDepthAmplitudeChanged)
    Q_PROPERTY(int lfoSpeed READ lfoSpeed WRITE setLFOSpeed NOTIFY lfoSpeedChanged)
    Q_PROPERTY(int lfoSync READ lfoSync WRITE setLFOSync NOTIFY lfoSyncChanged)
    Q_PROPERTY(int lfoWave READ lfoWave WRITE setLFOWave NOTIFY lfoWaveChanged)
    Q_PROPERTY(int lfoFade READ lfoFade WRITE setLFOFade NOTIFY lfoFadeChanged)

    // Modulation
    Q_PROPERTY(int modPitchLFOWheel READ modPitchLFOWheel WRITE setModPitchLFOWheel NOTIFY modPitchLFOWheelChanged)
    Q_PROPERTY(int modPitchLFOFoot READ modPitchLFOFoot WRITE setModPitchLFOFoot NOTIFY modPitchLFOFootChanged)
    Q_PROPERTY(int modAmpLFOAftertouch READ modAmpLFOAftertouch WRITE setModAmpLFOAftertouch NOTIFY modAmpLFOAftertouchChanged)
    Q_PROPERTY(int modAmpLFOWheel READ modAmpLFOWheel WRITE setModAmpLFOWheel NOTIFY modAmpLFOWheelChanged)
    Q_PROPERTY(int modAmpLFOBreath READ modAmpLFOBreath WRITE setModAmpLFOBreath NOTIFY modAmpLFOBreathChanged)
    Q_PROPERTY(int modAmpLFOFoot READ modAmpLFOFoot WRITE setModAmpLFOFoot NOTIFY modAmpLFOFootChanged)
    Q_PROPERTY(int modPitchLFOAftertouch READ modPitchLFOAftertouch WRITE setModPitchLFOAftertouch NOTIFY modPitchLFOAftertouchChanged)
    Q_PROPERTY(int modPitchLFOBreath READ modPitchLFOBreath WRITE setModPitchLFOBreath NOTIFY modPitchLFOBreathChanged)
    Q_PROPERTY(int modEnvelopeBiasAftertouch READ modEnvelopeBiasAftertouch WRITE setModEnvelopeBiasAftertouch NOTIFY modEnvelopeBiasAftertouchChanged)
    Q_PROPERTY(int modEnvelopeBiasWheel READ modEnvelopeBiasWheel WRITE setModEnvelopeBiasWheel NOTIFY modEnvelopeBiasWheelChanged)
    Q_PROPERTY(int modEnvelopeBiasBreath READ modEnvelopeBiasBreath WRITE setModEnvelopeBiasBreath NOTIFY modEnvelopeBiasBreathChanged)
    Q_PROPERTY(int modEnvelopeBiasFoot READ modEnvelopeBiasFoot WRITE setModEnvelopeBiasFoot NOTIFY modEnvelopeBiasFootChanged)
    Q_PROPERTY(int modPitchAftertouch READ modPitchAftertouch WRITE setModPitchAftertouch NOTIFY modPitchAftertouchChanged)
    Q_PROPERTY(int modPitchBreath READ modPitchBreath WRITE setModPitchBreath NOTIFY modPitchBreathChanged)
    Q_PROPERTY(int modPitchFoot READ modPitchFoot WRITE setModPitchFoot NOTIFY modPitchFootChanged)
    Q_PROPERTY(int modPitchRandom READ modPitchRandom WRITE setModPitchRandom NOTIFY modPitchRandomChanged)

    // Portamento
    Q_PROPERTY(int portamentoMode READ portamentoMode WRITE setPortamentoMode NOTIFY portamentoModeChanged)
    Q_PROPERTY(int portamentoTime READ portamentoTime WRITE setPortamentoTime NOTIFY portamentoTimeChanged)

    // Arpeggiator
    Q_PROPERTY(int arpeggiatorMode READ arpeggiatorMode WRITE setArpeggiatorMode NOTIFY arpeggiatorModeChanged)    
    Q_PROPERTY(int arpeggiatorTempo READ arpeggiatorTempo WRITE setArpeggiatorTempo NOTIFY arpeggiatorTempoChanged)
    Q_PROPERTY(int arpeggiatorTempoMultiplier READ arpeggiatorTempoMultiplier WRITE setArpeggiatorTempoMultiplier NOTIFY arpeggiatorTempoMultiplierChanged)
    Q_PROPERTY(int arpeggiatorOctaveRange READ arpeggiatorOctaveRange WRITE setArpeggiatorOctaveRange NOTIFY arpeggiatorOctaveRangeChanged)

    // Filter
    Q_PROPERTY(int filterLoCutoff READ filterLoCutoff WRITE setFilterLoCutoff NOTIFY filterLoCutoffChanged)
    Q_PROPERTY(int filterHiCutoff READ filterHiCutoff WRITE setFilterHiCutoff NOTIFY filterHiCutoffChanged)

    // FX: Bit crush and decimator
    Q_PROPERTY(int fxBitCrushDepth READ fxBitCrushDepth WRITE setFxBitCrushDepth NOTIFY fxBitCrushDepthChanged)
    Q_PROPERTY(int fxDecimator READ fxDecimator WRITE setFxDecimator NOTIFY fxDecimatorChanged)

    // FX: Chorus
    Q_PROPERTY(int fxChorusDry READ fxChorusDry WRITE setFxChorusDry NOTIFY fxChorusDryChanged)
    Q_PROPERTY(int fxChorusWet READ fxChorusWet WRITE setFxChorusWet NOTIFY fxChorusWetChanged)
    Q_PROPERTY(int fxChorusMode READ fxChorusMode WRITE setFxChorusMode NOTIFY fxChorusModeChanged)
    Q_PROPERTY(int fxChorusSpeed READ fxChorusSpeed WRITE setFxChorusSpeed NOTIFY fxChorusSpeedChanged)
    Q_PROPERTY(int fxChorusDepth READ fxChorusDepth WRITE setFxChorusDepth NOTIFY fxChorusDepthChanged)
    Q_PROPERTY(int fxChorusFeedback READ fxChorusFeedback WRITE setFxChorusFeedback NOTIFY fxChorusFeedbackChanged)
    Q_PROPERTY(int fxChorusPhase READ fxChorusPhase WRITE setFxChorusPhase NOTIFY fxChorusPhaseChanged)

    // FX: Phaser
    Q_PROPERTY(int fxPhaserDry READ fxPhaserDry WRITE setFxPhaserDry NOTIFY fxPhaserDryChanged)
    Q_PROPERTY(int fxPhaserWet READ fxPhaserWet WRITE setFxPhaserWet NOTIFY fxPhaserWetChanged)
    Q_PROPERTY(int fxPhaserMode READ fxPhaserMode WRITE setFxPhaserMode NOTIFY fxPhaserModeChanged)
    Q_PROPERTY(int fxPhaserSpeed READ fxPhaserSpeed WRITE setFxPhaserSpeed NOTIFY fxPhaserSpeedChanged)
    Q_PROPERTY(int fxPhaserDepth READ fxPhaserDepth WRITE setFxPhaserDepth NOTIFY fxPhaserDepthChanged)
    Q_PROPERTY(int fxPhaserFeedback READ fxPhaserFeedback WRITE setFxPhaserFeedback NOTIFY fxPhaserFeedbackChanged)
    Q_PROPERTY(int fxPhaserPhase READ fxPhaserPhase WRITE setFxPhaserPhase NOTIFY fxPhaserPhaseChanged)
    Q_PROPERTY(int fxPhaserOffset READ fxPhaserOffset WRITE setFxPhaserOffset NOTIFY fxPhaserOffsetChanged)
    Q_PROPERTY(int fxPhaserStages READ fxPhaserStages WRITE setFxPhaserStages NOTIFY fxPhaserStagesChanged)

    // FX: Delay
    Q_PROPERTY(int fxDelayDry READ fxDelayDry WRITE setFxDelayDry NOTIFY fxDelayDryChanged)
    Q_PROPERTY(int fxDelayWet READ fxDelayWet WRITE setFxDelayWet NOTIFY fxDelayWetChanged)
    Q_PROPERTY(int fxDelayMode READ fxDelayMode WRITE setFxDelayMode NOTIFY fxDelayModeChanged)
    Q_PROPERTY(int fxDelayTime READ fxDelayTime WRITE setFxDelayTime NOTIFY fxDelayTimeChanged)
    Q_PROPERTY(int fxDelayFeedback READ fxDelayFeedback WRITE setFxDelayFeedback NOTIFY fxDelayFeedbackChanged)
    Q_PROPERTY(int fxDelayLowPass READ fxDelayLowPass WRITE setFxDelayLowPass NOTIFY fxDelayLowPassChanged)
    Q_PROPERTY(int fxDelayHighPass READ fxDelayHighPass WRITE setFxDelayHighPass NOTIFY fxDelayHighPassChanged)
    Q_PROPERTY(int fxDelayTempo READ fxDelayTempo WRITE setFxDelayTempo NOTIFY fxDelayTempoChanged)
    Q_PROPERTY(int fxDelayMultiplier READ fxDelayMultiplier WRITE setFxDelayMultiplier NOTIFY fxDelayMultiplierChanged)
    Q_PROPERTY(int fxDelayDivider READ fxDelayDivider WRITE setFxDelayDivider NOTIFY fxDelayDividerChanged)

    // FX: Amplitude modulator
    Q_PROPERTY(int fxAMDepth READ fxAMDepth WRITE setFxAMDepth NOTIFY fxAMDepthChanged)
    Q_PROPERTY(int fxAMSpeed READ fxAMSpeed WRITE setFxAMSpeed NOTIFY fxAMSpeedChanged)
    Q_PROPERTY(int fxAMRange READ fxAMRange WRITE setFxAMRange NOTIFY fxAMRangeChanged)
    Q_PROPERTY(int fxAMPhase READ fxAMPhase WRITE setFxAMPhase NOTIFY fxAMPhaseChanged)

    // FX: Reverb
    Q_PROPERTY(int fxReverbDry READ fxReverbDry WRITE setFxReverbDry NOTIFY fxReverbDryChanged)
    Q_PROPERTY(int fxReverbWet READ fxReverbWet WRITE setFxReverbWet NOTIFY fxReverbWetChanged)
    Q_PROPERTY(int fxReverbDecay READ fxReverbDecay WRITE setFxReverbDecay NOTIFY fxReverbDecayChanged)
    Q_PROPERTY(int fxReverbDamp READ fxReverbDamp WRITE setFxReverbDamp NOTIFY fxReverbDampChanged)
    Q_PROPERTY(int fxReverbMode READ fxReverbMode WRITE setFxReverbMode NOTIFY fxReverbModeChanged)

    // FX Routing
    Q_PROPERTY(int fxRoute READ fxRoute WRITE setFxRoute NOTIFY fxRouteChanged)


public:
    explicit SynthModel(QObject *parent = nullptr);

    // Helper functions

    // Read and write the patch buffer.  When writing, an optional parameter allows the current
    // patch to be saved as a new patch
    Q_INVOKABLE bool readPatchBuffer();
    Q_INVOKABLE bool writePatchBuffer(int toPatch=-1);

    // Initialise the patch buffer
    Q_INVOKABLE bool initPatchBuffer();

    // Restore the current patch (revert to saved version)
    Q_INVOKABLE bool reloadPatch();

    // Send operator changes to the synth and update the memory buffer
    Q_INVOKABLE bool updateOperator(XFMOperator *op, bool notify=false);

    // Operator algorithm design:
    // XFM2 allows any operator to be a carrier, and any operator can
    // also modulate any other operator
    Q_INVOKABLE bool isOperatorACarrier(int op);
    Q_INVOKABLE bool makeOperatorACarrier(int op, bool enabled);
    Q_INVOKABLE bool isOperatorModulating(int op, int modulatingop);
    Q_INVOKABLE bool makeOperatorModulate(int op, int modulatingop, bool enabled);

    // Similate a DX7 algorithm by configuring the operators
    // in the same way as the DX7 would, based on info at https://www.futur3soundz.com/da-blog/dx7-algorithms-in-xfm2
    Q_INVOKABLE bool makeDX7Algorithm(int a);


signals:
    void patchNumberChanged();
    void operatorSyncChanged();
    void operatorModeChanged();
    void pitchEG_L0Changed();
    void pitchEG_L1Changed();
    void pitchEG_L2Changed();
    void pitchEG_L3Changed();
    void pitchEG_L4Changed();
    void pitchEG_L5Changed();
    void pitchEG_R0Changed();
    void pitchEG_R1Changed();
    void pitchEG_R2Changed();
    void pitchEG_R3Changed();
    void pitchEG_R4Changed();
    void pitchEG_R5Changed();
    void pitchEG_RangeChanged();
    void pitchEG_VelocityChanged();
    void pitchEG_RateKeyChanged();
    void lfoDepthPitchChanged();
    void lfoDepthAmplitudeChanged();
    void lfoSpeedChanged();
    void lfoSyncChanged();
    void lfoWaveChanged();
    void lfoFadeChanged();
    void modPitchLFOWheelChanged();
    void modPitchLFOBreathChanged();
    void modPitchLFOFootChanged();
    void modAmpLFOAftertouchChanged();
    void modAmpLFOWheelChanged();
    void modAmpLFOBreathChanged();
    void modAmpLFOFootChanged();
    void modPitchLFOAftertouchChanged();
    void masterPitchBendUpChanged();
    void masterPitchBendDownChanged();
    void masterTransposeChanged();
    void masterVolumeChanged();
    void masterPanChanged();
    void masterLegatoChanged();
    void modEnvelopeBiasAftertouchChanged();
    void modEnvelopeBiasWheelChanged();
    void modEnvelopeBiasBreathChanged();
    void modEnvelopeBiasFootChanged();
    void modPitchAftertouchChanged();
    void modPitchBreathChanged();
    void modPitchFootChanged();
    void modPitchRandomChanged();
    void portamentoModeChanged();
    void portamentoTimeChanged();
    void masterVelocityOffsetChanged();
    void envelopeLoopChanged();
    void envelopeLoopSegmentChanged();
    void envelopeRestartChanged();
    void masterTuningChanged();
    void operatorHasChanged();
    void outputLevelChanged();
    void arpeggiatorModeChanged();
    void arpeggiatorTempoChanged();
    void arpeggiatorTempoMultiplierChanged();
    void arpeggiatorOctaveRangeChanged();
    void fxBitCrushDepthChanged();
    void fxDecimatorChanged();
    void filterLoCutoffChanged();
    void filterHiCutoffChanged();
    void fxChorusDryChanged();
    void fxChorusWetChanged();
    void fxChorusModeChanged();
    void fxChorusSpeedChanged();
    void fxChorusDepthChanged();
    void fxChorusFeedbackChanged();
    void fxChorusPhaseChanged();
    void fxPhaserDryChanged();
    void fxPhaserWetChanged();
    void fxPhaserModeChanged();
    void fxPhaserSpeedChanged();
    void fxPhaserDepthChanged();
    void fxPhaserOffsetChanged();
    void fxPhaserStagesChanged();
    void fxPhaserFeedbackChanged();
    void fxPhaserPhaseChanged();
    void fxDelayDryChanged();
    void fxDelayWetChanged();
    void fxDelayModeChanged();
    void fxDelayTimeChanged();
    void fxDelayFeedbackChanged();
    void fxDelayLowPassChanged();
    void fxDelayHighPassChanged();
    void fxDelayTempoChanged();
    void fxDelayMultiplierChanged();
    void fxDelayDividerChanged();
    void fxAMDepthChanged();
    void fxAMSpeedChanged();
    void fxAMRangeChanged();
    void fxAMPhaseChanged();
    void fxReverbDryChanged();
    void fxReverbWetChanged();
    void fxReverbDecayChanged();
    void fxReverbDampChanged();
    void fxReverbModeChanged();
    void fxRouteChanged();
    void patchNameChanged();

protected:
    bool isConnected() const;

    int patchNumber() const;
    void setPatchNumber(int p);

    int operatorSync();
    void setOperatorSync(int v);

    int operatorMode();
    void setOperatorMode(int v);

    int pitchEG_L0();
    void setPitchEG_L0(int f);

    int pitchEG_L1();
    void setPitchEG_L1(int f);

    int pitchEG_L2();
    void setPitchEG_L2(int f);

    int pitchEG_L3();
    void setPitchEG_L3(int f);

    int pitchEG_L4();
    void setPitchEG_L4(int f);

    int pitchEG_L5();
    void setPitchEG_L5(int f);

    int pitchEG_R0();
    void setPitchEG_R0(int f);

    int pitchEG_R1();
    void setPitchEG_R1(int f);

    int pitchEG_R2();
    void setPitchEG_R2(int f);

    int pitchEG_R3();
    void setPitchEG_R3(int f);

    int pitchEG_R4();
    void setPitchEG_R4(int f);

    int pitchEG_R5();
    void setPitchEG_R5(int f);

    int pitchEG_Range();
    void setPitchEG_Range(int f);

    int pitchEG_Velocity();
    void setPitchEG_Velocity(int f);

    int pitchEG_RateKey();
    void setPitchEG_RateKey(int f);

    int lfoDepthPitch();
    void setLFODepthPitch(int f);

    int lfoDepthAmplitude();
    void setLFODepthAmplitude(int v);

    int lfoSpeed();
    void setLFOSpeed(int v);

    int lfoSync();
    void setLFOSync(int v);

    int lfoWave();
    void setLFOWave(int v);

    int lfoFade();
    void setLFOFade(int v);

    int modPitchLFOWheel();
    void setModPitchLFOWheel(int v);

    int modAmpLFOAftertouch();
    void setModAmpLFOAftertouch(int v);

    int modPitchLFOBreath();
    void setModPitchLFOBreath(int v);

    int modPitchLFOFoot();
    void setModPitchLFOFoot(int v);

    int modAmpLFOWheel();
    void setModAmpLFOWheel(int v);

    int modAmpLFOBreath();
    void setModAmpLFOBreath(int v);

    int modAmpLFOFoot();
    void setModAmpLFOFoot(int v);

    int modPitchLFOAftertouch();
    void setModPitchLFOAftertouch(int v);

    int masterPitchBendUp();
    void setMasterPitchBendUp(int v);

    int masterPitchBendDown();
    void setMasterPitchBendDown(int v);

    int masterTranspose();
    void setMasterTranspose(int v);

    int masterVolume();
    void setMasterVolume(int v);

    int masterPan();
    void setMasterPan(int v);

    int masterLegato();
    void setMasterLegato(int v);

    int masterVelocityOffset();
    void setMasterVelocityOffset(int v);

    int masterTuning();
    void setMasterTuning(int v);

    int modEnvelopeBiasAftertouch();
    void setModEnvelopeBiasAftertouch(int v);

    int modEnvelopeBiasWheel();
    void setModEnvelopeBiasWheel(int v);

    int modEnvelopeBiasBreath();
    void setModEnvelopeBiasBreath(int v);

    int modEnvelopeBiasFoot();
    void setModEnvelopeBiasFoot(int v);

    int modPitchAftertouch();
    void setModPitchAftertouch(int v);

    int modPitchBreath();
    void setModPitchBreath(int v);

    int modPitchFoot();
    void setModPitchFoot(int v);

    int modPitchRandom();
    void setModPitchRandom(int v);

    int portamentoMode();
    void setPortamentoMode(int v);

    int portamentoTime();
    void setPortamentoTime(int v);

    int envelopeLoop();
    void setEnvelopeLoop(int v);

    int envelopeLoopSegment();
    void setEnvelopeLoopSegment(int v);

    int envelopeRestart();
    void setEnvelopeRestart(int v);

    int outputLevel();
    void setOutputLevel(int v);

    int arpeggiatorMode();
    void setArpeggiatorMode(int v);

    int arpeggiatorTempo();
    void setArpeggiatorTempo(int v);

    int arpeggiatorTempoMultiplier();
    void setArpeggiatorTempoMultiplier(int v);

    int arpeggiatorOctaveRange();
    void setArpeggiatorOctaveRange(int v);

    int fxBitCrushDepth();
    void setFxBitCrushDepth(int v);

    int fxDecimator();
    void setFxDecimator(int v);

    int filterLoCutoff();
    void setFilterLoCutoff(int v);

    int filterHiCutoff();
    void setFilterHiCutoff(int v);

    int fxChorusDry();
    void setFxChorusDry(int v);

    int fxChorusWet();
    void setFxChorusWet(int v);

    int fxChorusMode();
    void setFxChorusMode(int v);

    int fxChorusSpeed();
    void setFxChorusSpeed(int v);

    int fxChorusDepth();
    void setFxChorusDepth(int v);

    int fxChorusFeedback();
    void setFxChorusFeedback(int v);

    int fxChorusPhase();
    void setFxChorusPhase(int v);

    int fxPhaserDry();
    void setFxPhaserDry(int v);

    int fxPhaserWet();
    void setFxPhaserWet(int v);

    int fxPhaserMode();
    void setFxPhaserMode(int v);

    int fxPhaserSpeed();
    void setFxPhaserSpeed(int v);

    int fxPhaserDepth();
    void setFxPhaserDepth(int v);

    int fxPhaserOffset();
    void setFxPhaserOffset(int v);

    int fxPhaserStages();
    void setFxPhaserStages(int v);

    int fxPhaserFeedback();
    void setFxPhaserFeedback(int v);

    int fxPhaserPhase();
    void setFxPhaserPhase(int v);

    int fxDelayDry();
    void setFxDelayDry(int v);

    int fxDelayWet();
    void setFxDelayWet(int v);

    int fxDelayMode();
    void setFxDelayMode(int v);

    int fxDelayTime();
    void setFxDelayTime(int v);

    int fxDelayFeedback();
    void setFxDelayFeedback(int v);

    int fxDelayLowPass();
    void setFxDelayLowPass(int v);

    int fxDelayHighPass();
    void setFxDelayHighPass(int v);

    int fxDelayTempo();
    void setFxDelayTempo(int v);

    int fxDelayMultiplier();
    void setFxDelayMultiplier(int v);

    int fxDelayDivider();
    void setFxDelayDivider(int v);

    int fxAMDepth();
    void setFxAMDepth(int v);

    int fxAMSpeed();
    void setFxAMSpeed(int v);

    int fxAMRange();
    void setFxAMRange(int v);

    int fxAMPhase();
    void setFxAMPhase(int v);

    int fxReverbDry();
    void setFxReverbDry(int v);

    int fxReverbWet();
    void setFxReverbWet(int v);

    int fxReverbDecay();
    void setFxReverbDecay(int v);

    int fxReverbDamp();
    void setFxReverbDamp(int v);

    int fxReverbMode();
    void setFxReverbMode(int v);

    int fxRoute();
    void setFxRoute(int v);

    void loadPatchNames();
    void savePatchNames();

    QString patchName();
    void setPatchName(const QString &str);

    unsigned char readMemoryLocation(XFM2Parameter offset, bool useCache=true);
    bool writeMemoryLocation(XFM2Parameter offset, unsigned char data);

    QList<QObject *> fmOperators();

private:
    unsigned char               m_xfm2[512];        // Memory buffer
    std::vector<std::string>    m_patchNames;       // XFM2 hardware doesn't hold patch names, so we use the app to store them
    QSerialPort *               m_port;             // USB serial port connection
    int                         m_patchnumber;      // Current patch number
    bool                        m_isconnected;      // True if the hardware is connected
    bool                        m_initialised;      // True if the model is initialised and the memory buffer has been read
    std::string                 m_patchNameBuffer;  // The current patch name
};

#endif // SYNTHMODEL_H
