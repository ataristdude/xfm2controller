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
    id: lfoPage
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
        spinWave.value=synthModel.lfoWave;
        spinSync.value=synthModel.lfoSync;
        dialSpeed.value=synthModel.lfoSpeed;
        dialFade.value=synthModel.lfoFade;
        dialPitch.value=synthModel.lfoDepthPitch;
        dialAmp.value=synthModel.lfoDepthAmplitude;
    }

    Label {
        id: label
        x: 27
        y: 37
        color: "#ffffff"
        text: qsTr("Wave")
        font.pixelSize: 16
    }

    CustomDial {
        id: dialSpeed
        x: 51
        y: 130
        width: 136
        height: 136
        maximumValue: 255
        onValueChanged: {
            synthModel.lfoSpeed=dialSpeed.value;
        }
    }

    SpinBox {
        id: spinWave
        x: 84
        y: 26
        width: 167
        height: 40
        to: 5
        onValueChanged: {
            synthModel.lfoWave=spinWave.value
        }
        textFromValue: function(value, locale) {
            var vals=["TRI", "SQR", "SAW UP", "SAW DN", "SIN", "RND"];

            return vals[value];
        }
    }

    Label {
        id: label1
        x: 98
        y: 280
        width: 42
        height: 17
        color: "#ffffff"
        text: qsTr("Rate")
        font.pixelSize: 16
    }

    Label {
        id: label2
        x: 304
        y: 37
        color: "#ffffff"
        text: qsTr("Sync")
        font.pixelSize: 16
    }

    SpinBox {
        id: spinSync
        x: 353
        y: 26
        width: 202
        height: 40
        to: 3
        onValueChanged: {
            synthModel.lfoSync=spinSync.value;
        }

        textFromValue: function(value, locale) {
            var vals=["SINGLE FREE", "SINGLE KEY", "MULTI FREE", "MULTI KEY"];

            return vals[value];
        }
    }

    CustomDial {
        id: dialFade
        x: 222
        y: 130
<<<<<<< HEAD
        width: 136
        height: 136
=======
>>>>>>> 5f1b6151ec4d2bf472cad1981025fb954064533c
        maximumValue: 255
        onValueChanged: {
            synthModel.lfoFade=synthModel.lfoFade;
        }
    }

    Label {
        id: label3
        x: 269
        y: 280
        width: 42
        height: 17
        color: "#ffffff"
        text: qsTr("Fade")
        font.pixelSize: 16
    }

    CustomDial {
        id: dialPitch
        x: 431
        y: 130
        width: 136
        height: 136
        maximumValue: 255
        onValueChanged: {
            synthModel.lfoDepthPitch=dialPitch.value;
        }
    }

    Label {
        id: label4
        x: 455
        y: 280
        width: 89
        height: 17
        color: "#ffffff"
        text: qsTr("Depth Pitch")
        font.pixelSize: 16
    }

    CustomDial {
        id: dialAmp
        x: 603
        y: 130
        width: 136
        height: 136
        maximumValue: 255
        onValueChanged: {
            synthModel.lfoDepthAmplitude=dialAmp.value;
        }
    }

    Label {
        id: label5
        x: 604
        y: 280
        width: 134
        height: 17
        color: "#ffffff"
        text: qsTr("Depth Amplitude")
        font.pixelSize: 16
        horizontalAlignment: Text.AlignHCenter
    }

    Component.onCompleted: {
        updatePage();
    }

}

/*##^##
Designer {
    D{i:1;anchors_height:400;anchors_x:0;anchors_y:0}D{i:2;anchors_height:400;anchors_x:0;anchors_y:0}
}
##^##*/
