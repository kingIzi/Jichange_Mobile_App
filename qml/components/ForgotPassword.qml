import QtQuick
import QtQuick.Layouts
import QtQuick.Controls.Material as QC2
import Felgo as Felgo
import "../reusables"

ColumnLayout {
    id: _col2
    Felgo.AppImage{
        Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
        source: "../../assets/img/jichangelogo.png"
        sourceSize: Qt.size(160,160)
    }
    Item{
        Layout.fillWidth: true
        Layout.preferredHeight: _emailField.implicitHeight
        ValidatedField {
            id: _emailField
            anchors.fill: parent
            label: qsTr("Email address")
            placeholderText: qsTr("Enter your email address")
            textField.onActiveFocusChanged: {
                hasError = !textField.activeFocus && !textField.acceptableInput
            }
            errorMessage: qsTr("Please, enter a valid email address")
            validator: RegularExpressionValidator {
                regularExpression: /^(?![.@!])\w(?:[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}|[a-zA-Z0-9_]{4,})$/
            }
        }
    }
    CustomButton {
        text: qsTr("Reset")
        Layout.fillWidth: true
    }
    Felgo.AppText{
        text: qsTr("Back to login")
        font.pixelSize: sp(12)
        font.underline: _mouse.pressed ? true : false
        //Layout.fillWidth: true
        Layout.alignment: Qt.AlignHCenter
        horizontalAlignment: "AlignHCenter"
        Layout.topMargin: 10
        color: Qt.color("#8196FE")
        MouseArea {
            id: _mouse
            anchors.fill: parent
            onClicked: {
                _authStack.pop()
            }
        }
    }
}



