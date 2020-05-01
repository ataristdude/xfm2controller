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
    id: arpeggiatorPage
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
        spinArpMode.value=synthModel.arpeggiatorMode;
        spinTempo.value=synthModel.arpeggiatorTempo === 0 ? 0 : synthModel.arpeggiatorTempo-49;
        spinMultiplier.value=synthModel.arpeggiatorTempoMultiplier;
        spinOctaveRange.value=synthModel.arpeggiatorOctaveRange;
    }


    Rectangle {
        anchors.fill: parent
        color: "#505050"
    }

    SpinBox {
        id: spinArpMode
        x: 110
        y: 24
        width: 160
        height: 40
        to: 5
        onValueChanged: {
            synthModel.arpeggiatorMode=spinArpMode.value;
        }
        textFromValue: function(value, locale) {
            var vals=["OFF", "UP", "DOWN", "UP/DOWN", "PLAYED", "RANDOM"];

            return vals[value];
        }
    }

    Label {
        id: label
        x: 49
        y: 35
        color: "#ffffff"
        text: qsTr("Mode")
        font.pixelSize: 16
    }

    SpinBox {
        id: spinTempo
        x: 110
        y: 98
        width: 160
        height: 40
        to: 206
        onValueChanged: {
            if (spinTempo.value === 0) {
                synthModel.arpeggiatorTempo=0;
            } else {
                synthModel.arpeggiatorTempo=spinTempo.value+49;
            }
        }
        textFromValue: function(value, locale) {
            if (value === 0) {
                return "MIDI";
            }

            return (value+49).toString();
        }
    }

    Label {
        id: label1
        x: 41
        y: 110
        color: "#ffffff"
        text: qsTr("Tempo")
        font.pixelSize: 16
    }

    SpinBox {
        id: spinMultiplier
        x: 444
        y: 98
        to: 255
        onValueChanged: {
            synthModel.arpeggiatorTempoMultiplier=spinMultiplier.value;
        }
    }

    Label {
        id: label2
        x: 310
        y: 110
        color: "#ffffff"
        text: qsTr("Tempo Multiplier")
        font.pixelSize: 16
    }

    SpinBox {
        id: spinOctaveRange
        x: 110
        y: 170
        to: 9
        onValueChanged: {
            synthModel.arpeggiatorOctaveRange=spinOctaveRange.value;
        }
    }

    Label {
        id: label3
        x: 17
        y: 182
        color: "#ffffff"
        text: qsTr("Oct Range")
        font.pixelSize: 16
    }


    Component.onCompleted: {
        updatePage();
    }

}
