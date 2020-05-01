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

import QtQuick 2.9
import QtQuick.Window 2.3
import QtQuick.Controls 2.2

/*
 * This is a custom virtual keyboard because it is actually
 * rather difficult to get the standard Qt keyboard working on
 * a Raspberry Pi. I ran out of patience and built my own.
 * It suits my requirements - your mileage may vary ;-)
 */

Item {
    id: root
    width:800
    height:260

    signal keyPressed(var keyval)

    property var keyColor: "#D3D3D3"
    property var backgroundColor: "#202020"
    property bool punctuationMode: false

    function setPunctuationMode(enabled)
    {
        punctuationMode=enabled;

        if (enabled) {
            keyQ.text="!";
            keyW.text="=";
            keyE.text="&";
            keyR.text="\\";
            keyT.text="?";
            keyY.text="(";
            keyU.text="{";
            keyI.text="\"";
            keyO.text="~";
            keyP.text="_";

            keyA.text="#";
            keyS.text="$";
            keyD.text="*";
            keyF.text="/";
            keyG.text=":";
            keyH.text=")";
            keyJ.text="}";
            keyK.text="'";
            keyL.text="`";

            keyZ.text="%";
            keyX.text="^";
            keyC.text="-";
            keyV.text="+";
            keyB.text=";";
            keyN.text=",";
            keyM.text="|";
        } else {
            keyQ.text="Q";
            keyW.text="W";
            keyE.text="E";
            keyR.text="R";
            keyT.text="T";
            keyY.text="Y";
            keyU.text="U";
            keyI.text="I";
            keyO.text="O";
            keyP.text="P";

            keyA.text="A";
            keyS.text="S";
            keyD.text="D";
            keyF.text="F";
            keyG.text="G";
            keyH.text="H";
            keyJ.text="J";
            keyK.text="K";
            keyL.text="L";

            keyZ.text="Z";
            keyX.text="X";
            keyC.text="C";
            keyV.text="V";
            keyB.text="B";
            keyN.text="N";
            keyM.text="M";
        }
    }

    Rectangle {
        id: rectangleBackground
        x: 0
        y: 0
        width: parent.width
        height: 260
        color: backgroundColor

        Button {
            id: key1
            x: 13
            y: 8
            width: 56
            height: 56
            text: "1"
            font.bold: true
            flat: false
            background: Rectangle {
                color: keyColor
                radius: 8
            }
            font.pixelSize: 28
            onClicked: {
                root.keyPressed("1");
            }
        }

        Button {
            id: key2
            x: 85
            y: 8
            width: 56
            height: 56
            text: "2"
            font.bold: true
            flat: false
            background: Rectangle {
                color: keyColor
                radius: 8
            }
            font.pixelSize: 28
            onClicked: {
                root.keyPressed("2");
            }
        }

        Button {
            id: key3
            x: 157
            y: 8
            width: 56
            height: 56
            text: "3"
            font.bold: true
            flat: false
            background: Rectangle {
                color: keyColor
                radius: 8
            }
            font.pixelSize: 28
            onClicked: {
                root.keyPressed("3");
            }
        }

        Button {
            id: key4
            x: 229
            y: 8
            width: 56
            height: 56
            text: "4"
            font.bold: true
            flat: false
            background: Rectangle {
                color: keyColor
                radius: 8
            }
            font.pixelSize: 28
            onClicked: {
                root.keyPressed("4");
            }
        }

        Button {
            id: key5
            x: 301
            y: 8
            width: 56
            height: 56
            text: "5"
            font.bold: true
            flat: false
            background: Rectangle {
                color: keyColor
                radius: 8
            }
            font.pixelSize: 28
            onClicked: {
                root.keyPressed("5");
            }
        }

        Button {
            id: key6
            x: 373
            y: 8
            width: 56
            height: 56
            text: "6"
            font.bold: true
            flat: false
            background: Rectangle {
                color: keyColor
                radius: 8
            }
            font.pixelSize: 28
            onClicked: {
                root.keyPressed("6");
            }
        }

        Button {
            id: key7
            x: 445
            y: 8
            width: 56
            height: 56
            text: "7"
            font.bold: true
            flat: false
            background: Rectangle {
                color: keyColor
                radius: 8
            }
            font.pixelSize: 28
            onClicked: {
                root.keyPressed("7");
            }
        }

        Button {
            id: key8
            x: 517
            y: 8
            width: 56
            height: 56
            text: "8"
            font.bold: true
            flat: false
            background: Rectangle {
                color: keyColor
                radius: 8
            }
            font.pixelSize: 28
            onClicked: {
                root.keyPressed("8");
            }
        }

        Button {
            id: key9
            x: 589
            y: 8
            width: 56
            height: 56
            text: "9"
            font.bold: true
            flat: false
            background: Rectangle {
                color: keyColor
                radius: 8
            }
            font.pixelSize: 28
            onClicked: {
                root.keyPressed("9");
            }
        }

        Button {
            id: key10
            x: 661
            y: 8
            width: 56
            height: 56
            text: "0"
            font.bold: true
            flat: false
            background: Rectangle {
                color: keyColor
                radius: 8
            }
            font.pixelSize: 28
            onClicked: {
                root.keyPressed("0");
            }
        }

        Button {
            id: keyQ
            x: 14
            y: 69
            width: 56
            height: 56
            text: qsTr("Q")
            font.bold: true
            flat: false
            background: Rectangle {
                color: keyColor
                radius: 8
            }
            font.pixelSize: 28
            onClicked: {
                root.keyPressed(punctuationMode ? "!" : "Q");
            }
        }

        Button {
            id: keyA
            x: 14
            y: 130
            width: 56
            height: 56
            text: qsTr("A")
            font.bold: true
            flat: false
            background: Rectangle {
                color: keyColor
                radius: 8
            }
            font.pixelSize: 28
            onClicked: {
                root.keyPressed(punctuationMode ? "#" : "A");
            }
        }

        Button {
            id: keyZ
            x: 14
            y: 191
            width: 56
            height: 56
            text: qsTr("Z")
            font.bold: true
            flat: false
            background: Rectangle {
                color: keyColor
                radius: 8
            }
            font.pixelSize: 28
            onClicked: {
                root.keyPressed(punctuationMode ? "%" : "Z");
            }
        }

        Button {
            id: keyW
            x: 86
            y: 69
            width: 56
            height: 56
            text: "W"
            font.bold: true
            flat: false
            background: Rectangle {
                color: keyColor
                radius: 8
            }
            font.pixelSize: 28
            onClicked: {
                root.keyPressed(punctuationMode ? "=" : "W");
            }
        }

        Button {
            id: keyE
            x: 158
            y: 69
            width: 56
            height: 56
            text: "E"
            font.bold: true
            flat: false
            background: Rectangle {
                color: keyColor
                radius: 8
            }
            font.pixelSize: 28
            onClicked: {
                root.keyPressed(punctuationMode ? "&" : "E");
            }
        }

        Button {
            id: keyR
            x: 230
            y: 69
            width: 56
            height: 56
            text: "R"
            font.bold: true
            flat: false
            background: Rectangle {
                color: keyColor
                radius: 8
            }
            font.pixelSize: 28
            onClicked: {
                root.keyPressed(punctuationMode ? "\\" : "R");
            }
        }

        Button {
            id: keyT
            x: 302
            y: 69
            width: 56
            height: 56
            text: "T"
            font.bold: true
            flat: false
            background: Rectangle {
                color: keyColor
                radius: 8
            }
            font.pixelSize: 28
            onClicked: {
                root.keyPressed(punctuationMode ? "?" : "T");
            }
        }

        Button {
            id: keyY
            x: 374
            y: 69
            width: 56
            height: 56
            text: "Y"
            font.bold: true
            flat: false
            background: Rectangle {
                color: keyColor
                radius: 8
            }
            font.pixelSize: 28
            onClicked: {
                root.keyPressed(punctuationMode ? "(" : "Y");
            }
        }

        Button {
            id: keyU
            x: 446
            y: 69
            width: 56
            height: 56
            text: "U"
            font.bold: true
            flat: false
            background: Rectangle {
                color: keyColor
                radius: 8
            }
            font.pixelSize: 28
            onClicked: {
                root.keyPressed(punctuationMode ? "{" : "U");
            }
        }

        Button {
            id: keyI
            x: 518
            y: 69
            width: 56
            height: 56
            text: "I"
            font.bold: true
            flat: false
            background: Rectangle {
                color: keyColor
                radius: 8
            }
            font.pixelSize: 28
            onClicked: {
                root.keyPressed(punctuationMode ? "\"" : "I");
            }
        }

        Button {
            id: keyO
            x: 590
            y: 69
            width: 56
            height: 56
            text: "O"
            font.bold: true
            flat: false
            background: Rectangle {
                color: keyColor
                radius: 8
            }
            font.pixelSize: 28
            onClicked: {
                root.keyPressed(punctuationMode ? "~" : "O");
            }
        }

        Button {
            id: keyP
            x: 662
            y: 69
            width: 56
            height: 56
            text: "P"
            font.bold: true
            flat: false
            background: Rectangle {
                color: keyColor
                radius: 8
            }
            font.pixelSize: 28
            onClicked: {
                root.keyPressed(punctuationMode ? "_" : "P");
            }
        }

        Button {
            id: keyS
            x: 86
            y: 130
            width: 56
            height: 56
            text: "S"
            font.bold: true
            flat: false
            background: Rectangle {
                color: keyColor
                radius: 8
            }
            font.pixelSize: 28
            onClicked: {
                root.keyPressed(punctuationMode ? "$" : "S");
            }
        }

        Button {
            id: keyD
            x: 158
            y: 130
            width: 56
            height: 56
            text: "D"
            font.bold: true
            flat: false
            background: Rectangle {
                color: keyColor
                radius: 8
            }
            font.pixelSize: 28
            onClicked: {
                root.keyPressed(punctuationMode ? "*" : "D");
            }
        }

        Button {
            id: keyF
            x: 230
            y: 130
            width: 56
            height: 56
            text: "F"
            font.bold: true
            flat: false
            background: Rectangle {
                color: keyColor
                radius: 8
            }
            font.pixelSize: 28
            onClicked: {
                root.keyPressed(punctuationMode ? "/" : "F");
            }
        }

        Button {
            id: keyG
            x: 302
            y: 130
            width: 56
            height: 56
            text: "G"
            font.bold: true
            flat: false
            background: Rectangle {
                color: keyColor
                radius: 8
            }
            font.pixelSize: 28
            onClicked: {
                root.keyPressed(punctuationMode ? ":" : "G");
            }
        }

        Button {
            id: keyH
            x: 374
            y: 130
            width: 56
            height: 56
            text: "H"
            font.bold: true
            flat: false
            background: Rectangle {
                color: keyColor
                radius: 8
            }
            font.pixelSize: 28
            onClicked: {
                root.keyPressed(punctuationMode ? ")" : "H");
            }
        }

        Button {
            id: keyJ
            x: 446
            y: 130
            width: 56
            height: 56
            text: "J"
            font.bold: true
            flat: false
            background: Rectangle {
                color: keyColor
                radius: 8
            }
            font.pixelSize: 28
            onClicked: {
                root.keyPressed(punctuationMode ? "}" : "J");
            }
        }

        Button {
            id: keyK
            x: 518
            y: 130
            width: 56
            height: 56
            text: "K"
            font.bold: true
            flat: false
            background: Rectangle {
                color: keyColor
                radius: 8
            }
            font.pixelSize: 28
            onClicked: {
                root.keyPressed(punctuationMode ? "'" : "K");
            }
        }

        Button {
            id: keyL
            x: 590
            y: 130
            width: 56
            height: 56
            text: "L"
            font.bold: true
            flat: false
            background: Rectangle {
                color: keyColor
                radius: 8
            }
            font.pixelSize: 28
            onClicked: {
                root.keyPressed(punctuationMode ? "`" : "L");
            }
        }

        Button {
            id: keyX
            x: 86
            y: 191
            width: 56
            height: 56
            text: "X"
            font.bold: true
            flat: false
            background: Rectangle {
                color: keyColor
                radius: 8
            }
            font.pixelSize: 28
            onClicked: {
                root.keyPressed(punctuationMode ? "%" : "X");
            }
        }

        Button {
            id: keyC
            x: 158
            y: 191
            width: 56
            height: 56
            text: "C"
            font.bold: true
            flat: false
            background: Rectangle {
                color: keyColor
                radius: 8
            }
            font.pixelSize: 28
            onClicked: {
                root.keyPressed(punctuationMode ? "-" : "C");
            }
        }

        Button {
            id: keyV
            x: 230
            y: 191
            width: 56
            height: 56
            text: "V"
            font.bold: true
            flat: false
            background: Rectangle {
                color: keyColor
                radius: 8
            }
            font.pixelSize: 28
            onClicked: {
                root.keyPressed(punctuationMode ? "+" : "V");
            }
        }

        Button {
            id: keyB
            x: 302
            y: 191
            width: 56
            height: 56
            text: "B"
            font.bold: true
            flat: false
            background: Rectangle {
                color: keyColor
                radius: 8
            }
            font.pixelSize: 28
            onClicked: {
                root.keyPressed(punctuationMode ? ";" : "B");
            }
        }

        Button {
            id: keyN
            x: 374
            y: 191
            width: 56
            height: 56
            text: "N"
            font.bold: true
            flat: false
            background: Rectangle {
                color: keyColor
                radius: 8
            }
            font.pixelSize: 28
            onClicked: {
                root.keyPressed(punctuationMode ? "," : "N");
            }
        }

        Button {
            id: keyM
            x: 446
            y: 191
            width: 56
            height: 56
            text: "M"
            font.bold: true
            flat: false
            background: Rectangle {
                color: keyColor
                radius: 8
            }
            font.pixelSize: 28
            onClicked: {
                root.keyPressed(punctuationMode ? "|" : "M");
            }
        }

        Button {
            id: keySpace
            x: 590
            y: 191
            width: 56
            height: 56
            text: ""
            font.bold: true
            flat: false
            background: Rectangle {
                color: keyColor
                radius: 8
            }
            font.pixelSize: 28
            Image {
                id: keySpaceImage
                width: 38
                height: 38
                anchors.fill: parent
                source: "images/Key - Space.png"
                fillMode: Image.PreserveAspectFit
            }
            onClicked: {
                root.keyPressed(" ");
            }
        }

        Button {
            id: keyLeft
            x: 662
            y: 191
            width: 56
            height: 56
            text: ""
            font.bold: true
            flat: false
            background: Rectangle {
                color: keyColor
                radius: 8
            }
            font.pixelSize: 28
            Image {
                id: keyLeftImage
                width: 38
                height: 38
                anchors.centerIn: parent
                source: "images/Key - Left Arrow.png"
                fillMode: Image.PreserveAspectFit
            }
            onClicked: {
                root.keyPressed("LEFT");
            }
        }

        Button {
            id: keyRight
            x: 733
            y: 191
            width: 56
            height: 56
            text: ""
            font.bold: true
            flat: false
            background: Rectangle {
                color: keyColor
                radius: 8
            }
            font.pixelSize: 28
            Image {
                id: keyRightImage
                width: 38
                height: 38
                anchors.centerIn: parent
                source: "images/Key - Right Arrow.png"
                fillMode: Image.PreserveAspectFit
            }
            onClicked: {
                root.keyPressed("RIGHT");
            }
        }

        Button {
            id: keyBackspace
            x: 733
            y: 8
            width: 56
            height: 56
            text: ""
            font.bold: true
            flat: false
            background: Rectangle {
                color: keyColor
                radius: 8
            }
            font.pixelSize: 28
            Image {
                id: keyBSImage
                width: 42
                height: 42
                anchors.centerIn: parent
                source: "images/Key - Backspace.png"
                fillMode: Image.PreserveAspectFit
            }
            onClicked: {
                root.keyPressed("DEL");
            }
        }

        Button {
            id: keyEnter
            x: 733
            y: 69
            width: 56
            height: 56
            text: ""
            font.family: "Futura PT"
            flat: false
            background: Rectangle {
                color: keyColor
                radius: 8
            }
            font.pixelSize: 28
            Image {
                id: keyEnterImage
                width: 42
                height: 42
                anchors.centerIn: parent
                source: "images/Key - Enter.png"
                fillMode: Image.PreserveAspectFit
            }
            onClicked: {
                root.keyPressed("ENTER");
            }
        }

        Button {
            id: keyAt
            x: 662
            y: 130
            width: 56
            height: 56
            text: "@"
            flat: false
            background: Rectangle {
                color: keyColor
                radius: 8
            }
            font.pixelSize: 28
            font.bold: true
            onClicked: {
                root.keyPressed("@");
            }
        }

        Button {
            id: keyPeriod
            x: 518
            y: 191
            width: 56
            height: 56
            text: "."
            font.bold: true
            flat: false
            background: Rectangle {
                color: keyColor
                radius: 8
            }
            font.pixelSize: 28
            onClicked: {
                root.keyPressed(".");
            }
        }

        Button {
            id: keyPunct
            x: 733
            y: 129
            width: 56
            height: 56
            text: "..."
            flat: false
            font.bold: true
            background: Rectangle {
                color: keyColor
                radius: 8
            }
            font.pixelSize: 28
            onClicked: {
                // Toggle punctuation mode
                // This relabels a bunch of key caps
                setPunctuationMode(!punctuationMode);
            }
        }
    }
}
