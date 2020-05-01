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
import QtQuick.Controls.Styles 1.4

Item {
    id: effectsPage
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
        dialChorusDry.value=synthModel.fxChorusDry;
        dialChorusWet.value=synthModel.fxChorusWet;
        dialChorusRate.value=synthModel.fxChorusSpeed;
        dialChorusDepth.value=synthModel.fxChorusDepth;
        dialChorusFeedback.value=synthModel.fxChorusFeedback;
        dialChorusPhase.value=synthModel.fxChorusPhase;
        spinChorusMode.value=synthModel.fxChorusMode;

        dialPhaserDry.value=synthModel.fxPhaserDry;
        dialPhaserWet.value=synthModel.fxPhaserWet;
        dialPhaserRate.value=synthModel.fxPhaserSpeed;
        dialPhaserDepth.value=synthModel.fxPhaserDepth;
        dialPhaserOffset.value=synthModel.fxPhaserOffset;
        dialPhaserFeedback.value=synthModel.fxPhaserFeedback;
        dialPhaserPhase.value=synthModel.fxPhaserPhase;
        spinPhaserStages.value=synthModel.fxPhaserStages;
        spinPhaserMode.value=synthModel.fxPhaserMode;

        dialDelayDry.value=synthModel.fxDelayDry;
        dialDelayWet.value=synthModel.fxDelayWet;
        dialDelayTime.value=synthModel.fxDelayTime;
        dialDelayFeedback.value=synthModel.fxDelayFeedback;
        dialDelayTempo.value=synthModel.fxDelayTempo;
        dialDelayMultiplier.value=synthModel.fxDelayMultiplier;
        dialDelayDivider.value=synthModel.fxDelayDivider;
        dialDelayLoPass.value=synthModel.fxDelayLowPass;
        dialDelayHiPass.value=synthModel.fxDelayHighPass;
        spinDelayMode.value=synthModel.fxDelayMode;
    }


    SpinBox {
        id: spinPhaserMode
        x: 676
        y: 182
        width: 115
        height: 40
        to: 2
        font.pointSize: 14
        onValueChanged: {
            synthModel.fxPhaserMode=spinPhaserMode.value;
        }
        textFromValue: function(value, locale) {
            var vals=["M", "S", "C"];

            return vals[value];
        }
    }

    SpinBox {
        id: spinPhaserStages
        x: 676
        y: 130
        width: 115
        height: 40
        to: 12
        from: 0
        font.pointSize: 14
        onValueChanged: {
            synthModel.fxPhaserStages=spinPhaserStages.value;
        }
    }

    Rectangle {
        id: rectangle1
        x: 60
        y: 119
        width: 731
        height: 2
        color: "#ffffff"
        border.color: "#ffb060"
    }

    Rectangle {
        id: rectangle
        x: 61
        y: 9
        width: 731
        height: 2
        color: "#ffffff"
        border.color: "#ffb060"
    }

    CustomDial {
        id: dialChorusDry
        x: 14
        y: 20
        width: 64
        height: 64
        maximumValue: 255
        onValueChanged: {
            synthModel.fxChorusDry=dialChorusDry.value;
        }
    }

    Label {
        id: label4
        x: 33
        y: 90
        color: "#ffffff"
        text: qsTr("Dry")
        font.pixelSize: 16
    }

    CustomDial {
        id: dialChorusWet
        x: 104
        y: 20
        width: 64
        height: 64
        maximumValue: 255
        onValueChanged: {
            synthModel.fxChorusWet=dialChorusWet.value;
        }
    }

    Label {
        id: label5
        x: 122
        y: 90
        color: "#ffffff"
        text: qsTr("Wet")
        font.pixelSize: 16
    }

    CustomDial {
        id: dialChorusRate
        x: 194
        y: 20
        width: 64
        height: 64
        maximumValue: 255
        onValueChanged: {
            synthModel.fxChorusSpeed=dialChorusRate.value;
        }
    }

    Label {
        id: label6
        x: 210
        y: 90
        color: "#ffffff"
        text: qsTr("Rate")
        font.pixelSize: 16
    }

    CustomDial {
        id: dialChorusDepth
        x: 284
        y: 20
        width: 64
        height: 64
        maximumValue: 255
        onValueChanged: {
            synthModel.fxChorusDepth=dialChorusDepth.value;
        }
    }

    Label {
        id: label7
        x: 295
        y: 90
        color: "#ffffff"
        text: qsTr("Depth")
        font.pixelSize: 16
    }

    CustomDial {
        id: dialChorusFeedback
        x: 374
        y: 20
        width: 64
        height: 64
        maximumValue: 255
        onValueChanged: {
            synthModel.fxChorusFeedback=dialChorusFeedback.value;
        }
    }

    Label {
        id: label8
        x: 374
        y: 90
        color: "#ffffff"
        text: qsTr("Feedback")
        font.pixelSize: 16
    }

    CustomDial {
        id: dialChorusPhase
        x: 464
        y: 20
        width: 64
        height: 64
        maximumValue: 255
        onValueChanged: {
            synthModel.fxChorusPhase=dialChorusPhase.value;
        }
    }

    Label {
        id: label9
        x: 462
        y: 90
        color: "#ffffff"
        text: qsTr("L/R Phase")
        font.pixelSize: 16
    }

    Label {
        id: label10
        x: 579
        y: 44
        color: "#ffffff"
        text: qsTr("Mode")
        font.pixelSize: 16
    }

    CustomDial {
        id: dialPhaserDry
        x: 14
        y: 137
        width: 64
        height: 64
        maximumValue: 255
        onValueChanged: {
            synthModel.fxPhaserDry=dialPhaserDry.value;
        }
    }

    Label {
        id: label15
        x: 33
        y: 207
        color: "#ffffff"
        text: qsTr("Dry")
        font.pixelSize: 16
    }

    CustomDial {
        id: dialPhaserWet
        x: 104
        y: 137
        width: 64
        height: 64
        maximumValue: 255
        onValueChanged: {
            synthModel.fxPhaserWet=dialPhaserWet.value;
        }
    }

    Label {
        id: label16
        x: 123
        y: 207
        color: "#ffffff"
        text: qsTr("Wet")
        font.pixelSize: 16
    }

    CustomDial {
        id: dialPhaserRate
        x: 194
        y: 137
        width: 64
        height: 64
        maximumValue: 255
        onValueChanged: {
            synthModel.fxPhaserSpeed=dialPhaserRate.value;
        }
    }

    Label {
        id: label17
        x: 210
        y: 207
        color: "#ffffff"
        text: qsTr("Rate")
        font.pixelSize: 16
    }

    CustomDial {
        id: dialPhaserDepth
        x: 284
        y: 137
        width: 64
        height: 64
        maximumValue: 255
        onValueChanged: {
            synthModel.fxPhaserDepth=dialPhaserDepth.value;
        }
    }

    Label {
        id: label18
        x: 295
        y: 207
        color: "#ffffff"
        text: qsTr("Depth")
        font.pixelSize: 16
    }

    CustomDial {
        id: dialPhaserFeedback
        x: 374
        y: 137
        width: 64
        height: 64
        maximumValue: 255
        onValueChanged: {
            synthModel.fxPhaserFeedback=dialPhaserFeedback.value;
        }
    }

    Label {
        id: label19
        x: 374
        y: 207
        color: "#ffffff"
        text: qsTr("Feedback")
        font.pixelSize: 16
    }

    CustomDial {
        id: dialPhaserPhase
        x: 464
        y: 137
        width: 64
        height: 64
        maximumValue: 255
        onValueChanged: {
            synthModel.fxPhaserPhase=dialPhaserPhase.value;
        }
    }

    Label {
        id: label20
        x: 464
        y: 207
        color: "#ffffff"
        text: qsTr("L/R Phase")
        font.pixelSize: 16
    }

    SpinBox {
        id: spinChorusMode
        x: 633
        y: 32
        width: 158
        height: 40
        to: 3
        onValueChanged: {
            synthModel.fxChorusMode=spinChorusMode.value;
        }
        textFromValue: function(value, locale) {
            var vals=["CHO (L)", "CHO (S)", "FLA (L)", "FLA (S)"];

            return vals[value];
        }
    }

    Label {
        id: label21
        x: 5
        y: 0
        color: "#ffb060"
        text: qsTr("Chorus")
        font.pixelSize: 16
    }

    Label {
        id: label22
        x: 5
        y: 111
        color: "#ffb060"
        text: qsTr("Phaser")
        font.pixelSize: 16
    }

    CustomDial {
        id: dialPhaserOffset
        x: 554
        y: 137
        width: 64
        height: 64
        maximumValue: 255
        onValueChanged: {
            synthModel.fxPhaserOffset=dialPhaserOffset.value;
        }
    }

    Label {
        id: label23
        x: 564
        y: 207
        color: "#ffffff"
        text: qsTr("Offset")
        font.pixelSize: 16
        horizontalAlignment: Text.AlignHCenter
    }

    Label {
        id: label11
        x: 624
        y: 142
        color: "#ffffff"
        text: qsTr("Stages")
        font.pixelSize: 16
        horizontalAlignment: Text.AlignRight
    }

    Label {
        id: label12
        x: 628
        y: 194
        color: "#ffffff"
        text: qsTr("Mode")
        font.pixelSize: 16
        horizontalAlignment: Text.AlignRight
    }

    Label {
        id: label24
        x: 5
        y: 230
        color: "#ffb060"
        text: qsTr("Delay")
        font.pixelSize: 16
    }

    Rectangle {
        id: rectangle2
        x: 61
        y: 238
        width: 731
        height: 2
        color: "#ffffff"
        border.color: "#ffb060"
    }

    CustomDial {
        id: dialDelayDry
        x: 14
        y: 260
        width: 64
        height: 64
        maximumValue: 255
        onValueChanged: {
            synthModel.fxDelayDry=dialDelayDry.value;
        }
    }

    Label {
        id: label25
        x: 33
        y: 325
        color: "#ffffff"
        text: qsTr("Dry")
        font.pixelSize: 16
    }

    CustomDial {
        id: dialDelayWet
        x: 104
        y: 260
        width: 64
        height: 64
        maximumValue: 255
        onValueChanged: {
            synthModel.fxDelayWet=dialDelayWet.value;
        }
    }

    Label {
        id: label26
        x: 122
        y: 325
        color: "#ffffff"
        text: qsTr("Wet")
        font.pixelSize: 16
    }

    CustomDial {
        id: dialDelayTime
        x: 194
        y: 260
        width: 64
        height: 64
        maximumValue: 255
        onValueChanged: {
            synthModel.fxDelayTime=dialDelayTime.value;
        }
    }

    Label {
        id: label27
        x: 209
        y: 325
        color: "#ffffff"
        text: qsTr("Time")
        font.pixelSize: 16
    }

    CustomDial {
        id: dialDelayFeedback
        x: 284
        y: 260
        width: 64
        height: 64
        maximumValue: 255
        onValueChanged: {
            synthModel.fxDelayFeedback=dialDelayFeedback.value;
        }
    }

    Label {
        id: label28
        x: 284
        y: 325
        color: "#ffffff"
        text: qsTr("Feedback")
        font.pixelSize: 16
    }

    CustomDial {
        id: dialDelayTempo
        x: 374
        y: 260
        width: 64
        height: 64
        maximumValue: 255
        onValueChanged: {
            synthModel.fxDelayTempo=dialDelayTempo.value;
        }
    }

    Label {
        id: label29
        x: 383
        y: 325
        color: "#ffffff"
        text: qsTr("Tempo")
        font.pixelSize: 16
    }

    CustomDial {
        id: dialDelayMultiplier
        x: 464
        y: 260
        width: 64
        height: 64
        maximumValue: 255
        onValueChanged: {
            synthModel.fxDelayMultiplier=dialDelayMultiplier.value;
        }
    }

    Label {
        id: label30
        x: 467
        y: 325
        color: "#ffffff"
        text: qsTr("Multiply")
        font.pixelSize: 16
    }

    CustomDial {
        id: dialDelayDivider
        x: 554
        y: 260
        width: 64
        height: 64
        maximumValue: 255
        onValueChanged: {
            synthModel.fxDelayDivider=dialDelayDivider.value;
        }
    }

    Label {
        id: label31
        x: 565
        y: 325
        color: "#ffffff"
        text: qsTr("Divide")
        font.pixelSize: 16
    }

    Label {
        id: label13
        x: 628
        y: 263
        color: "#ffffff"
        text: qsTr("Mode")
        font.pixelSize: 16
        horizontalAlignment: Text.AlignRight
    }

    SpinBox {
        id: spinDelayMode
        x: 676
        y: 251
        width: 115
        height: 40
        to: 2
        font.pointSize: 14
        onValueChanged: {
            synthModel.fxDelayMode=spinDelayMode.value;
        }
        textFromValue: function(value, locale) {
            var vals=["S", "C", "B"];

            return vals[value];
        }
    }

    CustomDial {
        id: dialDelayLoPass
        x: 674
        y: 301
        width: 48
        height: 48
        maximumValue: 255
        onValueChanged: {
            synthModel.fxDelayLowPass=dialDelayLoPass.value;
        }
    }

    CustomDial {
        id: dialDelayHiPass
        x: 747
        y: 301
        width: 48
        height: 48
        maximumValue: 255
        onValueChanged: {
            synthModel.fxDelayHighPass=dialDelayHiPass.value;
        }
    }

    Label {
        id: label14
        x: 651
        y: 317
        color: "#ffffff"
        text: qsTr("Lo")
        font.pixelSize: 16
        horizontalAlignment: Text.AlignRight
    }

    Label {
        id: label32
        x: 726
        y: 317
        width: 16
        height: 17
        color: "#ffffff"
        text: qsTr("Hi")
        font.pixelSize: 16
        horizontalAlignment: Text.AlignRight
    }

    Component.onCompleted: {
        updatePage();
    }
}
