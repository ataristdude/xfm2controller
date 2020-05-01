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

#ifndef XFMOPERATOR_H
#define XFMOPERATOR_H

#include <QObject>
#include <QString>
#include "xfm2.h"

/*
 * This is a class for a single XFM2 Operator
 * It makes it easy to manipulate the operator's parameters
 */

class XFMOperator : public QObject {
    Q_OBJECT

    // The operator number keeps track of which operator this is
    Q_PROPERTY(int operatorNumber READ operatorNumber WRITE setOperatorNumber NOTIFY operatorNumberChanged)

    // Algorithm, feedback and frequency ratio
    Q_PROPERTY(int algorithm READ algorithm WRITE setAlgorithm NOTIFY algorithmChanged)
    Q_PROPERTY(int feedback READ feedback WRITE setFeedback NOTIFY feedbackChanged)
    Q_PROPERTY(int ratio READ ratio WRITE setRatio NOTIFY ratioChanged)
    Q_PROPERTY(int ratioFine READ ratioFine WRITE setRatioFine NOTIFY ratioFineChanged)

    // Waveform and phase
    Q_PROPERTY(int wave1 READ wave1 WRITE setWave1 NOTIFY wave1Changed)
    Q_PROPERTY(int wave2 READ wave2 WRITE setWave2 NOTIFY wave2Changed)
    Q_PROPERTY(int oscillatorMode READ oscillatorMode WRITE setOscillatorMode NOTIFY oscillatorModeChanged)
    Q_PROPERTY(int oscillatorRatio READ oscillatorRatio WRITE setOscillatorRatio NOTIFY oscillatorRatioChanged)
    Q_PROPERTY(int phase READ phase WRITE setPhase NOTIFY phaseChanged)

    // Fine tuning
    Q_PROPERTY(int fine READ fine WRITE setFine NOTIFY fineChanged)

    // Level
    Q_PROPERTY(int level READ level WRITE setLevel NOTIFY levelChanged)
    Q_PROPERTY(int levelLeft READ levelLeft WRITE setLevelLeft NOTIFY levelLeftChanged)
    Q_PROPERTY(int levelRight READ levelRight WRITE setLevelRight NOTIFY levelRightChanged)

    // Keyboard control.  The breakpoint sets the split between "left" (lower) and "right" (upper)
    Q_PROPERTY(int velocitySensitivity READ velocitySensitivity WRITE setVelocitySensitivity NOTIFY velocitySensitivityChanged)
    Q_PROPERTY(int keyboardBreakpoint READ keyboardBreakpoint WRITE setKeyboardBreakpoint NOTIFY keyboardBreakpointChanged)
    Q_PROPERTY(int keyboardScaleLeft READ keyboardScaleLeft WRITE setKeyboardScaleLeft NOTIFY keyboardScaleLeftChanged)
    Q_PROPERTY(int keyboardScaleRight READ keyboardScaleRight WRITE setKeyboardScaleRight NOTIFY keyboardScaleRightChanged)
    Q_PROPERTY(int keyboardCurveLeft READ keyboardCurveLeft WRITE setKeyboardCurveLeft NOTIFY keyboardCurveLeftChanged)
    Q_PROPERTY(int keyboardCurveRight READ keyboardCurveRight WRITE setKeyboardCurveRight NOTIFY keyboardCurveRightChanged)
    Q_PROPERTY(int rateKey READ rateKey WRITE setRateKey NOTIFY rateKeyChanged)

    // Levels 0-5
    Q_PROPERTY(int L0 READ L0 WRITE setL0 NOTIFY L0Changed)
    Q_PROPERTY(int L1 READ L1 WRITE setL1 NOTIFY L1Changed)
    Q_PROPERTY(int L2 READ L2 WRITE setL2 NOTIFY L2Changed)
    Q_PROPERTY(int L3 READ L3 WRITE setL3 NOTIFY L3Changed)
    Q_PROPERTY(int L4 READ L4 WRITE setL4 NOTIFY L4Changed)
    Q_PROPERTY(int L5 READ L5 WRITE setL5 NOTIFY L5Changed)

    // Rates 0-5
    Q_PROPERTY(int R0 READ R0 WRITE setR0 NOTIFY R0Changed)
    Q_PROPERTY(int R1 READ R1 WRITE setR1 NOTIFY R1Changed)
    Q_PROPERTY(int R2 READ R2 WRITE setR2 NOTIFY R2Changed)
    Q_PROPERTY(int R3 READ R3 WRITE setR3 NOTIFY R3Changed)
    Q_PROPERTY(int R4 READ R4 WRITE setR4 NOTIFY R4Changed)
    Q_PROPERTY(int R5 READ R5 WRITE setR5 NOTIFY R5Changed)

    // Modulation
    Q_PROPERTY(int amplitudeModulationSensitivity READ amplitudeModulationSensitivity WRITE setAmplitudeModulationSensitivity NOTIFY amplitudeModulationSensitivityChanged)
    Q_PROPERTY(int pitchModulationSensitivity READ pitchModulationSensitivity WRITE setPitchModulationSensitivity NOTIFY pitchModulationSensitivityChanged)

public:
    explicit XFMOperator(QObject *parent = nullptr);


signals:
    void operatorNumberChanged();
    void algorithmChanged();
    void feedbackChanged();
    void ratioChanged();
    void ratioFineChanged();
    void fineChanged();
    void levelChanged();
    void levelLeftChanged();
    void levelRightChanged();
    void velocitySensitivityChanged();
    void keyboardBreakpointChanged();
    void keyboardScaleLeftChanged();
    void keyboardScaleRightChanged();
    void keyboardCurveLeftChanged();
    void keyboardCurveRightChanged();
    void L0Changed();
    void L1Changed();
    void L2Changed();
    void L3Changed();
    void L4Changed();
    void L5Changed();
    void R0Changed();
    void R1Changed();
    void R2Changed();
    void R3Changed();
    void R4Changed();
    void R5Changed();
    void rateKeyChanged();
    void amplitudeModulationSensitivityChanged();
    void pitchModulationSensitivityChanged();
    void wave1Changed();
    void wave2Changed();
    void oscillatorModeChanged();
    void oscillatorRatioChanged();
    void phaseChanged();

public:
    int operatorNumber() const;
    void setOperatorNumber(int n);

    int algorithm() const;
    void setAlgorithm(int a);

    int feedback() const;
    void setFeedback(int f);

    int ratio() const;
    void setRatio(int v);

    int ratioFine() const;
    void setRatioFine(int v);

    int fine() const;
    void setFine(int v);

    int level() const;
    void setLevel(int v);

    int levelLeft() const;
    void setLevelLeft(int v);

    int levelRight() const;
    void setLevelRight(int v);

    int velocitySensitivity() const;
    void setVelocitySensitivity(int v);

    int keyboardBreakpoint() const;
    void setKeyboardBreakpoint(int v);

    int keyboardScaleLeft() const;
    void setKeyboardScaleLeft(int v);

    int keyboardScaleRight() const;
    void setKeyboardScaleRight(int f);

    int keyboardCurveLeft() const;
    void setKeyboardCurveLeft(int f);

    int keyboardCurveRight() const;
    void setKeyboardCurveRight(int f);

    // Envelope
    int L0() const;
    void setL0(int f);

    int L1() const;
    void setL1(int f);

    int L2() const;
    void setL2(int f);

    int L3() const;
    void setL3(int f);

    int L4() const;
    void setL4(int f);

    int L5() const;
    void setL5(int f);

    int R0() const;
    void setR0(int f);

    int R1() const;
    void setR1(int f);

    int R2() const;
    void setR2(int f);

    int R3() const;
    void setR3(int f);

    int R4() const;
    void setR4(int f);

    int R5() const;
    void setR5(int f);

    int rateKey() const;
    void setRateKey(int f);

    int amplitudeModulationSensitivity() const;
    void setAmplitudeModulationSensitivity(int v);

    int pitchModulationSensitivity() const;
    void setPitchModulationSensitivity(int v);

    int wave1() const;
    void setWave1(int v);

    int wave2() const;
    void setWave2(int v);

    int oscillatorMode() const;
    void setOscillatorMode(int v);

    int oscillatorRatio() const;
    void setOscillatorRatio(int v);

    int phase() const;
    void setPhase(int v);

private:
    int m_operator;
    unsigned char m_algorithm;
    unsigned char m_feedback;
    unsigned char m_ratio;
    unsigned char m_ratiofine;
    unsigned char m_fine;
    unsigned char m_level;
    unsigned char m_levelLeft;
    unsigned char m_levelRight;
    unsigned char m_velocitysensitivity;
    unsigned char m_keyboardbreakpoint;
    unsigned char m_keyboardscaleleft;
    unsigned char m_keyboardscaleright;
    unsigned char m_keyboardcurveleft;
    unsigned char m_keyboardcurveright;
    unsigned char m_l0;
    unsigned char m_l1;
    unsigned char m_l2;
    unsigned char m_l3;
    unsigned char m_l4;
    unsigned char m_l5;
    unsigned char m_r0;
    unsigned char m_r1;
    unsigned char m_r2;
    unsigned char m_r3;
    unsigned char m_r4;
    unsigned char m_r5;
    unsigned char m_ratekey;
    unsigned char m_ams;
    unsigned char m_pms;
    unsigned char m_wave1;
    unsigned char m_wave2;
    unsigned char m_wmode;
    unsigned char m_wratio;
    unsigned char m_phase;
};


#endif // XFMOPERATOR_H
