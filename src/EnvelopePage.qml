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
    id: envelopePage
    width: 800
    height: 357

    Connections {
        target: synthModel
        onPatchNumberChanged: {
            updatePage();
        }
    }

    function updatePage()
    {
        dialRange.value=synthModel.pitchEG_Range;
        dialVelocity.value=synthModel.pitchEG_Velocity;
        dialRateKey.value=synthModel.pitchEG_RateKey;
        canvas.requestPaint();
    }

    Rectangle {
        anchors.fill: parent
        color: "#505050"
    }

    Row {
        id: envLoopRow
        x: 444
        y: 151
        width: 334
        height: 56
        spacing: 2

        Label {
            id: labelLoop1
            width: 50
            text: qsTr("1")
            font.pixelSize: 24
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.top: parent.top
            anchors.topMargin: 0
            color: synthModel.envelopeLoop & 0x01 ? "#ffffff" : "#000000"
            background: Rectangle {
                color: synthModel.envelopeLoop & 0x01 ? "#0000FF" : "#808080"
                radius: 5
            }

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    var i=synthModel.envelopeLoop;

                    i=i ^ 0x01;
                    synthModel.envelopeLoop=i;
                }
            }
        }
        Label {
            id: labelLoop2
            width: 50
            text: qsTr("2")
            font.pixelSize: 24
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.top: parent.top
            anchors.topMargin: 0
            color: synthModel.envelopeLoop & 0x02 ? "#ffffff" : "#000000"
            background: Rectangle {
                color: synthModel.envelopeLoop & 0x02 ? "#0000FF" : "#808080"
                radius: 5
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    var i=synthModel.envelopeLoop;

                    i=i ^ 0x02;
                    synthModel.envelopeLoop=i;
                }
            }
        }
        Label {
            id: labelLoop3
            width: 50
            text: qsTr("3")
            font.pixelSize: 24
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.top: parent.top
            anchors.topMargin: 0
            color: synthModel.envelopeLoop & 0x04 ? "#ffffff" : "#000000"
            background: Rectangle {
                color: synthModel.envelopeLoop & 0x04 ? "#0000FF" : "#808080"
                radius: 5
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    var i=synthModel.envelopeLoop;

                    i=i ^ 0x04;
                    synthModel.envelopeLoop=i;
                }
            }
        }
        Label {
            id: labelLoop4
            width: 50
            text: qsTr("4")
            font.pixelSize: 24
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.top: parent.top
            anchors.topMargin: 0
            color: synthModel.envelopeLoop & 0x08 ? "#ffffff" : "#000000"
            background: Rectangle {
                color: synthModel.envelopeLoop & 0x08 ? "#0000FF" : "#808080"
                radius: 5
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    var i=synthModel.envelopeLoop;

                    i=i ^ 0x08;
                    synthModel.envelopeLoop=i;
                }
            }
        }
        Label {
            id: labelLoop5
            width: 50
            text: qsTr("5")
            font.pixelSize: 24
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.top: parent.top
            anchors.topMargin: 0
            color: synthModel.envelopeLoop & 0x10 ? "#ffffff" : "#000000"
            background: Rectangle {
                color: synthModel.envelopeLoop & 0x10 ? "#0000FF" : "#808080"
                radius: 5
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    var i=synthModel.envelopeLoop;

                    i=i ^ 0x10;
                    synthModel.envelopeLoop=i;
                }
            }
        }
        Label {
            id: labelLoop6
            width: 50
            text: qsTr("6")
            font.pixelSize: 24
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.top: parent.top
            anchors.topMargin: 0
            color: synthModel.envelopeLoop & 0x20 ? "#ffffff" : "#000000"
            background: Rectangle {
                color: synthModel.envelopeLoop & 0x20 ? "#0000FF" : "#808080"
                radius: 5
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    var i=synthModel.envelopeLoop;

                    i=i ^ 0x20;
                    synthModel.envelopeLoop=i;
                }
            }
        }
    }


    Row {
        id: evSegRow
        x: 444
        y: 220
        width: 334
        height: 56
        spacing: 2

        Label {
            id: labelSeg1
            width: 50
            text: qsTr("1")
            font.pixelSize: 24
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.top: parent.top
            anchors.topMargin: 0
            color: synthModel.envelopeLoopSegment & 0x01 ? "#ffffff" : "#000000"
            background: Rectangle {
                color: synthModel.envelopeLoopSegment & 0x01 ? "#0000FF" : "#808080"
                radius: 5
            }

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    var i=synthModel.envelopeLoopSegment;

                    i=i ^ 0x01;
                    synthModel.envelopeLoopSegment=i;
                }
            }
        }
        Label {
            id: labelSeg2
            width: 50
            text: qsTr("2")
            font.pixelSize: 24
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.top: parent.top
            anchors.topMargin: 0
            color: synthModel.envelopeLoopSegment & 0x02 ? "#ffffff" : "#000000"
            background: Rectangle {
                color: synthModel.envelopeLoopSegment & 0x02 ? "#0000FF" : "#808080"
                radius: 5
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    var i=synthModel.envelopeLoopSegment;

                    i=i ^ 0x02;
                    synthModel.envelopeLoopSegment=i;
                }
            }
        }
        Label {
            id: labelSeg3
            width: 50
            text: qsTr("3")
            font.pixelSize: 24
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.top: parent.top
            anchors.topMargin: 0
            color: synthModel.envelopeLoopSegment & 0x04 ? "#ffffff" : "#000000"
            background: Rectangle {
                color: synthModel.envelopeLoopSegment & 0x04 ? "#0000FF" : "#808080"
                radius: 5
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    var i=synthModel.envelopeLoopSegment;

                    i=i ^ 0x04;
                    synthModel.envelopeLoopSegment=i;
                }
            }
        }
        Label {
            id: labelSeg4
            width: 50
            text: qsTr("4")
            font.pixelSize: 24
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.top: parent.top
            anchors.topMargin: 0
            color: synthModel.envelopeLoopSegment & 0x08 ? "#ffffff" : "#000000"
            background: Rectangle {
                color: synthModel.envelopeLoopSegment & 0x08 ? "#0000FF" : "#808080"
                radius: 5
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    var i=synthModel.envelopeLoopSegment;

                    i=i ^ 0x08;
                    synthModel.envelopeLoopSegment=i;
                }
            }
        }
        Label {
            id: labelSeg5
            width: 50
            text: qsTr("5")
            font.pixelSize: 24
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.top: parent.top
            anchors.topMargin: 0
            color: synthModel.envelopeLoopSegment & 0x10 ? "#ffffff" : "#000000"
            background: Rectangle {
                color: synthModel.envelopeLoopSegment & 0x10 ? "#0000FF" : "#808080"
                radius: 5
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    var i=synthModel.envelopeLoopSegment;

                    i=i ^ 0x10;
                    synthModel.envelopeLoopSegment=i;
                }
            }
        }
        Label {
            id: labelSeg6
            width: 50
            text: qsTr("6")
            font.pixelSize: 24
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.top: parent.top
            anchors.topMargin: 0
            color: synthModel.envelopeLoopSegment & 0x20 ? "#ffffff" : "#000000"
            background: Rectangle {
                color: synthModel.envelopeLoopSegment & 0x20 ? "#0000FF" : "#808080"
                radius: 5
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    var i=synthModel.envelopeLoopSegment;

                    i=i ^ 0x20;
                    synthModel.envelopeLoopSegment=i;
                }
            }
        }
    }


    Rectangle {
        color: "#000000"
        x: 16
        width: 768
        height: 128
        anchors.top: parent.top
        anchors.topMargin: 0
    }

    Canvas {
        id: canvas;
        x: 16
        width: 768
        height: 128
        contextType: qsTr("2d")
        anchors.top: parent.top
        anchors.topMargin: 0
        property int grabRadius: 20

        onPaint: {
            var ctx = getContext("2d")

            ctx.fillStyle = "black"
            ctx.fillRect(0, 0, canvas.width, canvas.height)

            var egL0=synthModel.pitchEG_L0/2;
            var egL1=synthModel.pitchEG_L1/2;
            var egL2=synthModel.pitchEG_L2/2;
            var egL3=synthModel.pitchEG_L3/2;
            var egL4=synthModel.pitchEG_L4/2;
            var egL5=synthModel.pitchEG_L5/2;
            var egR0=synthModel.pitchEG_R0/2;
            var egR1=synthModel.pitchEG_R1/2;
            var egR2=synthModel.pitchEG_R2/2;
            var egR3=synthModel.pitchEG_R3/2;
            var egR4=synthModel.pitchEG_R4/2;
            var egR5=synthModel.pitchEG_R5/2;

<<<<<<< HEAD
            if (egL0 > 127) egL0=127;
            if (egL1 > 127) egL1=127;
            if (egL2 > 127) egL2=127;
            if (egL3 > 127) egL3=127;
            if (egL4 > 127) egL4=127;
            if (egL5 > 127) egL5=127;
            if (egR0 > 127) egR0=127;
            if (egR1 > 127) egR1=127;
            if (egR2 > 127) egR2=127;
            if (egR3 > 127) egR3=127;
            if (egR4 > 127) egR4=127;
            if (egR5 > 127) egR5=127;

=======
>>>>>>> 5f1b6151ec4d2bf472cad1981025fb954064533c
            ctx.lineWidth=1;
            ctx.strokeStyle="lightgray";
            ctx.beginPath();
            ctx.moveTo(egR0, 0);
            ctx.lineTo(egR0, canvas.height-1);
            ctx.moveTo(egR0+egR1, 0);
            ctx.lineTo(egR0+egR1, canvas.height-1);
            ctx.moveTo(egR0+egR1+egR2, 0);
            ctx.lineTo(egR0+egR1+egR2, canvas.height-1);
            ctx.moveTo(egR0+egR1+egR2+egR3, 0);
            ctx.lineTo(egR0+egR1+egR2+egR3, canvas.height-1);
            ctx.moveTo(egR0+egR1+egR2+egR3+egR4, 0);
            ctx.lineTo(egR0+egR1+egR2+egR3+egR4, canvas.height-1);
            ctx.moveTo(egR0+egR1+egR2+egR3+egR4+egR5, 0);
            ctx.lineTo(egR0+egR1+egR2+egR3+egR4+egR5, canvas.height-1);
            ctx.stroke();

            ctx.lineWidth = 5;
            ctx.strokeStyle = "yellow"
            ctx.beginPath()
            ctx.moveTo(0, canvas.height-1);
            ctx.lineTo(egR0, canvas.height-egL0-1);
            ctx.lineTo(egR0+egR1, canvas.height-egL1-1);
            ctx.lineTo(egR0+egR1+egR2, canvas.height-egL2-1);
            ctx.lineTo(egR0+egR1+egR2+egR3, canvas.height-egL3-1);
            ctx.lineTo(egR0+egR1+egR2+egR3+egR4, canvas.height-egL4-1);
            ctx.lineTo(egR0+egR1+egR2+egR3+egR4+egR5, canvas.height-egL5-1);
            ctx.lineTo(canvas.width-1, canvas.height-egL5-1);
            //ctx.closePath()
            ctx.stroke()

            ctx.fillStyle="yellow"
            ctx.fillRect(egR0-5, canvas.height-egL0-5-1, 10, 10);
            ctx.fillRect(egR0+egR1-5, canvas.height-egL1-5-1, 10, 10);
            ctx.fillRect(egR0+egR1+egR2-5, canvas.height-egL2-5-1, 10, 10);
            ctx.fillRect(egR0+egR1+egR2+egR3-5, canvas.height-egL3-5-1, 10, 10);
            ctx.fillRect(egR0+egR1+egR2+egR3+egR4-5, canvas.height-egL4-5-1, 10, 10);
            ctx.fillRect(egR0+egR1+egR2+egR3+egR4+egR5-5, canvas.height-egL5-5-1, 10, 10);
<<<<<<< HEAD

            ctx.fillStyle = "white";
            ctx.font = "16px monospace";
            ctx.fillText("L0: "+egL0.toFixed(0), canvas.width-160, 16);
            ctx.fillText("L1: "+egL1.toFixed(0), canvas.width-160, 32);
            ctx.fillText("L2: "+egL2.toFixed(0), canvas.width-160, 48);
            ctx.fillText("L3: "+egL3.toFixed(0), canvas.width-160, 64);
            ctx.fillText("L4: "+egL4.toFixed(0), canvas.width-160, 80);
            ctx.fillText("L5: "+egL5.toFixed(0), canvas.width-160, 96);

            ctx.fillText("R0: "+egR0.toFixed(0), canvas.width-80, 16);
            ctx.fillText("R1: "+egR1.toFixed(0), canvas.width-80, 32);
            ctx.fillText("R2: "+egR2.toFixed(0), canvas.width-80, 48);
            ctx.fillText("R3: "+egR3.toFixed(0), canvas.width-80, 64);
            ctx.fillText("R4: "+egR4.toFixed(0), canvas.width-80, 80);
            ctx.fillText("R5: "+egR5.toFixed(0), canvas.width-80, 96);
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

                var egL0=synthModel.pitchEG_L0/2;
                var egL1=synthModel.pitchEG_L1/2;
                var egL2=synthModel.pitchEG_L2/2;
                var egL3=synthModel.pitchEG_L3/2;
                var egL4=synthModel.pitchEG_L4/2;
                var egL5=synthModel.pitchEG_L5/2;
                var egR0=synthModel.pitchEG_R0/2;
                var egR1=synthModel.pitchEG_R1/2;
                var egR2=synthModel.pitchEG_R2/2;
                var egR3=synthModel.pitchEG_R3/2;
                var egR4=synthModel.pitchEG_R4/2;
                var egR5=synthModel.pitchEG_R5/2;

                if (x >= egR0-canvas.grabRadius && x <= egR0+canvas.grabRadius && y >= canvas.height-egL0-canvas.grabRadius-1 && y <= canvas.height-egL0+canvas.grabRadius-1) {
                    console.debug("R0,L0 clicked")
                    updatingPoint=0;
                    deltaX=x-(egR0-canvas.grabRadius);
                    deltaY=y-(canvas.height-egL0-canvas.grabRadius-1);
                } else if (x >= egR0+egR1-canvas.grabRadius && x <= egR0+egR1+canvas.grabRadius && y >= canvas.height-egL1-canvas.grabRadius-1 && y <= canvas.height-egL1+canvas.grabRadius-1) {
                    console.debug("R1,L1 clicked")
                    updatingPoint=1;
                    deltaX=x-(egR0+egR1-canvas.grabRadius);
                    deltaY=y-(canvas.height-egL1-canvas.grabRadius-1);
                } else if (x >= egR0+egR1+egR2-canvas.grabRadius && x <= egR0+egR1+egR2+canvas.grabRadius && y >= canvas.height-egL2-canvas.grabRadius-1 && y <= canvas.height-egL2+canvas.grabRadius-1) {
                    console.debug("R2,L2 clicked")
                    updatingPoint=2;
                    deltaX=x-(egR0+egR1+egR2-canvas.grabRadius);
                    deltaY=y-(canvas.height-egL2-canvas.grabRadius-1);
                } else if (x >= egR0+egR1+egR2+egR3-canvas.grabRadius && x <= egR0+egR1+egR2+egR3+canvas.grabRadius && y >= canvas.height-egL3-canvas.grabRadius-1 && y <= canvas.height-egL3+canvas.grabRadius-1) {
                    console.debug("R3,L3 clicked")
                    updatingPoint=3;
                    deltaX=x-(egR0+egR1+egR2+egR3-canvas.grabRadius);
                    deltaY=y-(canvas.height-egL3-canvas.grabRadius-1);
                } else if (x >= egR0+egR1+egR2+egR3+egR4-canvas.grabRadius && x <= egR0+egR1+egR2+egR3+egR4+canvas.grabRadius && y >= canvas.height-egL4-canvas.grabRadius-1 && y <= canvas.height-egL4+canvas.grabRadius-1) {
                    console.debug("R4,L4 clicked")
                    updatingPoint=4;
                    deltaX=x-(egR0+egR1+egR2+egR3+egR4-canvas.grabRadius);
                    deltaY=y-(canvas.height-egL4-canvas.grabRadius-1);
                } else if (x >= egR0+egR1+egR2+egR3+egR4+egR5-canvas.grabRadius && x <= egR0+egR1+egR2+egR3+egR4+egR5+canvas.grabRadius && y >= canvas.height-egL5-canvas.grabRadius-1 && y <= canvas.height-egL5+canvas.grabRadius-1) {
                    console.debug("R5,L5 clicked")
                    updatingPoint=5;
                    deltaX=x-(egR0+egR1+egR2+egR3+egR4+egR5-canvas.grabRadius);
                    deltaY=y-(canvas.height-egL5-canvas.grabRadius-1);
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

                    synthModel.pitchEG_L0=level*2;
                    synthModel.pitchEG_R0=rate*2;
                    canvas.requestPaint();
                } else if (updatingPoint == 1) {
                    rate=x-synthModel.pitchEG_R0/2;

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

                    synthModel.pitchEG_L1=level*2;
                    synthModel.pitchEG_R1=rate*2;
                    canvas.requestPaint();
                } else if (updatingPoint == 2) {
                    rate=x-(synthModel.pitchEG_R0+synthModel.pitchEG_R1)/2;

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

                    synthModel.pitchEG_L2=level*2;
                    synthModel.pitchEG_R2=rate*2;
                    canvas.requestPaint();
                } else if (updatingPoint == 3) {
                    rate=x-(synthModel.pitchEG_R0+synthModel.pitchEG_R1+synthModel.pitchEG_R2)/2;

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

                    synthModel.pitchEG_L3=level*2;
                    synthModel.pitchEG_R3=rate*2;
                    canvas.requestPaint();
                } else if (updatingPoint == 4) {
                    rate=x-(synthModel.pitchEG_R0+synthModel.pitchEG_R1+synthModel.pitchEG_R2+synthModel.pitchEG_R3)/2;

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

                    synthModel.pitchEG_L4=level*2;
                    synthModel.pitchEG_R4=rate*2;
                    canvas.requestPaint();
                } else if (updatingPoint == 5) {
                    rate=x-(synthModel.pitchEG_R0+synthModel.pitchEG_R1+synthModel.pitchEG_R2+synthModel.pitchEG_R3+synthModel.pitchEG_R4)/2;

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

                    synthModel.pitchEG_L5=level*2;
                    synthModel.pitchEG_R5=rate*2;
                    canvas.requestPaint();
                }
            }

            onReleased: {
                updatingPoint=-1;
            }

        }
    }

    CustomDial {
        id: dialRange
        x: 16
        y: 139
        width: 121
        height: 80
        maximumValue: 127
        stepSize: 1
        onValueChanged: {
            synthModel.pitchEG_Range=dialRange.value;
        }
    }

    Label {
        id: label
        x: 55
        y: 225
        color: "#ffffff"
        text: qsTr("Range")
        font.pixelSize: 16
    }

    CustomDial {
        id: dialVelocity
        x: 143
        y: 139
        width: 121
        height: 80
        maximumValue: 255
        stepSize: 1
        onValueChanged: {
            synthModel.pitchEG_Velocity=dialVelocity.value;
        }
    }

    Label {
        id: label1
        x: 176
        y: 225
        color: "#ffffff"
        text: qsTr("Velocity")
        font.pixelSize: 16
    }

    CustomDial {
        id: dialRateKey
        x: 16
        y: 248
        width: 121
        height: 80
        maximumValue: 255
        stepSize: 1
        onValueChanged: {
            synthModel.pitchEG_RateKey=dialRateKey.value;
        }
    }

    Label {
        id: label2
        x: 49
        y: 334
        color: "#ffffff"
        text: qsTr("Rate Key")
        font.pixelSize: 16
    }

    Label {
        id: label3
        x: 330
        y: 171
        color: "#ffffff"
        text: qsTr("Envelope Loop")
        font.pixelSize: 16
    }

    Label {
        id: label4
        x: 304
        y: 240
        color: "#ffffff"
        text: qsTr("Env Loop Segment")
        font.pixelSize: 16
    }

    Component.onCompleted: {
        updatePage();
    }

}

/*##^##
Designer {
    D{i:1;anchors_height:400;anchors_x:0;anchors_y:0}
}
##^##*/
