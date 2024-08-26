import QtQuick
import QtQuick.Layouts
import QtQuick.Controls.Material as QC2
import Felgo as Felgo
import QtWebView
//import AuthRequests 1.0
import "../components"
import "../reusables"
import "../scripts/utilities.js" as Utils
import "../scripts/requester.js" as Req

Felgo.FlickablePage {
    id: _loginPage
    navigationBarHidden: true
    backgroundColor: Qt.color("#F6F8FC")
    Component {
        id: _forgotPasswordComponent
        ForgotPasswordPage{}
    }
    Component {
        id: _vendorRegistrationPageComponent
        VendorRegistrationPage{}
    }

    Connections {
        target: _authRequests
        function onLoginFailed(message) {
            Felgo.NativeUtils.displayMessageBox(qsTr("Login Failed"),qsTr(message),1)
        }
        function onLoginSuccessfull() {
            console.log("Logged in successfully!")
        }
    }
    Item {
        id: _item6
        visible: true
        anchors.centerIn: parent
        implicitWidth: parent.width
        implicitHeight: _loginForm.implicitHeight * 1.1
        QtObject {
            id: _loginPayload
            readonly property string userName: _emailField.textField.text
            readonly property string password: _passwordField.textField.text
        }
        QC2.Pane {
            QC2.Material.background: Qt.color("#ffffff")
            QC2.Material.elevation: 1
            anchors.fill: parent
            anchors.leftMargin: 10
            anchors.rightMargin: 10
            BusyLoader {
                id: _loginBusyLoader
                _isRunning: _authRequests.isWorking
                on_IsRunningChanged: {
                    if (_isRunning) {
                        _loginBusyLoader.open()
                    }
                    else {
                        _loginBusyLoader.close()
                    }
                }
            }
            contentItem: ColumnLayout {
                id: _loginForm
                anchors.fill: parent
                anchors.leftMargin: 10
                anchors.rightMargin: 10
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
                                    let compo = Qt.createComponent("./ForgotPasswordPage.qml")
                                    let sprite = compo.createObject()
                                    _loginPage.navigationStack.push(sprite)
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
                        if (!_emailField.hasError && !_passwordField.hasError) {
                            const payload = Req.createLoginPayload(_loginPayload)
                            _authRequests.loginUser(payload)
                        }
                    }
                }
//                CustomButton {
//                    id: _signInGoogle
//                    Layout.fillWidth: true
//                    background: Item{}
//                    contentItem: Felgo.AppImage {
//                        source: "../../assets/img/android_light_sq_SU@3x.png"
//                        anchors.fill: parent
//                        opacity: _signInGoogle.pressed ? 0.8 : 1
//                    }
//                    onClicked: {
//                        //_authRequests.signInWithGoogle()
//                        Req.requestJsonPlaceholder(Felgo.HttpRequest)
//                    }
//                }
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
                                    let compo = Qt.createComponent("./VendorRegistrationPage.qml")
                                    let sprite = compo.createObject()
                                    _loginPage.navigationStack.push(sprite)
                                    //_loginPage.navigationStack.push(_vendorRegistrationPageComponent)
                                    //_authStack.push(_vendorRegistrationPageComponent)
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
