import QtQuick
import QtQuick.Layouts
import QtQuick.Controls.Material as QC2
import Felgo as Felgo
import "../reusables"
import "../pages"
import "../scripts/utilities.js" as Utils
import "../scripts/requester.js" as Req


ColumnLayout {
    id: _col
    Component {
        id: _vendorRegistrationComponent
        VendorRegistrationPage{}
    }
    Component {
        id: _forgotPasswordComponent
        ForgotPasswordPage{}
    }

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
    Item{
        Layout.fillWidth: true
        Layout.preferredHeight: _passwordField.implicitHeight
        ValidatedField {
            id: _passwordField
            anchors.fill: parent
            // we display an error message if the password length is less than 6
            //property bool isEmptyField: textField.text.length === 0

            // this hides characters by default
            textField.inputMode: textField.inputModePassword
            label: qsTr("Password")
            placeholderText: qsTr("Password")

            //hasError: isEmptyField
            errorMessage: qsTr("Please, enter password")
            textField.onActiveFocusChanged: {
                hasError = _passwordField.textField.length === 0
                //hasError = textField.text.length === 0 && !textField.activeFocus && !textField.acceptableInput
            }
        }
    }
    Item{
        Layout.fillWidth: true
        Layout.preferredHeight: _row.implicitHeight
        RowLayout{
            id: _row
            anchors.fill: parent
            Felgo.AppText{
                text: qsTr("Forgot password?")
                font.pixelSize: sp(14)
                font.underline: _mouse.pressed ? true : false
                Layout.fillWidth: true
                MouseArea {
                    id: _mouse
                    anchors.fill: parent
                    onClicked: {
                        _authStack.push(_forgotPasswordComponent)
                    }
                }
            }
        }
    }
    CustomButton {
        id: _loginBtn
        Layout.topMargin: 10
        Layout.fillWidth: true
        text: qsTr("Sign in")
        onClicked: {
            _loginBusyLoader.open()
            //_mainLoader.state = "Vendor"
        }
    }
    Item{
        Layout.topMargin: 10
        Layout.bottomMargin: 10
        Layout.fillWidth: true
        Layout.preferredHeight: _flow.implicitHeight
        Flow{
            id: _flow
            anchors.centerIn: parent
            spacing: 2
            Felgo.AppText{
                text: qsTr("Not registered?")
                horizontalAlignment: "AlignHCenter"
                Layout.fillWidth: true
                font.pixelSize: sp(14)
            }
            Felgo.AppText{
                id: _clickHere
                text: qsTr("Click here")
                color: Qt.color("#8196FE")
                font.underline: _mouse2.pressed ? true : false
                font.pixelSize: sp(14)
                horizontalAlignment: "AlignHCenter"
                Layout.fillWidth: true
                MouseArea{
                    id: _mouse2
                    anchors.fill: parent
                    onClicked: {
                        _authStack.push(_vendorRegistrationComponent)
                    }
                }
            }
        }
    }
}




