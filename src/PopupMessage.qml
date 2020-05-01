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
import QtQuick.Controls 2.12

Popup {
    id: rootPopup
    width: 600
    height: 240
    x: (800 - width) / 2
    y: (480 - height) / 2
    dim: true
    background: Rectangle { color: "#00ffffff" }
    closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside
    clip: true

    signal okClicked()
    signal cancelClicked()

    property alias titleText: popupLabel.text;
    property alias detailText: confirmLabel.text;
    property alias okButtonText: okBtnLabel.text;
    property alias cancelButtonText: cancelBtnLabel.text;
    property alias okButton: okBtn;
    property alias cancelButton: cancelBtn;

    // popup content
    Rectangle {
        id: popupRect
        anchors.fill: parent
        radius: 0
        clip: true
        border.color: "white"

        Label {
            id: popupLabel
            x: 1
            y: 1
            width: 598
            height: 40
            color: "#ffffff"
            text: "Title"
            clip: true
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 0
            verticalAlignment: Text.AlignVCenter
            font.pixelSize: 30
            anchors.top: parent.top
            anchors.topMargin: 0
            horizontalAlignment: Text.AlignHCenter
            background: Rectangle {
                color: "#808080"
            }
        }

        Label {
            id: confirmLabel
            width: 571
            height: 91
            text: "Detailed text"
            verticalAlignment: Text.AlignVCenter
            wrapMode: Text.WordWrap
            font.pixelSize: 22
            anchors.top: popupLabel.bottom
            anchors.topMargin: 10
            horizontalAlignment: Text.AlignHCenter
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Rectangle {
            id: horizontalLine
            x: 1
            y: 145
            width: parent.width
            height: 1
            anchors.top : popupLabel.bottom
            anchors.topMargin: 110
            color: "lightgray"
        }

        Rectangle {
            id: cancelBtn
            y: 154
            width: 298
            height: 64
            radius: 10.0
            border.color: "#00000000"
            anchors.top: horizontalLine.bottom
            anchors.left: parent.left
            anchors.leftMargin: 1
            Label {
                id: cancelBtnLabel
                text: "Cancel"
                font.pixelSize: 25
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                horizontalAlignment: Text.AlignHCenter
            }

            TapHandler {
                gesturePolicy: TapHandler.ReleaseWithinBounds
                onTapped: {
                    rootPopup.cancelClicked();
                    rootPopup.close()
                }
                onCanceled: {
                }
            }

        }

        Rectangle {
            id: verticalLine
            width: 1
            height: 64
            anchors.top : horizontalLine.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            color: "lightgray"
        }

        Rectangle {
            id: okBtn
            y: 154
            width: parent.width / 2 - 2
            height: 64
            radius: 10.0
            border.color: "#00000000"
            anchors.top: horizontalLine.bottom
            anchors.right: parent.right
            anchors.rightMargin: 1

            Label {
                id: okBtnLabel
                text: "Ok"
                font.pixelSize: 25
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                horizontalAlignment: Text.AlignHCenter
            }
            TapHandler {
                gesturePolicy: TapHandler.ReleaseWithinBounds
                onTapped: {
                    rootPopup.okClicked();
                    rootPopup.close()
                }
                onCanceled: {
                }
            }

        }
    }
}

