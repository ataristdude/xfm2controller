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
    id: algorithmPage
    width: 800
    height: 357

    Connections {
        target: synthModel
        onPatchNumberChanged: {
            updatePage();
        }
        onOperatorHasChanged: {
            updatePage();
        }
    }

    function updatePage()
    {
        checkCarrier1.checked=synthModel.isOperatorACarrier(0);
        checkCarrier2.checked=synthModel.isOperatorACarrier(1);
        checkCarrier3.checked=synthModel.isOperatorACarrier(2);
        checkCarrier4.checked=synthModel.isOperatorACarrier(3);
        checkCarrier5.checked=synthModel.isOperatorACarrier(4);
        checkCarrier6.checked=synthModel.isOperatorACarrier(5);

        checkModulate11.checked=synthModel.isOperatorModulating(0, 0);
        checkModulate21.checked=synthModel.isOperatorModulating(1, 0);
        checkModulate31.checked=synthModel.isOperatorModulating(2, 0);
        checkModulate41.checked=synthModel.isOperatorModulating(3, 0);
        checkModulate51.checked=synthModel.isOperatorModulating(4, 0);
        checkModulate61.checked=synthModel.isOperatorModulating(5, 0);

        checkModulate12.checked=synthModel.isOperatorModulating(0, 1);
        checkModulate22.checked=synthModel.isOperatorModulating(1, 1);
        checkModulate32.checked=synthModel.isOperatorModulating(2, 1);
        checkModulate42.checked=synthModel.isOperatorModulating(3, 1);
        checkModulate52.checked=synthModel.isOperatorModulating(4, 1);
        checkModulate62.checked=synthModel.isOperatorModulating(5, 1);

        checkModulate13.checked=synthModel.isOperatorModulating(0, 2);
        checkModulate23.checked=synthModel.isOperatorModulating(1, 2);
        checkModulate33.checked=synthModel.isOperatorModulating(2, 2);
        checkModulate43.checked=synthModel.isOperatorModulating(3, 2);
        checkModulate53.checked=synthModel.isOperatorModulating(4, 2);
        checkModulate63.checked=synthModel.isOperatorModulating(5, 2);

        checkModulate14.checked=synthModel.isOperatorModulating(0, 3);
        checkModulate24.checked=synthModel.isOperatorModulating(1, 3);
        checkModulate34.checked=synthModel.isOperatorModulating(2, 3);
        checkModulate44.checked=synthModel.isOperatorModulating(3, 3);
        checkModulate54.checked=synthModel.isOperatorModulating(4, 3);
        checkModulate64.checked=synthModel.isOperatorModulating(5, 3);

        checkModulate15.checked=synthModel.isOperatorModulating(0, 4);
        checkModulate25.checked=synthModel.isOperatorModulating(1, 4);
        checkModulate35.checked=synthModel.isOperatorModulating(2, 4);
        checkModulate45.checked=synthModel.isOperatorModulating(3, 4);
        checkModulate55.checked=synthModel.isOperatorModulating(4, 4);
        checkModulate65.checked=synthModel.isOperatorModulating(5, 4);

        checkModulate16.checked=synthModel.isOperatorModulating(0, 5);
        checkModulate26.checked=synthModel.isOperatorModulating(1, 5);
        checkModulate36.checked=synthModel.isOperatorModulating(2, 5);
        checkModulate46.checked=synthModel.isOperatorModulating(3, 5);
        checkModulate56.checked=synthModel.isOperatorModulating(4, 5);
        checkModulate66.checked=synthModel.isOperatorModulating(5, 5);
    }

    Rectangle {
        anchors.fill: parent
        color: "#505050"

        Grid {
            id: gridMatrix
            x: 14
            y: 14
            width: 383
            height: 335
            rows: 8
            columns: 7
            spacing: 0

            Label {
                id: heading1
                width: 100
                height: 40
                color: "#ffffff"
                text: qsTr("Operator")
                font.pixelSize: 16
                verticalAlignment: Text.AlignVCenter
            }
            Label {
                id: heading2
                width: 46
                height: 40
                color: "#ffffff"
                text: qsTr("1")
                font.pixelSize: 16
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
            }
            Label {
                id: heading3
                width: 46
                height: 40
                color: "#ffffff"
                text: qsTr("2")
                font.pixelSize: 16
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
            }
            Label {
                id: heading4
                width: 46
                height: 40
                color: "#ffffff"
                text: qsTr("3")
                font.pixelSize: 16
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
            }
            Label {
                id: heading5
                width: 46
                height: 40
                color: "#ffffff"
                text: qsTr("4")
                font.pixelSize: 16
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
            }
            Label {
                id: heading6
                width: 46
                height: 40
                color: "#ffffff"
                text: qsTr("5")
                font.pixelSize: 16
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
            }
            Label {
                id: heading7
                width: 46
                height: 40
                color: "#ffffff"
                text: qsTr("6")
                font.pixelSize: 16
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
            }
            Label {
                id: row1
                width: 100
                height: 40
                color: "#ffffff"
                text: qsTr("Carrier")
                font.pixelSize: 16
                verticalAlignment: Text.AlignVCenter
            }

            CheckBox {
                id: checkCarrier1
                text: qsTr("")
                display: AbstractButton.IconOnly
                onCheckedChanged: {
                    synthModel.makeOperatorACarrier(0, checkCarrier1.checked);
                }
            }

            CheckBox {
                id: checkCarrier2
                text: qsTr("")
                display: AbstractButton.IconOnly
                onCheckedChanged: {
                    synthModel.makeOperatorACarrier(1, checkCarrier2.checked);
                }
            }

            CheckBox {
                id: checkCarrier3
                text: qsTr("")
                display: AbstractButton.IconOnly
                onCheckedChanged: {
                    synthModel.makeOperatorACarrier(2, checkCarrier3.checked);
                }
            }

            CheckBox {
                id: checkCarrier4
                text: qsTr("")
                display: AbstractButton.IconOnly
                onCheckedChanged: {
                    synthModel.makeOperatorACarrier(3, checkCarrier4.checked);
                }
            }

            CheckBox {
                id: checkCarrier5
                text: qsTr("")
                display: AbstractButton.IconOnly
                onCheckedChanged: {
                    synthModel.makeOperatorACarrier(4, checkCarrier5.checked);
                }
            }

            CheckBox {
                id: checkCarrier6
                text: qsTr("")
                display: AbstractButton.IconOnly
                onCheckedChanged: {
                    synthModel.makeOperatorACarrier(5, checkCarrier6.checked);
                }
            }

            Label {
                id: row2
                width: 100
                height: 40
                color: "#ffffff"
                text: qsTr("Modulate 1")
                font.pixelSize: 16
                verticalAlignment: Text.AlignVCenter
            }

            CheckBox {
                id: checkModulate11
                text: qsTr("")
                display: AbstractButton.IconOnly
                onCheckedChanged: {
                    synthModel.makeOperatorModulate(0, 0, checkModulate11.checked);
                }
            }

            CheckBox {
                id: checkModulate21
                text: qsTr("")
                display: AbstractButton.IconOnly
                onCheckedChanged: {
                    synthModel.makeOperatorModulate(1, 0, checkModulate21.checked);
                }
            }

            CheckBox {
                id: checkModulate31
                text: qsTr("")
                display: AbstractButton.IconOnly
                onCheckedChanged: {
                    synthModel.makeOperatorModulate(2, 0, checkModulate31.checked);
                }
            }

            CheckBox {
                id: checkModulate41
                text: qsTr("")
                display: AbstractButton.IconOnly
                onCheckedChanged: {
                    synthModel.makeOperatorModulate(3, 0, checkModulate41.checked);
                }
            }

            CheckBox {
                id: checkModulate51
                text: qsTr("")
                display: AbstractButton.IconOnly
                onCheckedChanged: {
                    synthModel.makeOperatorModulate(4, 0, checkModulate51.checked);
                }
            }

            CheckBox {
                id: checkModulate61
                text: qsTr("")
                display: AbstractButton.IconOnly
                onCheckedChanged: {
                    synthModel.makeOperatorModulate(5, 0, checkModulate61.checked);
                }
            }

            Label {
                id: row3
                width: 100
                height: 40
                color: "#ffffff"
                text: qsTr("Modulate 2")
                font.pixelSize: 16
                verticalAlignment: Text.AlignVCenter
            }

            CheckBox {
                id: checkModulate12
                text: qsTr("")
                display: AbstractButton.IconOnly
                onCheckedChanged: {
                    synthModel.makeOperatorModulate(0, 1, checkModulate12.checked);
                }
            }

            CheckBox {
                id: checkModulate22
                text: qsTr("")
                display: AbstractButton.IconOnly
                onCheckedChanged: {
                    synthModel.makeOperatorModulate(1, 1, checkModulate22.checked);
                }
            }

            CheckBox {
                id: checkModulate32
                text: qsTr("")
                display: AbstractButton.IconOnly
                onCheckedChanged: {
                    synthModel.makeOperatorModulate(2, 1, checkModulate32.checked);
                }
            }

            CheckBox {
                id: checkModulate42
                text: qsTr("")
                display: AbstractButton.IconOnly
                onCheckedChanged: {
                    synthModel.makeOperatorModulate(3, 1, checkModulate42.checked);
                }
            }

            CheckBox {
                id: checkModulate52
                text: qsTr("")
                display: AbstractButton.IconOnly
                onCheckedChanged: {
                    synthModel.makeOperatorModulate(4, 1, checkModulate52.checked);
                }
            }

            CheckBox {
                id: checkModulate62
                text: qsTr("")
                display: AbstractButton.IconOnly
                onCheckedChanged: {
                    synthModel.makeOperatorModulate(5, 1, checkModulate62.checked);
                }
            }

            Label {
                id: row4
                width: 100
                height: 40
                color: "#ffffff"
                text: qsTr("Modulate 3")
                font.pixelSize: 16
                verticalAlignment: Text.AlignVCenter
            }

            CheckBox {
                id: checkModulate13
                text: qsTr("")
                display: AbstractButton.IconOnly
                onCheckedChanged: {
                    synthModel.makeOperatorModulate(0, 2, checkModulate13.checked);
                }
            }

            CheckBox {
                id: checkModulate23
                text: qsTr("")
                display: AbstractButton.IconOnly
                onCheckedChanged: {
                    synthModel.makeOperatorModulate(1, 2, checkModulate23.checked);
                }
            }

            CheckBox {
                id: checkModulate33
                text: qsTr("")
                display: AbstractButton.IconOnly
                onCheckedChanged: {
                    synthModel.makeOperatorModulate(2, 2, checkModulate33.checked);
                }
            }

            CheckBox {
                id: checkModulate43
                text: qsTr("")
                display: AbstractButton.IconOnly
                onCheckedChanged: {
                    synthModel.makeOperatorModulate(3, 2, checkModulate43.checked);
                }
            }

            CheckBox {
                id: checkModulate53
                text: qsTr("")
                display: AbstractButton.IconOnly
                onCheckedChanged: {
                    synthModel.makeOperatorModulate(4, 2, checkModulate53.checked);
                }
            }

            CheckBox {
                id: checkModulate63
                text: qsTr("")
                display: AbstractButton.IconOnly
                onCheckedChanged: {
                    synthModel.makeOperatorModulate(5, 2, checkModulate63.checked);
                }
            }

            Label {
                id: row5
                width: 100
                height: 40
                color: "#ffffff"
                text: qsTr("Modulate 4")
                font.pixelSize: 16
                verticalAlignment: Text.AlignVCenter
            }

            CheckBox {
                id: checkModulate14
                text: qsTr("")
                display: AbstractButton.IconOnly
                onCheckedChanged: {
                    synthModel.makeOperatorModulate(0, 3, checkModulate14.checked);
                }
            }

            CheckBox {
                id: checkModulate24
                text: qsTr("")
                display: AbstractButton.IconOnly
                onCheckedChanged: {
                    synthModel.makeOperatorModulate(1, 3, checkModulate24.checked);
                }
            }

            CheckBox {
                id: checkModulate34
                text: qsTr("")
                display: AbstractButton.IconOnly
                onCheckedChanged: {
                    synthModel.makeOperatorModulate(2, 3, checkModulate34.checked);
                }
            }

            CheckBox {
                id: checkModulate44
                text: qsTr("")
                display: AbstractButton.IconOnly
                onCheckedChanged: {
                    synthModel.makeOperatorModulate(3, 3, checkModulate44.checked);
                }
            }

            CheckBox {
                id: checkModulate54
                text: qsTr("")
                display: AbstractButton.IconOnly
                onCheckedChanged: {
                    synthModel.makeOperatorModulate(4, 3, checkModulate54.checked);
                }
            }

            CheckBox {
                id: checkModulate64
                text: qsTr("")
                display: AbstractButton.IconOnly
                onCheckedChanged: {
                    synthModel.makeOperatorModulate(5, 3, checkModulate64.checked);
                }
            }

            Label {
                id: row6
                width: 100
                height: 40
                color: "#ffffff"
                text: qsTr("Modulate 5")
                font.pixelSize: 16
                verticalAlignment: Text.AlignVCenter
            }

            CheckBox {
                id: checkModulate15
                text: qsTr("")
                display: AbstractButton.IconOnly
                onCheckedChanged: {
                    synthModel.makeOperatorModulate(0, 4, checkModulate15.checked);
                }
            }

            CheckBox {
                id: checkModulate25
                text: qsTr("")
                display: AbstractButton.IconOnly
                onCheckedChanged: {
                    synthModel.makeOperatorModulate(1, 4, checkModulate25.checked);
                }
            }

            CheckBox {
                id: checkModulate35
                text: qsTr("")
                display: AbstractButton.IconOnly
                onCheckedChanged: {
                    synthModel.makeOperatorModulate(2, 4, checkModulate35.checked);
                }
            }

            CheckBox {
                id: checkModulate45
                text: qsTr("")
                display: AbstractButton.IconOnly
                onCheckedChanged: {
                    synthModel.makeOperatorModulate(3, 4, checkModulate45.checked);
                }
            }

            CheckBox {
                id: checkModulate55
                text: qsTr("")
                display: AbstractButton.IconOnly
                onCheckedChanged: {
                    synthModel.makeOperatorModulate(4, 4, checkModulate55.checked);
                }
            }

            CheckBox {
                id: checkModulate65
                text: qsTr("")
                display: AbstractButton.IconOnly
                onCheckedChanged: {
                    synthModel.makeOperatorModulate(5, 4, checkModulate65.checked);
                }
            }

            Label {
                id: row7
                width: 100
                height: 40
                color: "#ffffff"
                text: qsTr("Modulate 6")
                font.pixelSize: 16
                verticalAlignment: Text.AlignVCenter
            }

            CheckBox {
                id: checkModulate16
                text: qsTr("")
                display: AbstractButton.IconOnly
                onCheckedChanged: {
                    synthModel.makeOperatorModulate(0, 5, checkModulate16.checked);
                }
            }

            CheckBox {
                id: checkModulate26
                text: qsTr("")
                display: AbstractButton.IconOnly
                onCheckedChanged: {
                    synthModel.makeOperatorModulate(1, 5, checkModulate26.checked);
                }
            }

            CheckBox {
                id: checkModulate36
                text: qsTr("")
                display: AbstractButton.IconOnly
                onCheckedChanged: {
                    synthModel.makeOperatorModulate(2, 5, checkModulate36.checked);
                }
            }

            CheckBox {
                id: checkModulate46
                text: qsTr("")
                display: AbstractButton.IconOnly
                onCheckedChanged: {
                    synthModel.makeOperatorModulate(3, 5, checkModulate46.checked);
                }
            }

            CheckBox {
                id: checkModulate56
                text: qsTr("")
                display: AbstractButton.IconOnly
                onCheckedChanged: {
                    synthModel.makeOperatorModulate(4, 5, checkModulate56.checked);
                }
            }

            CheckBox {
                id: checkModulate66
                text: qsTr("")
                display: AbstractButton.IconOnly
                onCheckedChanged: {
                    synthModel.makeOperatorModulate(5, 5, checkModulate66.checked);
                }
            }
        }
    }

    Button {
        id: buttonDX7Algorithm
        x: 728
        y: 19
        width: 59
        height: 40
        text: qsTr("SET")

        onClicked: {
            synthModel.makeDX7Algorithm(spinDX7Algorithm.value-1);
        }
    }

    SpinBox {
        id: spinDX7Algorithm
        x: 573
        y: 19
        to: 32
        from: 1
        value: 1
    }

    Label {
        id: label
        x: 416
        y: 26
        color: "#ffb060"
        text: qsTr("DX7 Algorithm")
        font.pixelSize: 22
    }

    Component.onCompleted: {
        updatePage();
    }

}


/*##^##
Designer {
    D{i:1;anchors_height:400;anchors_x:0;anchors_y:0}D{i:11;anchors_width:100}D{i:18;anchors_width:100}
D{i:25;anchors_width:100}D{i:32;anchors_width:100}D{i:39;anchors_width:100}D{i:46;anchors_width:100}
D{i:53;anchors_width:100}
}
##^##*/
