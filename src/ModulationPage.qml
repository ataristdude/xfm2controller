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
    id: modulationPage
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
        dialPitchAftertouch.value=synthModel.modPitchAftertouch;
        dialPitchLFOAftertouch.value=synthModel.modPitchLFOAftertouch;
        dialAmplitudeLFOAftertouch.value=synthModel.modAmpLFOAftertouch;
        dialEGBiasAftertouch.value=synthModel.modEnvelopeBiasAftertouch;

        dialPitchRandom.value=synthModel.modPitchRandom;
        dialPitchLFOWheel.value=synthModel.modPitchLFOWheel;
        dialAmplitudeLFOWheel.value=synthModel.modAmpLFOWheel;
        dialEGBiasWheel.value=synthModel.modEnvelopeBiasWheel;

        dialPitchBreath.value=synthModel.modPitchBreath;
        dialPitchLFOBreath.value=synthModel.modPitchLFOBreath;
        dialAmplitudeLFOBreath.value=synthModel.modAmpLFOBreath;
        dialEGBiasBreath.value=synthModel.modEnvelopeBiasBreath;

        dialPitchFoot.value=synthModel.modPitchFoot;
        dialPitchLFOFoot.value=synthModel.modPitchLFOFoot;
        dialAmplitudeLFOFoot.value=synthModel.modAmpLFOFoot;
        dialEGBiasFoot.value=synthModel.modEnvelopeBiasFoot;
    }

    Rectangle {
        anchors.fill: parent
        color: "#505050"
    }


    Label {
        id: label
        x: 144
        y: 10
        color: "#ffffff"
        text: qsTr("Aftertouch")
        font.pixelSize: 16
    }

    Label {
        id: label1
        x: 81
        y: 60
        color: "#ffffff"
        text: qsTr("Pitch")
        font.pixelSize: 16
    }

    CustomDial {
        id: dialPitchAftertouch
        x: 141
        y: 33
        width: 80
        height: 70
        maximumValue: 255
        onValueChanged: {
            synthModel.modPitchAftertouch=dialPitchAftertouch.value;
        }
    }

    CustomDial {
        id: dialPitchLFOAftertouch
        x: 141
        y: 109
        width: 80
        height: 70
        maximumValue: 255
        onValueChanged: {
            synthModel.modPitchLFOAftertouch=dialPitchLFOAftertouch.value;
        }
    }

    CustomDial {
        id: dialAmplitudeLFOAftertouch
        x: 141
        y: 185
        width: 80
        height: 70
        maximumValue: 255
        onValueChanged: {
            synthModel.modAmpLFOAftertouch=dialAmplitudeLFOAftertouch.value;
        }
    }

    CustomDial {
        id: dialEGBiasAftertouch
        x: 141
        y: 261
        width: 80
        height: 70
        maximumValue: 255
        onValueChanged: {
            synthModel.modEnvelopeBiasAftertouch=dialEGBiasAftertouch.value;
        }
    }

    Label {
        id: label2
        x: 50
        y: 136
        color: "#ffffff"
        text: qsTr("Pitch LFO")
        font.pixelSize: 16
    }

    Label {
        id: label3
        x: 13
        y: 212
        color: "#ffffff"
        text: qsTr("Amplitude LFO")
        font.pixelSize: 16
    }

    Label {
        id: label4
        x: 65
        y: 288
        color: "#ffffff"
        text: qsTr("EG Bias")
        font.pixelSize: 16
    }

    Label {
        id: label5
        x: 297
        y: 10
        color: "#ffffff"
        text: qsTr("Wheel/RND")
        font.pixelSize: 16
    }

    CustomDial {
        id: dialPitchRandom
        x: 297
        y: 33
        width: 80
        height: 70
        maximumValue: 255
        onValueChanged: {
            synthModel.modPitchRandom=dialPitchRandom.value;
        }
    }

    CustomDial {
        id: dialPitchLFOWheel
        x: 297
        y: 109
        width: 80
        height: 70
        maximumValue: 255
        onValueChanged: {
            synthModel.modPitchLFOWheel=dialPitchLFOWheel.value;
        }
    }

    CustomDial {
        id: dialAmplitudeLFOWheel
        x: 297
        y: 185
        width: 80
        height: 70
        maximumValue: 255
        onValueChanged: {
            synthModel.modAmpLFOWheel=dialAmplitudeLFOWheel.value;
        }
    }

    CustomDial {
        id: dialEGBiasWheel
        x: 297
        y: 261
        width: 80
        height: 70
        maximumValue: 255
        onValueChanged: {
            synthModel.modEnvelopeBiasWheel=dialEGBiasWheel.value;
        }
    }

    Label {
        id: label6
        x: 470
        y: 10
        color: "#ffffff"
        text: qsTr("Breath")
        font.pixelSize: 16
    }

    CustomDial {
        id: dialPitchBreath
        x: 453
        y: 33
        width: 80
        height: 70
        maximumValue: 255
        onValueChanged: {
            synthModel.modPitchBreath=dialPitchBreath.value;
        }
    }

    CustomDial {
        id: dialPitchLFOBreath
        x: 453
        y: 110
        width: 80
        height: 70
        maximumValue: 255
        onValueChanged: {
            synthModel.modPitchLFOBreath=dialPitchLFOBreath.value;
        }
    }

    CustomDial {
        id: dialAmplitudeLFOBreath
        x: 453
        y: 185
        width: 80
        height: 70
        maximumValue: 255
        onValueChanged: {
            synthModel.modAmpLFOBreath=dialAmplitudeLFOBreath.value;
        }
    }

    CustomDial {
        id: dialEGBiasBreath
        x: 453
        y: 262
        width: 80
        height: 70
        maximumValue: 255
        onValueChanged: {
            synthModel.modEnvelopeBiasBreath=dialEGBiasBreath.value;
        }
    }

    Label {
        id: label7
        x: 633
        y: 10
        color: "#ffffff"
        text: qsTr("Foot")
        font.pixelSize: 16
    }

    CustomDial {
        id: dialPitchFoot
        x: 609
        y: 33
        width: 80
        height: 70
        maximumValue: 255
        onValueChanged: {
            synthModel.modPitchFoot=dialPitchFoot.value;
        }
    }

    CustomDial {
        id: dialPitchLFOFoot
        x: 609
        y: 109
        width: 80
        height: 70
        maximumValue: 255
        onValueChanged: {
            synthModel.modPitchLFOFoot=dialPitchLFOFoot.value;
        }
    }

    CustomDial {
        id: dialAmplitudeLFOFoot
        x: 609
        y: 185
        width: 80
        height: 70
        maximumValue: 255
        onValueChanged: {
            synthModel.modAmpLFOFoot=dialAmplitudeLFOFoot.value;
        }
    }

    CustomDial {
        id: dialEGBiasFoot
        x: 609
        y: 262
        width: 80
        height: 70
        maximumValue: 255
        onValueChanged: {
            synthModel.modEnvelopeBiasFoot=dialEGBiasFoot.value;
        }
    }

    Component.onCompleted: {
        updatePage();
    }
}
