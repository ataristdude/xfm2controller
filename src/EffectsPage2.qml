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
    id: effectsPage2
    width: 800
    height: 357


    Rectangle {
        anchors.fill: parent
        color: "#505050"
    }

    Connections {
        target: synthModel
        onPatchNumberChanged: {
            updatePage();
        }
    }

    function updatePage()
    {
        dialBitCrusher.value=synthModel.fxBitCrushDepth;
        dialDecimator.value=synthModel.fxDecimator;
        dialLowPassFilter.value=synthModel.filterLoCutoff;
        dialHighPassFilter.value=synthModel.filterHiCutoff;

        dialAMDepth.value=synthModel.fxAMDepth;
        dialAMSpeed.value=synthModel.fxAMSpeed;
        dialAMRange.value=synthModel.fxAMRange;
        dialAMPhase.value=synthModel.fxAMPhase;

        dialReverbDry.value=synthModel.fxReverbDry;
        dialReverbWet.value=synthModel.fxReverbWet;
        dialReverbDecay.value=synthModel.fxReverbDecay;
        dialReverbDamp.value=synthModel.fxReverbDamp;
        spinReverbMode.value=synthModel.fxReverbMode;

        switchFXRoute.checked=synthModel.fxRoute !== 0;
    }

    Rectangle {
        id: rectangle1
        x: 109
        y: 175
        width: 508
        height: 2
        color: "#ffffff"
        border.color: "#ffb060"
    }

    Switch {
        id: switchFXRoute
        x: 623
        y: 218
        text: qsTr("<font color='white'>Delay-Chorus</font>")
        font.pixelSize: 16
        onCheckedChanged: {
            if (switchFXRoute.checked) {
                synthModel.fxRoute=1;
            } else {
                synthModel.fxRoute=0;
            }
        }
    }

    Rectangle {
        id: rectangle
        x: 61
        y: 17
        width: 731
        height: 2
        color: "#ffffff"
        border.color: "#ffb060"
    }

    Label {
        id: label
        x: 8
        y: 110
        color: "#ffffff"
        text: qsTr("Bit Crusher")
        font.pixelSize: 16
    }

    CustomDial {
        id: dialBitCrusher
        x: 14
        y: 40
        width: 64
        height: 64
        maximumValue: 24
        onValueChanged: {
            synthModel.fxBitCrushDepth=dialBitCrusher.value;
        }
    }

    CustomDial {
        id: dialDecimator
        x: 104
        y: 40
        width: 64
        height: 64
        maximumValue: 255
        onValueChanged: {
            synthModel.fxDecimator=dialDecimator.value;
        }
    }

    Label {
        id: label1
        x: 101
        y: 110
        width: 71
        height: 17
        color: "#ffffff"
        text: qsTr("Decimator")
        font.pixelSize: 16
    }

    CustomDial {
        id: dialLowPassFilter
        x: 194
        y: 40
        width: 64
        height: 64
        maximumValue: 255
        onValueChanged: {
            synthModel.filterLoCutoff=dialLowPassFilter.value;
        }
    }

    Label {
        id: label2
        x: 190
        y: 110
        width: 72
        height: 17
        color: "#ffffff"
        text: qsTr("Low Pass")
        font.pixelSize: 16
        horizontalAlignment: Text.AlignHCenter
    }

    CustomDial {
        id: dialHighPassFilter
        x: 284
        y: 40
        width: 64
        height: 64
        maximumValue: 255
        onValueChanged: {
            synthModel.filterHiCutoff=dialHighPassFilter.value;
        }
    }

    Label {
        id: label3
        x: 285
        y: 110
        width: 62
        height: 17
        color: "#ffffff"
        text: qsTr("Hi Pass")
        font.pixelSize: 16
        horizontalAlignment: Text.AlignHCenter
    }

    Label {
        id: label4
        x: 0
        y: 10
        color: "#ffb060"
        text: qsTr("Effects")
        font.pixelSize: 16
    }

    Label {
        id: label5
        x: 0
        y: 166
        color: "#ffb060"
        text: qsTr("Global Reverb")
        font.pixelSize: 16
    }

    CustomDial {
        id: dialAMDepth
        x: 419
        y: 40
        width: 64
        height: 64
        maximumValue: 255
        onValueChanged: {
            synthModel.fxAMDepth=dialAMDepth.value;
        }
    }

    Label {
        id: label6
        x: 420
        y: 110
        width: 62
        height: 35
        color: "#ffffff"
        text: qsTr("AM Depth")
        font.pixelSize: 16
        wrapMode: Text.WordWrap
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
    }

    CustomDial {
        id: dialAMSpeed
        x: 509
        y: 40
        width: 64
        height: 64
        maximumValue: 255
        onValueChanged: {
            synthModel.fxAMSpeed=dialAMSpeed.value;
        }
    }

    Label {
        id: label7
        x: 510
        y: 110
        width: 62
        height: 35
        color: "#ffffff"
        text: qsTr("AM Speed")
        font.pixelSize: 16
        wrapMode: Text.WordWrap
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
    }

    CustomDial {
        id: dialAMRange
        x: 599
        y: 40
        width: 64
        height: 64
        maximumValue: 255
        onValueChanged: {
            synthModel.fxAMRange=dialAMRange.value;
        }

    }

    Label {
        id: label8
        x: 600
        y: 110
        width: 62
        height: 35
        color: "#ffffff"
        text: qsTr("AM Range")
        font.pixelSize: 16
        wrapMode: Text.WordWrap
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
    }

    CustomDial {
        id: dialAMPhase
        x: 689
        y: 40
        width: 64
        height: 64
        maximumValue: 255
        onValueChanged: {
            synthModel.fxAMPhase=dialAMPhase.value;
        }
    }

    Label {
        id: label9
        x: 690
        y: 110
        width: 62
        height: 35
        color: "#ffffff"
        text: qsTr("AM Phase")
        font.pixelSize: 16
        wrapMode: Text.WordWrap
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
    }

    CustomDial {
        id: dialReverbDry
        x: 14
        y: 205
        width: 64
        height: 64
        maximumValue: 255
        onValueChanged: {
            synthModel.fxReverbDry=dialReverbDry.value
        }
    }

    Label {
        id: label10
        x: 35
        y: 275
        color: "#ffffff"
        text: qsTr("Dry")
        font.pixelSize: 16
        horizontalAlignment: Text.AlignHCenter
    }

    CustomDial {
        id: dialReverbWet
        x: 104
        y: 205
        width: 64
        height: 64
        maximumValue: 255
        onValueChanged: {
            synthModel.fxReverbWet=dialReverbWet.value;
        }
    }

    Label {
        id: label11
        x: 122
        y: 275
        width: 28
        height: 17
        color: "#ffffff"
        text: qsTr("Wet")
        font.pixelSize: 16
        horizontalAlignment: Text.AlignHCenter
    }

    CustomDial {
        id: dialReverbDecay
        x: 194
        y: 205
        width: 64
        height: 64
        maximumValue: 255
        onValueChanged: {
            synthModel.fxReverbDecay=dialReverbDecay.value;
        }
    }

    Label {
        id: label12
        x: 203
        y: 275
        width: 46
        height: 17
        color: "#ffffff"
        text: qsTr("Decay")
        font.pixelSize: 16
        horizontalAlignment: Text.AlignHCenter
    }

    CustomDial {
        id: dialReverbDamp
        x: 284
        y: 205
        width: 64
        height: 64
        maximumValue: 255
        onValueChanged: {
            synthModel.fxReverbDamp=dialReverbDamp.value;
        }
    }

    Label {
        id: label13
        x: 293
        y: 275
        width: 46
        height: 17
        color: "#ffffff"
        text: qsTr("Damp")
        font.pixelSize: 16
        horizontalAlignment: Text.AlignHCenter
    }

    SpinBox {
        id: spinReverbMode
        x: 440
        y: 217
        width: 160
        height: 40
        to: 1
        font.pointSize: 14
        onValueChanged: {
            synthModel.fxReverbMode=spinReverbMode.value;
        }
        textFromValue: function(value, locale) {
            var vals=["Plate", "Hall"];

            return vals[value];
        }
    }

    Label {
        id: label14
        x: 374
        y: 229
        width: 46
        height: 17
        color: "#ffffff"
        text: qsTr("Mode")
        font.pixelSize: 16
        horizontalAlignment: Text.AlignRight
    }

    Rectangle {
        id: rectangle2
        x: 698
        y: 175
        width: 90
        height: 2
        color: "#ffffff"
        border.color: "#ffb060"
    }

    Label {
        id: label15
        x: 628
        y: 166
        color: "#ffb060"
        text: qsTr("FX Route")
        font.pixelSize: 16
    }

    Component.onCompleted: {
        updatePage();
    }
}
