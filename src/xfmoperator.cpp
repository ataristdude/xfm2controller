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

#include <QDebug>
#include <string.h>
#include "xfmoperator.h"
#include "SynthModel.h"

/* This is the implementation of a single FM operator for XFM2
 * Really the class just holds a set of properties and gives
 * them nice names that make it easy to use.  The main SynthModel
 * actually talks to the hardware
 */

XFMOperator::XFMOperator(QObject *parent) : QObject(parent)
{
    m_operator=0;
    m_algorithm=0;
    m_ratio=0;
    m_ratiofine=0;
    m_fine=0;
    m_level=0;
    m_levelLeft=0;
    m_levelRight=0;
    m_velocitysensitivity=0;
    m_keyboardbreakpoint=0;
    m_keyboardscaleleft=0;
    m_keyboardscaleright=0;
    m_keyboardcurveleft=0;
    m_keyboardcurveright=0;
    m_l0=0;
    m_l1=0;
    m_l2=0;
    m_l3=0;
    m_l4=0;
    m_l5=0;
    m_r0=0;
    m_r1=0;
    m_r2=0;
    m_r3=0;
    m_r4=0;
    m_r5=0;
    m_ratekey=0;
    m_ams=0;
    m_pms=0;
    m_wave1=0;
    m_wave2=0;
    m_wmode=0;
    m_wratio=0;
    m_phase=0;
}

int XFMOperator::operatorNumber() const
{
    return m_operator;
}

void XFMOperator::setOperatorNumber(int n)
{
    if (n != m_operator) {
        m_operator=n;
        emit operatorNumberChanged();
    }
}

int XFMOperator::algorithm() const
{
    return static_cast<int>(m_algorithm);
}

void XFMOperator::setAlgorithm(int a)
{
    unsigned char aa=static_cast<unsigned char>(a);
    if (aa != m_algorithm) {
        m_algorithm=aa;
        emit algorithmChanged();
    }
}

int XFMOperator::feedback() const
{
    return static_cast<int>(m_feedback);
}

void XFMOperator::setFeedback(int f)
{
    unsigned char ff=static_cast<unsigned char>(f);
    if (ff != m_feedback) {
        m_feedback=ff;
        emit feedbackChanged();
    }
}

int XFMOperator::ratio() const
{
    return static_cast<int>(m_ratio);
}

void XFMOperator::setRatio(int f)
{
    unsigned char ff=static_cast<unsigned char>(f);
    if (ff != m_ratio) {
        m_ratio=ff;
        emit ratioChanged();
    }
}

int XFMOperator::ratioFine() const
{
    return static_cast<int>(m_ratiofine);
}

void XFMOperator::setRatioFine(int f)
{
    unsigned char ff=static_cast<unsigned char>(f);
    if (ff != m_ratiofine) {
        m_ratiofine=ff;
        emit ratioFineChanged();
    }
}

int XFMOperator::fine() const
{
    return static_cast<int>(m_fine);
}

void XFMOperator::setFine(int f)
{
    unsigned char ff=static_cast<unsigned char>(f);
    if (ff != m_fine) {
        m_fine=ff;
        emit fineChanged();
    }
}

int XFMOperator::level() const
{
    return static_cast<int>(m_level);
}

void XFMOperator::setLevel(int f)
{
    unsigned char ff=static_cast<unsigned char>(f);
    if (ff != m_level) {
        m_level=ff;
        emit levelChanged();
    }
}

int XFMOperator::levelLeft() const
{
    return static_cast<int>(m_levelLeft);
}

void XFMOperator::setLevelLeft(int f)
{
    unsigned char ff=static_cast<unsigned char>(f);
    if (ff != m_levelLeft) {
        m_levelLeft=ff;
        emit levelLeftChanged();
    }
}

int XFMOperator::levelRight() const
{
    return static_cast<int>(m_levelRight);
}

void XFMOperator::setLevelRight(int f)
{
    unsigned char ff=static_cast<unsigned char>(f);
    if (ff != m_levelRight) {
        m_levelRight=ff;
        emit levelRightChanged();
    }
}


int XFMOperator::velocitySensitivity() const
{
    return static_cast<int>(m_velocitysensitivity);
}

void XFMOperator::setVelocitySensitivity(int f)
{
    unsigned char ff=static_cast<unsigned char>(f);
    if (ff != m_velocitysensitivity) {
        m_velocitysensitivity=ff;
        emit velocitySensitivityChanged();
    }
}

int XFMOperator::keyboardBreakpoint() const
{
    return static_cast<int>(m_keyboardbreakpoint);
}

void XFMOperator::setKeyboardBreakpoint(int f)
{
    unsigned char ff=static_cast<unsigned char>(f);
    if (ff != m_keyboardbreakpoint) {
        m_keyboardbreakpoint=ff;
        emit keyboardBreakpointChanged();
    }
}

int XFMOperator::keyboardScaleLeft() const
{
    return static_cast<int>(m_keyboardscaleleft);
}

void XFMOperator::setKeyboardScaleLeft(int f)
{
    unsigned char ff=static_cast<unsigned char>(f);
    if (ff != m_keyboardscaleleft) {
        m_keyboardscaleleft=ff;
        emit keyboardScaleLeftChanged();
    }
}

int XFMOperator::keyboardScaleRight() const
{
    return static_cast<int>(m_keyboardscaleright);
}

void XFMOperator::setKeyboardScaleRight(int f)
{
    unsigned char ff=static_cast<unsigned char>(f);
    if (ff != m_keyboardscaleright) {
        m_keyboardscaleright=ff;
        emit keyboardScaleRightChanged();
    }
}

int XFMOperator::keyboardCurveLeft() const
{
    return static_cast<int>(m_keyboardcurveleft);
}

void XFMOperator::setKeyboardCurveLeft(int f)
{
    unsigned char ff=static_cast<unsigned char>(f);
    if (ff != m_keyboardcurveleft) {
        m_keyboardcurveleft=ff;
        emit keyboardCurveLeftChanged();
    }
}

int XFMOperator::keyboardCurveRight() const
{
    return static_cast<int>(m_keyboardcurveright);
}

void XFMOperator::setKeyboardCurveRight(int f)
{
    unsigned char ff=static_cast<unsigned char>(f);
    if (ff != m_keyboardcurveright) {
        m_keyboardcurveright=ff;
        emit keyboardCurveRightChanged();
    }
}

int XFMOperator::L0() const
{
    return static_cast<int>(m_l0);
}

void XFMOperator::setL0(int f)
{
    unsigned char ff=static_cast<unsigned char>(f);
    if (ff != m_l0) {
        m_l0=ff;
        emit L0Changed();
    }
}

int XFMOperator::L1() const
{
    return static_cast<int>(m_l1);
}

void XFMOperator::setL1(int f)
{
    unsigned char ff=static_cast<unsigned char>(f);
    if (ff != m_l1) {
        m_l1=ff;
        emit L1Changed();
    }
}

int XFMOperator::L2() const
{
    return static_cast<int>(m_l2);
}

void XFMOperator::setL2(int f)
{
    unsigned char ff=static_cast<unsigned char>(f);
    if (ff != m_l2) {
        m_l2=ff;
        emit L2Changed();
    }
}

int XFMOperator::L3() const
{
    return static_cast<int>(m_l3);
}

void XFMOperator::setL3(int f)
{
    unsigned char ff=static_cast<unsigned char>(f);
    if (ff != m_l3) {
        m_l3=ff;
        emit L3Changed();
    }
}

int XFMOperator::L4() const
{
    return static_cast<int>(m_l4);
}

void XFMOperator::setL4(int f)
{
    unsigned char ff=static_cast<unsigned char>(f);
    if (ff != m_l4) {
        m_l4=ff;
        emit L4Changed();
    }
}

int XFMOperator::L5() const
{
    return static_cast<int>(m_l5);
}

void XFMOperator::setL5(int f)
{
    unsigned char ff=static_cast<unsigned char>(f);
    if (ff != m_l5) {
        m_l5=ff;
        emit L5Changed();
    }
}

int XFMOperator::R0() const
{
    return static_cast<int>(m_r0);
}

void XFMOperator::setR0(int f)
{
    unsigned char ff=static_cast<unsigned char>(f);
    if (ff != m_r0) {
        m_r0=ff;
        emit R0Changed();
    }
}

int XFMOperator::R1() const
{
    return static_cast<int>(m_r1);
}

void XFMOperator::setR1(int f)
{
    unsigned char ff=static_cast<unsigned char>(f);
    if (ff != m_r1) {
        m_r1=ff;
        emit R1Changed();
    }
}

int XFMOperator::R2() const
{
    return static_cast<int>(m_r2);
}

void XFMOperator::setR2(int f)
{
    unsigned char ff=static_cast<unsigned char>(f);
    if (ff != m_r2) {
        m_r2=ff;
        emit R2Changed();
    }
}

int XFMOperator::R3() const
{
    return static_cast<int>(m_r3);
}

void XFMOperator::setR3(int f)
{
    unsigned char ff=static_cast<unsigned char>(f);
    if (ff != m_r3) {
        m_r3=ff;
        emit R3Changed();
    }
}

int XFMOperator::R4() const
{
    return static_cast<int>(m_r4);
}

void XFMOperator::setR4(int f)
{
    unsigned char ff=static_cast<unsigned char>(f);
    if (ff != m_r4) {
        m_r4=ff;
        emit R4Changed();
    }
}

int XFMOperator::R5() const
{
    return static_cast<int>(m_r5);
}

void XFMOperator::setR5(int f)
{
    unsigned char ff=static_cast<unsigned char>(f);
    if (ff != m_r5) {
        m_r5=ff;
        emit R5Changed();
    }
}

int XFMOperator::rateKey() const
{
    return static_cast<int>(m_ratekey);
}

void XFMOperator::setRateKey(int f)
{
    unsigned char ff=static_cast<unsigned char>(f);
    if (ff != m_ratekey) {
        m_ratekey=ff;
        emit rateKeyChanged();
    }
}

int XFMOperator::amplitudeModulationSensitivity() const
{
    return static_cast<int>(m_ams);
}

void XFMOperator::setAmplitudeModulationSensitivity(int v)
{
    unsigned char vv=static_cast<unsigned char>(v);
    if (vv != m_ams) {
        m_ams=vv;
        emit amplitudeModulationSensitivityChanged();
    }
}

int XFMOperator::pitchModulationSensitivity() const
{
    return static_cast<int>(m_pms);
}

void XFMOperator::setPitchModulationSensitivity(int v)
{
    unsigned char vv=static_cast<unsigned char>(v);
    if (vv != m_pms) {
        m_pms=vv;
        emit pitchModulationSensitivityChanged();
    }
}

int XFMOperator::wave1() const
{
    return static_cast<int>(m_wave1);
}

void XFMOperator::setWave1(int v)
{
    unsigned char vv=static_cast<unsigned char>(v);
    if (vv != m_wave1) {
        m_wave1=vv;
        emit wave1Changed();
    }
}


int XFMOperator::wave2() const
{
    return static_cast<int>(m_wave2);
}

void XFMOperator::setWave2(int v)
{
    unsigned char vv=static_cast<unsigned char>(v);
    if (vv != m_wave2) {
        m_wave2=vv;
        emit wave2Changed();
    }
}

int XFMOperator::oscillatorMode() const
{
    return static_cast<int>(m_wmode);
}

void XFMOperator::setOscillatorMode(int v)
{
    unsigned char vv=static_cast<unsigned char>(v);
    if (vv != m_wmode) {
        m_wmode=vv;
        emit oscillatorModeChanged();
    }
}

int XFMOperator::oscillatorRatio() const
{
    return static_cast<int>(m_wratio);
}

void XFMOperator::setOscillatorRatio(int v)
{
    unsigned char vv=static_cast<unsigned char>(v);
    if (vv != m_wratio) {
        m_wratio=vv;
        emit oscillatorRatioChanged();
    }
}

int XFMOperator::phase() const
{
    return static_cast<int>(m_phase);
}

void XFMOperator::setPhase(int v)
{
    unsigned char vv=static_cast<unsigned char>(v);
    if (vv != m_phase) {
        m_phase=vv;
        emit phaseChanged();
    }
}
