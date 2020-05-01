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
    id: commonPage
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
        sliderOutput.value=synthModel.outputLevel
        dialVolume.value=synthModel.masterVolume
        dialPan.value=synthModel.masterPan
        spinBendUp.value=synthModel.masterPitchBendUp
        spinBendDown.value=synthModel.masterPitchBendDown
        spinTranspose.value=synthModel.masterTranspose-24
        spinVelocityOffset.value=synthModel.masterVelocityOffset
        sliderPortamentoTime.value=synthModel.portamentoTime
        switchLegato.checked=synthModel.masterLegato != 0
        spinPortamentoMode.value=synthModel.portamentoMode
        textName.text=synthModel.patchName
    }

    TextField {
        id: textName
        x: 101
        y: 20
        width: 410
        height: 38
        verticalAlignment: Text.AlignVCenter
        font.pixelSize: 18
        cursorVisible: false

        background: Rectangle {
            border.width: 1
            border.color: "#000000"
            color: "#ffffff"
            radius: 4
        }

        onTextChanged: {
            synthModel.patchName=textName.text;
        }

        onPressed: {
            keyboard.visible=true;
            textName.cursorVisible=true;
        }
    }

    Slider {
        id: sliderOutput
        x: 471
        y: 146
        width: 40
        height: 161
        to: 255
        orientation: Qt.Vertical
        onValueChanged: {
            synthModel.outputLevel=sliderOutput.value;
        }
    }

    CustomDial {
        id: dialVolume
        x: 627
        y: 15
        width: 136
        height: 136
        maximumValue: 255
        onValueChanged: {
            synthModel.masterVolume=dialVolume.value;
        }
    }

    Label {
        id: label1
        x: 669
        y: 162
        color: "#ffffff"
        text: qsTr("Volume")
        font.pixelSize: 16
    }

    Label {
        id: label
        x: 455
        y: 313
        width: 73
        height: 38
        color: "#ffffff"
        text: qsTr("Output Level")
        font.pixelSize: 16
        wrapMode: Text.WordWrap
        horizontalAlignment: Text.AlignHCenter
    }

    CustomDial {
        id: dialPan
        x: 627
        y: 192
        width: 136
        height: 136
        maximumValue: 255
        onValueChanged: {
            synthModel.masterPan=dialPan.value;
        }
    }

    Label {
        id: label3
        x: 27
        y: 95
        color: "#ffffff"
        text: qsTr("Bend Up")
        font.pixelSize: 16
    }

    SpinBox {
        id: spinBendUp
        x: 101
        y: 84
        to: 127
        onValueChanged: {
            synthModel.masterPitchBendUp=spinBendUp.value
        }
    }

    Label {
        id: label2
        x: 682
        y: 332
        color: "#ffffff"
        text: qsTr("Pan")
        font.pixelSize: 16
        horizontalAlignment: Text.AlignHCenter
    }

    Label {
        id: label4
        x: 5
        y: 154
        color: "#ffffff"
        text: qsTr("Bend Down")
        font.pixelSize: 16
    }

    SpinBox {
        id: spinBendDown
        x: 101
        y: 143
        to: 127
        onValueChanged: {
            synthModel.masterPitchBendDown=spinBendDown.value
        }
    }

    Label {
        id: label5
        x: 282
        y: 95
        color: "#ffffff"
        text: qsTr("Transpose")
        font.pixelSize: 16
    }

    SpinBox {
        id: spinTranspose
        x: 371
        y: 84
        from: -24
        to: 24
        onValueChanged: {
            synthModel.masterTranspose=spinTranspose.value+24
        }
    }

    Label {
        id: label6
        x: 8
        y: 324
        width: 81
        height: 17
        color: "#ffffff"
        text: qsTr("Vel. Offset")
        font.pixelSize: 16
    }

    SpinBox {
        id: spinVelocityOffset
        x: 101
        y: 312
        to: 127
        from: 0
        onValueChanged: {
            synthModel.masterVelocityOffset=spinVelocityOffset.value
        }
    }

    Slider {
        id: sliderPortamentoTime
        x: 371
        y: 146
        width: 40
        height: 161
        orientation: Qt.Vertical
        to: 255
        onValueChanged: {
            synthModel.portamentoTime=sliderPortamentoTime.value;
        }
    }

    Switch {
        id: switchLegato
        x: 94
        y: 203
        text: qsTr("<font color='white'>Mono</font>")
        font.pixelSize: 16
        onCheckedChanged: {
            synthModel.masterLegato=switchLegato.checked ? 1 : 0
        }
    }

    Label {
        id: label7
        x: 347
        y: 313
        width: 88
        height: 38
        color: "#ffffff"
        text: qsTr("Portamento Time")
        font.pixelSize: 16
        horizontalAlignment: Text.AlignHCenter
        wrapMode: Text.WordWrap
    }

    Label {
        id: label8
        x: 58
        y: 213
        height: 17
        color: "#ffffff"
        text: qsTr("Poly")
        font.pixelSize: 16
    }

    Label {
        id: label9
        x: -11
        y: 267
        width: 100
        height: 36
        color: "#ffffff"
        text: qsTr("Portamento Mode")
        font.pixelSize: 16
        wrapMode: Text.WordWrap
        horizontalAlignment: Text.AlignRight
    }

    SpinBox {
        id: spinPortamentoMode
        x: 101
        y: 265
        width: 178
        height: 40
        to: 2
        onValueChanged: {
            synthModel.portamentoMode=spinPortamentoMode.value
        }
        textFromValue: function(value, locale) {
            var clist=["OFF", "ALWAYS", "FINGERED"];

            return clist[value];
        }
    }

    Label {
        id: label10
        x: 2
        y: 29
        color: "#ffffff"
        text: qsTr("Patch Name")
        font.pixelSize: 16
    }

    /* This custom keyboard is required on the Raspberry Pi/Touch screen implementation
     * but you won't need it for a Desktop version.
     */
    CustomKeyboard {
        id: keyboard
        width: 800
        height: 260
        x: 0
        y: 97
        visible: false;
        z: 1000

        onKeyPressed: {
            if (keyval === "LEFT") {
                if (textName.cursorPosition > 0) {
                    textName.cursorPosition=textName.cursorPosition-1;
                    textName.cursorVisible=true;
                    textName.focus=true;
                }
            } else if (keyval === "RIGHT") {
                if (textName.cursorPosition < textName.text.length) {
                    textName.cursorPosition=textName.cursorPosition+1;
                    textName.cursorVisible=true;
                    textName.focus=true;
                }
            } else if (keyval === "DEL") {
                if (textName.cursorPosition > 0) {
                    var oldpos=textName.cursorPosition;

                    var leftText=textName.text.substring(0, oldpos-1);
                    var rightText=textName.text.substring(oldpos, textName.text.length);

                    textName.text=leftText+""+rightText;
                    textName.cursorPosition=oldpos-1;
                    textName.cursorVisible=true;
                    textName.focus=true;
                }
            } else if (keyval === "ENTER") {    // Dismiss and move to next field
                keyboard.visible=false;
                textName.cursorVisible=false;
            } else {
                var charToInsert=keyval;
                if (textName.cursorPosition > 0) {
                    var prevchar=textName.text.charAt(textName.cursorPosition-1);

                    if (prevchar !== ' ') {
                        charToInsert=charToInsert.toLowerCase();
                    }
                }
                textName.insert(textName.cursorPosition, charToInsert);
                textName.focus=true;
            }
        }

    }

    TapHandler {
        onTapped: {
            keyboard.visible=false;
            textName.cursorVisible=false;
        }
        onCanceled: {
        }
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
