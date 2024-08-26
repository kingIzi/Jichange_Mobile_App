import QtQuick
import QtQuick.Layouts
import QtQuick.Controls.Material as QC2
import Felgo as Felgo
import "../reusables"

ColumnLayout{
    id: _vendorRegCol
    Felgo.AppText{
        text: qsTr("Vendor Registration")
        font.pixelSize: sp(20)
        Layout.fillWidth: true
    }
    QC2.ToolSeparator {
        Layout.fillWidth: true
        orientation: Qt.Horizontal
    }
    Item{
        Layout.fillWidth: true
        Layout.preferredHeight: _col1.implicitHeight
        ColumnLayout{
            id: _col1
            anchors.fill: parent
            Item{
                Layout.fillWidth: true
                Layout.preferredHeight: _vendorName.implicitHeight
                ValidatedField {
                    id: _vendorName
                    anchors.fill: parent
                    label: qsTr("Vendor name")
                    placeholderText: qsTr("Enter vendor name")
                    errorMessage: qsTr("Please, enter vendor name")
                    validator: RegularExpressionValidator {
                        regularExpression: /[\w ]+/
                    }
                    // when the active focus is taken away from the textField we check if we need to display an error
                    textField.onActiveFocusChanged: {
                        hasError = !textField.activeFocus && !textField.acceptableInput
                    }
                }
            }
            Item{
                id: _item3
                Layout.fillWidth: true
                Layout.preferredHeight: _row2.implicitHeight
                RowLayout{
                    id: _row2
                    anchors.fill: parent
                    Item{
                        id: _item
                        Layout.fillWidth: true
                        Layout.preferredHeight: implicitHeight
                        implicitHeight: _mobileNumber.implicitHeight
                        ValidatedField {
                            id: _mobileNumber
                            anchors.fill: parent
                            label: qsTr("Mobile number")
                            placeholderText: qsTr("+255 (0) 742 036 609")
                            errorMessage: qsTr("Please, enter a valid phone number")
                            validator: RegularExpressionValidator {
                                regularExpression: /^(\+255|0)[67]\d{8}$/
                            }
                            textField.onActiveFocusChanged: {

                                hasError = !textField.activeFocus && !textField.acceptableInput
                            }

                        }
                    }
                }
            }
            Item{
                Layout.fillWidth: true
                Layout.preferredHeight: _col3.implicitHeight
                ColumnLayout {
                    id: _col3
                    anchors.fill: parent
                    Felgo.AppText {
                        font.bold: true
                        Layout.fillWidth: true
                        text: qsTr("Branch")
                    }
                    CustomTextComboBox {
                        Layout.fillWidth: true
                        model: ["HQ Dar es Salaam", "Branch #2", "Branch #3"]
                    }
                }
            }
            Item{
                Layout.fillWidth: true
                Layout.preferredHeight: _accountNumberField.implicitHeight
                ValidatedField {
                    id: _accountNumberField
                    anchors.fill: parent
                    label: qsTr("Account number")
                    placeholderText: qsTr("09378240000")
                    errorMessage: qsTr("Please, enter account number")
                    textField.onActiveFocusChanged: {
                        hasError = textField.text.length === 0
                        //hasError = textField.text.length === 0 && !textField.activeFocus && !textField.acceptableInput
                    }
                }
            }
            Item{
                Layout.fillWidth: true
                Layout.preferredHeight: _col4.implicitHeight
                ColumnLayout {
                    id: _col4
                    anchors.fill: parent
                    Felgo.AppText {
                        id: label
                        font.bold: true
                        Layout.fillWidth: true
                        text: qsTr("Send invoice approval checker?")
                    }
                    Item{
                        Layout.fillWidth: true
                        Layout.preferredHeight: _row6.implicitHeight
                        FontLoader {
                            id: _fontLoader
                            source: "../../assets/fonts/Inter-Regular.ttf" // loaded from your assets folder
                        }
                        RowLayout {
                            id: _row6
                            anchors.top: parent.top
                            anchors.bottom: parent.bottom
                            anchors.left: parent.left
                            QC2.RadioButton {
                                text: qsTr("YES")
                                //font: _root._extraBoldFont
                                font.family: _fontLoader.name
                                font.pixelSize: sp(12)
                                QC2.Material.accent: Qt.color("#8196FE")
                            }
                            QC2.RadioButton {
                                text: qsTr("NO")
                                font.family: _fontLoader.name
                                font.pixelSize: sp(12)
                                QC2.Material.accent: Qt.color("#8196FE")
                            }
                        }
                    }
                }
            }
            CustomButton {
                text: qsTr("Register")
                Layout.fillWidth: true
            }
            Felgo.AppText{
                text: qsTr("Back to login")
                font.pixelSize: sp(12)
                font.underline: _mouse.pressed ? true : false
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
    }
}



