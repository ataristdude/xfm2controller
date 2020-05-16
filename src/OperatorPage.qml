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

import QtQuick 2.12
import QtQuick.Controls 2.3
import QtQuick.Extras 1.4
import Xfm.Synth 1.0

Item {
    id: operatorPage
    width: 800
    height: 357

    property int currentOperator: 0
    property XFMOperator fmOperator

    Connections {
        target: synthModel
        onPatchNumberChanged: {
            setOperator(operatorPage.currentOperator);
        }
        onOperatorHasChanged: {
            setOperator(operatorPage.currentOperator);
        }
    }

    function setOperator(opNumber)
    {
        operatorPage.currentOperator=opNumber;

        fmOperator=synthModel.fmOperators[opNumber];

        canvas.requestPaint();

        dialFeedback.value=fmOperator.feedback;
        dialRatio.value=fmOperator.ratio;
        dialRatioFine.value=fmOperator.ratioFine;
        dialFine.value=fmOperator.fine;
        checkKeyTrack.checked=(synthModel.operatorMode & (0x01 << currentOperator)) != 0;
        checkSync.checked=(synthModel.operatorSync & (0x01 << currentOperator)) != 0;
        spinOsc1Mode.value=fmOperator.wave1;
        spinOsc2Mode.value=fmOperator.wave2;
        checkOsc2Enabled.checked=(fmOperator.oscillatorMode & 1) != 0;
        dialOscRatio.value=fmOperator.oscillatorRatio;
        sliderLevel.value=fmOperator.level;
        sliderMixL.value=fmOperator.levelLeft;
        sliderMixR.value=fmOperator.levelRight;
        dialVelocitySens.value=fmOperator.velocitySensitivity;
        sliderAMS.value=fmOperator.amplitudeModulationSensitivity;
        sliderPMS.value=fmOperator.pitchModulationSensitivity;
        spinKeyboardBreakpoint.value=fmOperator.keyboardBreakpoint;
        sliderLDepth.value=fmOperator.keyboardScaleLeft;
        sliderRDepth.value=fmOperator.keyboardScaleRight;
        spinLeftCurve.value=fmOperator.keyboardCurveLeft;
        spinRightCurve.value=fmOperator.keyboardCurveRight;
    }

    Rectangle {
        anchors.fill: parent
        color: "#505050"
    }

    Button {
        id: buttonKeyboard
        x: 720
        y: 190
        width: 71
        height: 40
        text: keyboardPanel.visible ? qsTr("<font color='red'>KBD</font>") : qsTr("KBD")
        onClicked: {
            keyboardPanel.visible=!keyboardPanel.visible;
        }
    }

    CheckBox {
        id: checkOsc2Enabled
        x: 606
        y: 190
        text: qsTr("<font color='white'>Enabled</font>")
        font.pixelSize: 16
        onCheckedChanged: {
            if (checkOsc2Enabled.checked) {
                fmOperator.oscillatorMode=fmOperator.oscillatorMode|1;
            } else {
                if ((fmOperator.oscillatorMode & 1) != 0) {
                    fmOperator.oscillatorMode^=1;
                }
            }
            synthModel.updateOperator(fmOperator);
        }
    }

    SpinBox {
        id: spinOsc1Mode
        x: 457
        y: 140
        to: 7
        onValueChanged: {
            fmOperator.wave1=spinOsc1Mode.value;
            synthModel.updateOperator(fmOperator);
        }
    }

    Slider {
        id: sliderLevel
        x: 647
        y: 241
        width: 40
        height: 87
        to: 255
        orientation: Qt.Vertical
        onValueChanged: {
            fmOperator.level=sliderLevel.value;
            synthModel.updateOperator(fmOperator);
        }
    }

    CheckBox {
        id: checkKeyTrack
        x: 283
        y: 140
        text: qsTr("<font color='white'>Key Track</font>")
        font.pixelSize: 16
        onCheckedChanged: {
            var i=synthModel.operatorMode;
            if (checkKeyTrack.checked) {
                i=i|(0x01 << currentOperator);
            } else {
                if ((i & (0x01 << currentOperator)) != 0) {
                    i=i ^ (0x01 << currentOperator);
                }
            }
            synthModel.operatorMode=i;
        }
    }

    CheckBox {
        id: checkSync
        x: 283
        y: 190
        text: qsTr("<font color='white'>Sync</font>")
        font.pixelSize: 16
        onCheckedChanged: {
            var i=synthModel.operatorSync;
            if (checkSync.checked) {
                i=i|(0x01 << currentOperator);
            } else {
                if ((i & (0x01 << currentOperator)) != 0) {
                    i=i ^ (0x01 << currentOperator);
                }
            }
            synthModel.operatorSync=i;
        }
    }

    Column {
        id: column
        width: 32
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        anchors.top: parent.top
        anchors.topMargin: 0

        Button {
            id: buttonOperator1
            height: 59
            text: operatorPage.currentOperator === 0 ? qsTr("<font color='#0000FF'>1</font>") : qsTr("1")
            font.pixelSize: 32
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 0

            background: Rectangle {
                border.width: 1
                border.color: "#000000"
                color: operatorPage.currentOperator === 0 ? "#FFFF00" : "#D0D0D0"
            }

            onClicked: {
                setOperator(0);
            }
        }

        Button {
            id: buttonOperator2
            height: 59
            text: operatorPage.currentOperator === 1 ? qsTr("<font color='#0000FF'>2</font>") : qsTr("2")
            font.pixelSize: 32
            anchors.leftMargin: 0
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.left: parent.left

            background: Rectangle {
                border.width: 1
                border.color: "#000000"
                color: operatorPage.currentOperator === 1 ? "#FFFF00" : "#D0D0D0"
            }

            onClicked: {
                setOperator(1);
            }
        }

        Button {
            id: buttonOperator3
            height: 59
            text: operatorPage.currentOperator === 2 ? qsTr("<font color='#0000FF'>3</font>") : qsTr("3")
            font.pixelSize: 32
            anchors.leftMargin: 0
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.left: parent.left

            background: Rectangle {
                border.width: 1
                border.color: "#000000"
                color: operatorPage.currentOperator === 2 ? "#FFFF00" : "#D0D0D0"
            }

            onClicked: {
                setOperator(2);
            }
        }

        Button {
            id: buttonOperator4
            height: 59
            text: operatorPage.currentOperator === 3 ? qsTr("<font color='#0000FF'>4</font>") : qsTr("4")
            font.pixelSize: 32
            anchors.leftMargin: 0
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.left: parent.left

            background: Rectangle {
                border.width: 1
                border.color: "#000000"
                color: operatorPage.currentOperator === 3 ? "#FFFF00" : "#D0D0D0"
            }

            onClicked: {
                setOperator(3);
            }
        }

        Button {
            id: buttonOperator5
            height: 59
            text: operatorPage.currentOperator === 4 ? qsTr("<font color='#0000FF'>5</font>") : qsTr("5")
            font.pixelSize: 32
            anchors.leftMargin: 0
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.left: parent.left

            background: Rectangle {
                border.width: 1
                border.color: "#000000"
                color: operatorPage.currentOperator === 4 ? "#FFFF00" : "#D0D0D0"
            }

            onClicked: {
                setOperator(4);
            }
        }

        Button {
            id: buttonOperator6
            height: 59
            text: operatorPage.currentOperator === 5 ? qsTr("<font color='#0000FF'>6</font>") : qsTr("6")
            font.pixelSize: 32
            anchors.leftMargin: 0
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.left: parent.left

            background: Rectangle {
                border.width: 1
                border.color: "#000000"
                color: operatorPage.currentOperator === 5 ? "#FFFF00" : "#D0D0D0"
            }

            onClicked: {
                setOperator(5);
            }
        }
    }

    Rectangle {
        color: "#000000"
        height: 128
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: column.right
        anchors.leftMargin: 0
        anchors.top: parent.top
        anchors.topMargin: 0
    }

    Canvas {
        id: canvas;
        height: 128
        contextType: qsTr("2d")
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: column.right
        anchors.leftMargin: 0
        anchors.top: parent.top
        anchors.topMargin: 0

        property int grabRadius: 20

        onPaint: {
            var ctx = getContext("2d")

            ctx.fillStyle = "black"
            ctx.fillRect(0, 0, canvas.width, canvas.height)

            var opL0=fmOperator.L0/2;
            var opL1=fmOperator.L1/2;
            var opL2=fmOperator.L2/2;
            var opL3=fmOperator.L3/2;
            var opL4=fmOperator.L4/2;
            var opL5=fmOperator.L5/2;
            var opR0=fmOperator.R0/2;
            var opR1=fmOperator.R1/2;
            var opR2=fmOperator.R2/2;
            var opR3=fmOperator.R3/2;
            var opR4=fmOperator.R4/2;
            var opR5=fmOperator.R5/2;

<<<<<<< HEAD
            if (opL0 > 127) opL0=127;
            if (opL1 > 127) opL1=127;
            if (opL2 > 127) opL2=127;
            if (opL3 > 127) opL3=127;
            if (opL4 > 127) opL4=127;
            if (opL5 > 127) opL5=127;
            if (opR0 > 127) opR0=127;
            if (opR1 > 127) opR1=127;
            if (opR2 > 127) opR2=127;
            if (opR3 > 127) opR3=127;
            if (opR4 > 127) opR4=127;
            if (opR5 > 127) opR5=127;

=======
>>>>>>> 5f1b6151ec4d2bf472cad1981025fb954064533c
            ctx.lineWidth=1;
            ctx.strokeStyle="lightgray";
            ctx.beginPath();
            ctx.moveTo(opR0, 0);
            ctx.lineTo(opR0, canvas.height-1);
            ctx.moveTo(opR0+opR1, 0);
            ctx.lineTo(opR0+opR1, canvas.height-1);
            ctx.moveTo(opR0+opR1+opR2, 0);
            ctx.lineTo(opR0+opR1+opR2, canvas.height-1);
            ctx.moveTo(opR0+opR1+opR2+opR3, 0);
            ctx.lineTo(opR0+opR1+opR2+opR3, canvas.height-1);
            ctx.moveTo(opR0+opR1+opR2+opR3+opR4, 0);
            ctx.lineTo(opR0+opR1+opR2+opR3+opR4, canvas.height-1);
            ctx.moveTo(opR0+opR1+opR2+opR3+opR4+opR5, 0);
            ctx.lineTo(opR0+opR1+opR2+opR3+opR4+opR5, canvas.height-1);
            ctx.stroke();


            ctx.lineWidth = 5;
            ctx.strokeStyle = "green"
            ctx.beginPath()
            ctx.moveTo(0, canvas.height-1);
            ctx.lineTo(opR0, canvas.height-opL0-1);
            ctx.lineTo(opR0+opR1, canvas.height-opL1-1);
            ctx.lineTo(opR0+opR1+opR2, canvas.height-opL2-1);
            ctx.lineTo(opR0+opR1+opR2+opR3, canvas.height-opL3-1);
            ctx.lineTo(opR0+opR1+opR2+opR3+opR4, canvas.height-opL4-1);
            ctx.lineTo(opR0+opR1+opR2+opR3+opR4+opR5, canvas.height-opL5-1);
            ctx.lineTo(canvas.width-1, canvas.height-opL5-1);
            //ctx.closePath()
            ctx.stroke()

            ctx.fillStyle="green"
            ctx.fillRect(opR0-5, canvas.height-opL0-5-1, 10, 10);
            ctx.fillRect(opR0+opR1-5, canvas.height-opL1-5-1, 10, 10);
            ctx.fillRect(opR0+opR1+opR2-5, canvas.height-opL2-5-1, 10, 10);
            ctx.fillRect(opR0+opR1+opR2+opR3-5, canvas.height-opL3-5-1, 10, 10);
            ctx.fillRect(opR0+opR1+opR2+opR3+opR4-5, canvas.height-opL4-5-1, 10, 10);
            ctx.fillRect(opR0+opR1+opR2+opR3+opR4+opR5-5, canvas.height-opL5-5-1, 10, 10);
<<<<<<< HEAD

            ctx.fillStyle = "white";
            ctx.font = "16px monospace";
            ctx.fillText("L0: "+opL0.toFixed(0), canvas.width-160, 16);
            ctx.fillText("L1: "+opL1.toFixed(0), canvas.width-160, 32);
            ctx.fillText("L2: "+opL2.toFixed(0), canvas.width-160, 48);
            ctx.fillText("L3: "+opL3.toFixed(0), canvas.width-160, 64);
            ctx.fillText("L4: "+opL4.toFixed(0), canvas.width-160, 80);
            ctx.fillText("L5: "+opL5.toFixed(0), canvas.width-160, 96);

            ctx.fillText("R0: "+opR0.toFixed(0), canvas.width-80, 16);
            ctx.fillText("R1: "+opR1.toFixed(0), canvas.width-80, 32);
            ctx.fillText("R2: "+opR2.toFixed(0), canvas.width-80, 48);
            ctx.fillText("R3: "+opR3.toFixed(0), canvas.width-80, 64);
            ctx.fillText("R4: "+opR4.toFixed(0), canvas.width-80, 80);
            ctx.fillText("R5: "+opR5.toFixed(0), canvas.width-80, 96);
=======
>>>>>>> 5f1b6151ec4d2bf472cad1981025fb954064533c
        }

        MouseArea {
            id: mouseArea;
            anchors.fill: parent
            property int updatingPoint: -1
            property int deltaX: 0
            property int deltaY: 0

            onPressed: {
                var x=mouseArea.mouseX
                var y=mouseArea.mouseY

                var opL0=fmOperator.L0/2;
                var opL1=fmOperator.L1/2;
                var opL2=fmOperator.L2/2;
                var opL3=fmOperator.L3/2;
                var opL4=fmOperator.L4/2;
                var opL5=fmOperator.L5/2;
                var opR0=fmOperator.R0/2;
                var opR1=fmOperator.R1/2;
                var opR2=fmOperator.R2/2;
                var opR3=fmOperator.R3/2;
                var opR4=fmOperator.R4/2;
                var opR5=fmOperator.R5/2;

                if (x >= opR0-canvas.grabRadius && x <= opR0+canvas.grabRadius && y >= canvas.height-opL0-canvas.grabRadius-1 && y <= canvas.height-opL0+canvas.grabRadius-1) {
                    console.debug("R0,L0 clicked")
                    updatingPoint=0;
                    deltaX=x-(opR0-canvas.grabRadius);
                    deltaY=y-(canvas.height-opL0-canvas.grabRadius-1);
                } else if (x >= opR0+opR1-canvas.grabRadius && x <= opR0+opR1+canvas.grabRadius && y >= canvas.height-opL1-canvas.grabRadius-1 && y <= canvas.height-opL1+canvas.grabRadius-1) {
                    console.debug("R1,L1 clicked")
                    updatingPoint=1;
                    deltaX=x-(opR0+opR1-canvas.grabRadius);
                    deltaY=y-(canvas.height-opL1-canvas.grabRadius-1);
                } else if (x >= opR0+opR1+opR2-canvas.grabRadius && x <= opR0+opR1+opR2+canvas.grabRadius && y >= canvas.height-opL2-canvas.grabRadius-1 && y <= canvas.height-opL2+canvas.grabRadius-1) {
                    console.debug("R2,L2 clicked")
                    updatingPoint=2;
                    deltaX=x-(opR0+opR1+opR2-canvas.grabRadius);
                    deltaY=y-(canvas.height-opL2-canvas.grabRadius-1);
                } else if (x >= opR0+opR1+opR2+opR3-canvas.grabRadius && x <= opR0+opR1+opR2+opR3+canvas.grabRadius && y >= canvas.height-opL3-canvas.grabRadius-1 && y <= canvas.height-opL3+canvas.grabRadius-1) {
                    console.debug("R3,L3 clicked")
                    updatingPoint=3;
                    deltaX=x-(opR0+opR1+opR2+opR3-canvas.grabRadius);
                    deltaY=y-(canvas.height-opL3-canvas.grabRadius-1);
                } else if (x >= opR0+opR1+opR2+opR3+opR4-canvas.grabRadius && x <= opR0+opR1+opR2+opR3+opR4+canvas.grabRadius && y >= canvas.height-opL4-canvas.grabRadius-1 && y <= canvas.height-opL4+canvas.grabRadius-1) {
                    console.debug("R4,L4 clicked")
                    updatingPoint=4;
                    deltaX=x-(opR0+opR1+opR2+opR3+opR4-canvas.grabRadius);
                    deltaY=y-(canvas.height-opL4-canvas.grabRadius-1);
                } else if (x >= opR0+opR1+opR2+opR3+opR4+opR5-canvas.grabRadius && x <= opR0+opR1+opR2+opR3+opR4+opR5+canvas.grabRadius && y >= canvas.height-opL5-canvas.grabRadius-1 && y <= canvas.height-opL5+canvas.grabRadius-1) {
                    console.debug("R5,L5 clicked")
                    updatingPoint=5;
                    deltaX=x-(opR0+opR1+opR2+opR3+opR4+opR5-canvas.grabRadius);
                    deltaY=y-(canvas.height-opL5-canvas.grabRadius-1);
                }
            }

            onPositionChanged: {
                var x=mouseArea.mouseX-deltaX
                var y=mouseArea.mouseY-deltaY
                var rate;
                var level;

                if (updatingPoint == 0) {
                    rate=x;

                    if (rate < 0) {
                        rate=0;
                    } else if (rate > 127) {
                        rate=127;
                    }

                    level=canvas.height-y-1;

                    if (level < 0) {
                        level=0;
                    } else if (level > 127) {
                        level=127;
                    }

                    fmOperator.L0=level*2;
                    fmOperator.R0=rate*2;
                    canvas.requestPaint();
                } else if (updatingPoint == 1) {
                    rate=x-(fmOperator.R0/2);

                    if (rate < 0) {
                        rate=0;
                    } else if (rate > 127) {
                        rate=127;
                    }

                    level=canvas.height-y-1;

                    if (level < 0) {
                        level=0;
                    } else if (level > 127) {
                        level=127;
                    }

                    fmOperator.L1=level*2;
                    fmOperator.R1=rate*2;
                    canvas.requestPaint();
                } else if (updatingPoint == 2) {
                    rate=x-(fmOperator.R0+fmOperator.R1)/2;

                    if (rate < 0) {
                        rate=0;
                    } else if (rate > 127) {
                        rate=127;
                    }

                    level=canvas.height-y-1;

                    if (level < 0) {
                        level=0;
                    } else if (level > 127) {
                        level=127;
                    }

                    fmOperator.L2=level*2;
                    fmOperator.R2=rate*2;
                    canvas.requestPaint();
                } else if (updatingPoint == 3) {
                    rate=x-(fmOperator.R0+fmOperator.R1+fmOperator.R2)/2;

                    if (rate < 0) {
                        rate=0;
                    } else if (rate > 127) {
                        rate=127;
                    }

                    level=canvas.height-y-1;

                    if (level < 0) {
                        level=0;
                    } else if (level > 127) {
                        level=127;
                    }

                    fmOperator.L3=level*2;
                    fmOperator.R3=rate*2;
                    canvas.requestPaint();
                } else if (updatingPoint == 4) {
                    rate=x-(fmOperator.R0+fmOperator.R1+fmOperator.R2+fmOperator.R3)/2;

                    if (rate < 0) {
                        rate=0;
                    } else if (rate > 127) {
                        rate=127;
                    }

                    level=canvas.height-y-1;

                    if (level < 0) {
                        level=0;
                    } else if (level > 127) {
                        level=127;
                    }

                    fmOperator.L4=level*2;
                    fmOperator.R4=rate*2;
                    canvas.requestPaint();
                } else if (updatingPoint == 5) {
                    rate=x-(fmOperator.R0+fmOperator.R1+fmOperator.R2+fmOperator.R3+fmOperator.R4)/2;

                    if (rate < 0) {
                        rate=0;
                    } else if (rate > 127) {
                        rate=127;
                    }

                    level=canvas.height-y-1;

                    if (level < 0) {
                        level=0;
                    } else if (level > 127) {
                        level=127;
                    }

                    fmOperator.L5=level*2;
                    fmOperator.R5=rate*2;
                    canvas.requestPaint();
                }

                synthModel.updateOperator(fmOperator);
            }

            onReleased: {
                updatingPoint=-1;
            }
        }
    }

    Rectangle {
        id: keyboardPanel
        color: "#505050"
        visible: false
        height: 128
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: column.right
        anchors.leftMargin: 0
        anchors.top: parent.top
        anchors.topMargin: 0

        Label {
            id: label14
            x: 21
            y: 20
            color: "#ffffff"
            text: qsTr("Split Point")
        }

        Label {
            id: label16
            x: 359
            y: 96
            width: 56
            height: 17
            color: "#ffffff"
            text: qsTr("R Depth")
            horizontalAlignment: Text.AlignHCenter
        }

        Slider {
            id: sliderRDepth
            x: 367
            y: 8
            width: 40
            height: 87
            to: 255
            orientation: Qt.Vertical
            onValueChanged: {
                fmOperator.keyboardScaleRight=sliderRDepth.value;
                synthModel.updateOperator(fmOperator);
            }
        }

        Label {
            id: label15
            x: 280
            y: 96
            width: 56
            height: 17
            color: "#ffffff"
            text: qsTr("L Depth")
            horizontalAlignment: Text.AlignHCenter
        }

        Slider {
            id: sliderLDepth
            x: 288
            y: 8
            width: 40
            height: 87
            to: 255
            orientation: Qt.Vertical
            onValueChanged: {
                fmOperator.keyboardScaleLeft=sliderLDepth.value;
                synthModel.updateOperator(fmOperator);
            }
        }

        SpinBox {
            id: spinKeyboardBreakpoint
            x: 106
            y: 8
            to: 127
            onValueChanged: {
                fmOperator.keyboardBreakpoint=spinKeyboardBreakpoint.value;
                synthModel.updateOperator(fmOperator);
            }
            textFromValue: function(value, locale) {
                var str;
                var notes=["C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"];
                var octave=Math.floor(value/12);
                var n=value % 12;

                octave=octave-1;
                str=notes[n];
                str=str+" "+octave.toString();
                return str;
            }
        }

        SpinBox {
            id: spinLeftCurve
            x: 574
            y: 9
            width: 165
            height: 40
            to: 3
            onValueChanged: {
                fmOperator.keyboardCurveLeft=spinLeftCurve.value;
                synthModel.updateOperator(fmOperator);
            }
            textFromValue: function(value, locale) {
                var clist=["exp -", "lin -", "lin +", "exp +"];

                return clist[value];
            }
        }

        Label {
            id: label18
            x: 475
            y: 72
            width: 79
            height: 17
            color: "#ffffff"
            text: qsTr("Right Curve")
            horizontalAlignment: Text.AlignHCenter
        }

        Label {
            id: label17
            x: 475
            y: 22
            width: 79
            height: 17
            color: "#ffffff"
            text: qsTr("Left Curve")
            horizontalAlignment: Text.AlignHCenter
        }

        SpinBox {
            id: spinRightCurve
            x: 574
            y: 62
            width: 165
            height: 40
            to: 3
            onValueChanged: {
                fmOperator.keyboardCurveRight=spinRightCurve.value;
                synthModel.updateOperator(fmOperator);
            }
            textFromValue: function(value, locale) {
                var clist=["exp -", "lin -", "lin +", "exp +"];

                return clist[value];
            }
        }
    }

    CustomDial {
        id: dialFeedback
        x: 35
        y: 135
        width: 121
        height: 80
        maximumValue: 255
        stepSize: 1
        onValueChanged: {
            fmOperator.feedback=dialFeedback.value;
            synthModel.updateOperator(fmOperator);
        }
    }

    Label {
        id: label
        x: 63
        y: 221
        color: "#ffffff"
        text: qsTr("Feedback")
        font.pixelSize: 16
    }

    CustomDial {
        id: dialRatio
        x: 156
        y: 135
        width: 121
        height: 80
<<<<<<< HEAD
        maximumValue: 63
=======
        maximumValue: 255
>>>>>>> 5f1b6151ec4d2bf472cad1981025fb954064533c
        stepSize: 1
        onValueChanged: {
            fmOperator.ratio=dialRatio.value;
            synthModel.updateOperator(fmOperator);
        }
    }

    Label {
        id: label1
        x: 199
        y: 221
        color: "#ffffff"
        text: qsTr("Ratio")
        font.pixelSize: 16
    }

    CustomDial {
        id: dialRatioFine
        x: 156
        y: 248
        width: 121
        height: 80
        maximumValue: 255
        stepSize: 1
        onValueChanged: {
            fmOperator.ratioFine=dialRatioFine.value;
            synthModel.updateOperator(fmOperator);
        }
    }

    Label {
        id: label2
        x: 183
        y: 332
        color: "#ffffff"
        text: qsTr("Ratio Fine")
        font.pixelSize: 16
    }

    CustomDial {
        id: dialFine
        x: 35
        y: 248
        width: 121
        height: 80
        maximumValue: 255
        stepSize: 1
        onValueChanged: {
            fmOperator.fine=dialFine.value;
            synthModel.updateOperator(fmOperator);
        }
    }

    Label {
        id: label3
        x: 81
        y: 332
        color: "#ffffff"
        text: qsTr("Fine")
        font.pixelSize: 16
    }

    Label {
        id: label4
        x: 404
        y: 152
        color: "#ffffff"
        text: qsTr("OSC 1")
        font.pixelSize: 16
    }

    Label {
        id: label5
        x: 404
        y: 202
        color: "#ffffff"
        text: qsTr("OSC 2")
        font.pixelSize: 16
    }

    SpinBox {
        id: spinOsc2Mode
        x: 457
        y: 190
        to: 7
        onValueChanged: {
            fmOperator.wave2=spinOsc1Mode.value;
            synthModel.updateOperator(fmOperator);
        }
    }

    CustomDial {
        id: dialOscRatio
        x: 399
        y: 248
        width: 121
        height: 80
        stepSize: 1
        maximumValue: 255
        onValueChanged: {
            fmOperator.oscillatorRatio=dialOscRatio.value;
            synthModel.updateOperator(fmOperator);
        }
    }

    Label {
        id: label6
        x: 423
        y: 332
        width: 72
        height: 17
        color: "#ffffff"
        text: qsTr("OSC Ratio")
        font.pixelSize: 16
        horizontalAlignment: Text.AlignHCenter
    }

    SpinBox {
        id: spinOscPhase
        x: 653
        y: 140
        to: 3
        onValueChanged: {
            fmOperator.phase=spinOscPhase.value;
            synthModel.updateOperator(fmOperator);
        }
        textFromValue: function(value, locale) {
            var str;

            if (value === 0) {
                str="0"
            } else if (value === 1) {
                str="90"
            } else if (value === 2) {
                str="180"
            } else {
                str="270"
            }

            return str;
        }
    }

    Label {
        id: label7
        x: 606
        y: 152
        color: "#ffffff"
        text: qsTr("Phase")
        font.pixelSize: 16
    }

    Label {
        id: label8
        x: 639
        y: 332
        width: 56
        height: 17
        color: "#ffffff"
        text: qsTr("Level")
        font.pixelSize: 16
        horizontalAlignment: Text.AlignHCenter
    }

    Slider {
        id: sliderMixL
        x: 699
        y: 241
        width: 40
        height: 87
        to: 255
        orientation: Qt.Vertical
        onValueChanged: {
            fmOperator.levelLeft=sliderMixL.value;
            synthModel.updateOperator(fmOperator);
        }
    }

    Slider {
        id: sliderMixR
        x: 751
        y: 241
        width: 40
        height: 87
        to: 255
        orientation: Qt.Vertical
        onValueChanged: {
            fmOperator.levelRight=sliderMixR.value;
            synthModel.updateOperator(fmOperator);
        }
    }

    Label {
        id: label9
        x: 691
        y: 332
        width: 56
        height: 17
        color: "#ffffff"
        text: qsTr("Mix L")
        font.pixelSize: 16
        horizontalAlignment: Text.AlignHCenter
    }

    Label {
        id: label10
        x: 743
        y: 332
        width: 56
        height: 17
        color: "#ffffff"
        text: qsTr("Mix R")
        font.pixelSize: 16
        horizontalAlignment: Text.AlignHCenter
    }

    CustomDial {
        id: dialVelocitySens
        x: 278
        y: 248
        width: 121
        height: 80
        stepSize: 1
        maximumValue: 255
        onValueChanged: {
            fmOperator.velocitySensitivity=dialVelocitySens.value;
            synthModel.updateOperator(fmOperator);
        }
    }

    Label {
        id: label11
        x: 294
        y: 332
        color: "#ffffff"
        text: qsTr("Velocity Sens")
        font.pixelSize: 16
    }

    Slider {
        id: sliderAMS
        x: 538
        y: 241
        width: 40
        height: 87
        to: 255
        orientation: Qt.Vertical
        onValueChanged: {
            fmOperator.amplitudeModulationSensitivity=sliderAMS.value;
            synthModel.updateOperator(fmOperator);
        }
    }

    Slider {
        id: sliderPMS
        x: 595
        y: 241
        width: 40
        height: 87
        to: 255
        orientation: Qt.Vertical
        onValueChanged: {
            fmOperator.pitchModulationSensitivity=sliderPMS.value;
            synthModel.updateOperator(fmOperator);
        }
    }

    Label {
        id: label12
        x: 530
        y: 332
        width: 56
        height: 17
        color: "#ffffff"
        text: qsTr("AMS")
        font.pixelSize: 16
        horizontalAlignment: Text.AlignHCenter
    }

    Label {
        id: label13
        x: 587
        y: 332
        width: 56
        height: 17
        color: "#ffffff"
        text: qsTr("PMS")
        font.pixelSize: 16
        horizontalAlignment: Text.AlignHCenter
    }

    Component.onCompleted: {
        setOperator(0);
    }

}

/*##^##
Designer {
    D{i:1;anchors_height:400;anchors_x:0;anchors_y:0}
}
##^##*/
