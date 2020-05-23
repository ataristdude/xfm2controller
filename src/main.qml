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
import QtQuick.Window 2.12
import QtQuick.Controls 2.3

Window {
    id: mainWindow
    visible: true
    width: 800
    height: 480
    title: qsTr("XFm2 Synth")

    // Note: This app was designed to run on a Raspberry Pi with an 800x480 touch screen
    // Remove the visibility line below if you want to run it as a Desktop application!
    visibility: "FullScreen"

    Rectangle {
        anchors.fill: parent
        color: "#505050"
    }

    CommonPage {
        id: commonPage
        anchors.fill: tabArea
        visible: true
    }

    AlgorithmPage {
        id: algorithmPage
        anchors.fill: tabArea
        visible: false
    }

    OperatorPage {
        id: operatorPage
        anchors.fill: tabArea
        visible: false
    }

    EnvelopePage {
        id: envelopePage
        anchors.fill: tabArea
        visible: false
    }

    LFOPage {
        id: lfoPage
        anchors.fill: tabArea
        visible: false
    }

    ModulationPage {
        id: modulationPage
        anchors.fill: tabArea
        visible: false
    }

    ArpeggiatorPage {
        id: arpeggiatorPage
        anchors.fill: tabArea
        visible: false
    }

    EffectsPage {
        id: effectsPage
        anchors.fill: tabArea
        visible: false
    }

    EffectsPage2 {
        id: effectsPage2
        anchors.fill: tabArea
        visible: false
    }

    Label {
        id: element
        x: 34
        y: 34
        color: "#ffb060"
        text: qsTr("Patch")
        font.pixelSize: 22
    }

    SpinBox {
        id: spinPatchNumber
        x: 107
        y: 27
        font.pixelSize: 22
        to: 127

        onValueChanged: {
            synthModel.patchNumber=spinPatchNumber.value;
        }
    }

    GroupBox {
        id: groupBox
        x: 0
        y: 79
        width: 800
        height: 1
        title: qsTr("")
    }

    TabBar {
        id: tabBar
        y: 440
        position: TabBar.Footer
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0

        TabButton {
            id: tabButtonCommon
            x: 0
            y: 0
            text: qsTr("Common")
        }

        TabButton {
            id: tabButtonAlgorithm
            text: qsTr("ALGO")
        }

        TabButton {
            id: tabButtonOperator
            text: qsTr("OPER")
        }

        TabButton {
            id: tabButtonEnvelope
            text: qsTr("ENV")
        }

        TabButton {
            id: tabButtonLFO
            text: qsTr("LFO")
        }

        TabButton {
            id: tabButtonModulation
            text: qsTr("MOD")
        }

        TabButton {
            id: tabButtonArpeggiator
            text: qsTr("ARP")
        }

        TabButton {
            id: tabButtonEffects
            text: qsTr("FX1")
        }

        TabButton {
            id: tabButtonEffects2
            text: qsTr("FX2")
        }

        onCurrentIndexChanged: {
            switch (tabBar.currentIndex) {
            case 0: // Common
                commonPage.visible=true;
                algorithmPage.visible=false;
                operatorPage.visible=false;
                envelopePage.visible=false;
                lfoPage.visible=false;
                modulationPage.visible=false;
                arpeggiatorPage.visible=false;
                effectsPage.visible=false;
                effectsPage2.visible=false;
                break;

            case 1: // Algorithm
                commonPage.visible=true;
                algorithmPage.visible=true;
                operatorPage.visible=false;
                envelopePage.visible=false;
                lfoPage.visible=false;
                modulationPage.visible=false;
                arpeggiatorPage.visible=false;
                effectsPage.visible=false;
                effectsPage2.visible=false;
                break;

            case 2: // Operator
                commonPage.visible=false;
                algorithmPage.visible=false;
                operatorPage.visible=true;
                envelopePage.visible=false;
                lfoPage.visible=false;
                modulationPage.visible=false;
                arpeggiatorPage.visible=false;
                effectsPage.visible=false;
                effectsPage2.visible=false;
                break;

            case 3: // Envelope
                commonPage.visible=false;
                algorithmPage.visible=false;
                operatorPage.visible=false;
                envelopePage.visible=true;
                lfoPage.visible=false;
                modulationPage.visible=false;
                arpeggiatorPage.visible=false;
                effectsPage.visible=false;
                effectsPage2.visible=false;
                break;

            case 4: // LFO
                commonPage.visible=false;
                algorithmPage.visible=false;
                operatorPage.visible=false;
                envelopePage.visible=false;
                lfoPage.visible=true;
                modulationPage.visible=false;
                arpeggiatorPage.visible=false;
                effectsPage.visible=false;
                effectsPage2.visible=false;
                break;

            case 5: // Modulation
                commonPage.visible=false;
                algorithmPage.visible=false;
                operatorPage.visible=false;
                envelopePage.visible=false;
                lfoPage.visible=false;
                modulationPage.visible=true;
                arpeggiatorPage.visible=false;
                effectsPage.visible=false;
                effectsPage2.visible=false;
                break;

            case 6: // Arpeggiator
                commonPage.visible=false;
                algorithmPage.visible=false;
                operatorPage.visible=false;
                envelopePage.visible=false;
                lfoPage.visible=false;
                modulationPage.visible=false;
                arpeggiatorPage.visible=true;
                effectsPage.visible=false;
                effectsPage2.visible=false;
                break;

            case 7: // Effects
                commonPage.visible=false;
                algorithmPage.visible=false;
                operatorPage.visible=false;
                envelopePage.visible=false;
                lfoPage.visible=false;
                modulationPage.visible=false;
                arpeggiatorPage.visible=false;
                effectsPage.visible=true;
                effectsPage2.visible=false;
                break;

            case 8: // Effects 2
                commonPage.visible=false;
                algorithmPage.visible=false;
                operatorPage.visible=false;
                envelopePage.visible=false;
                lfoPage.visible=false;
                modulationPage.visible=false;
                arpeggiatorPage.visible=false;
                effectsPage.visible=false;
                effectsPage2.visible=true;
                break;

            default:
                break;
            }
        }
    }

    Item {
        id: tabArea
        x: 0
        y: 83
        width: 800
        height: 357
    }

    Button {
        id: buttonWrite
        x: 674
        y: 27
        text: qsTr("WRITE")
        font.pointSize: 16
        onClicked: {
            popupWriteMessage.open();
        }
    }

    Button {
        id: buttonReload
        x: 280
        y: 27
        text: qsTr("READ")
        font.pointSize: 16
        onClicked: {
            popupReloadMessage.open();
        }
    }

    Button {
        id: buttonInit
        x: 417
        y: 27
        text: qsTr("INIT")
        font.pointSize: 16
        onClicked: {
            popupInitMessage.open();
        }
    }

    PopupMessage {
        id: popupInitMessage
        titleText: "Initialise Patch"
        detailText: "Do you want to init this patch?"
        okButtonText: "Yes"
        cancelButtonText: "No"
        onOkClicked: {
            synthModel.initPatchBuffer();
        }
    }

    PopupMessage {
        id: popupReloadMessage
        titleText: "Load Patch"
        detailText: "Do you want to reload this patch?"
        okButtonText: "Yes"
        cancelButtonText: "No"
        onOkClicked: {
            synthModel.reloadPatch();
        }
    }

    PopupMessage {
        id: popupWriteMessage
        titleText: "Write Patch"
        detailText: "Do you want to save this patch?"
        okButtonText: "Yes"
        cancelButtonText: "No"
        onOkClicked: {
            synthModel.writePatchBuffer(-1);
        }
    }

    Component.onCompleted: {
        spinPatchNumber.value=synthModel.patchNumber;
        synthModel.readPatchBuffer();
    }
}
