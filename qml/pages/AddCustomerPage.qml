import QtQuick
import QtQuick.Controls.Material as QC2
import QtQuick.Layouts
import Felgo as Felgo
import CustomerForm 1.0
import Validator 1.0
import "../reusables"
import "../components"

Felgo.FlickablePage {
    id: _customersPage
    title: qsTr("Add New Customer")
    backgroundColor: Qt.color("#F6F8FC")
    flickable.contentHeight: _col6.implicitHeight
    navigationBarHidden: false
    property var _routes: []
    FontLoader {
        id: _fontLoader
        source: "../../assets/fonts/Inter-Regular.ttf"
    }
    FontLoader {
        id: _fontBoldLoader
        source: "../../assets/fonts/Inter-ExtraBold.ttf"
    }
    CustomerForm {
        id: _customerForm
        cust_Name: _customerName.textField.text
        phone: _mobileNumber.textField.text
        phoneCountryCode: _phonePrefix.currentText.substring(1)
        email: _emailField.textField.text
        property var _body: ({})
        validatorListReference: _validators
        readonly property list<Validator> _validators: [
            Validator {
                name: "Cust_Name"
                required: true
                validator: RegularExpressionValidator {
                    id: _custNameValidator
                    regularExpression: /^[A-Za-z]+(?: [A-Za-z]+)+$/
                }
                errors: [qsTr("Please provide the customer name."),qsTr("Customer name must contain at least one first and last name, separated by a space.")]
            },
            Validator {
                name: "Phone"
                validator: RegularExpressionValidator {
                    id: _mobileNumberValidator
                    regularExpression: /^[67]\d{8}$/
                }
                required: true
                errors: [qsTr("Please, provide a mobile number."),qsTr("Please enter a valid mobile number without leading zeros or country code."),qsTr("Please select the mobile number's country code.")]
            },
            Validator {
                name: "Email"
                validator: RegularExpressionValidator {
                    id: _emailValidator
                    regularExpression: /\w+([-+.']\w+)*@\w+([-.]\w+)*\.\w+([-.]\w+)*/
                }
                required: false
                errors: [qsTr("Please, provide an email address."),qsTr("Please enter a valid email address.")]
            }
        ]
    }
    Connections {
        target: _customerForm
        function onIsInvalidForm(message) {
            Felgo.NativeUtils.displayMessageBox(qsTr("Invalid"),message,2)
        }
        function onIsValidForm(payload) {
            //_vendorRegistrationForm._body = payload
            _customerForm._body = payload
            Felgo.NativeUtils.displayAlertDialog(qsTr("Confirm"), qsTr("Save changes?"), qsTr("Confirm"), qsTr("Cancel"))
        }
    }

    ColumnLayout {
        id: _col6
        anchors.fill: parent
        anchors.leftMargin: 10
        anchors.rightMargin: 10
        anchors.topMargin: 10
        TitleText {
            Layout.fillWidth: true
            text: qsTr("Add New Customer")
        }
        QC2.Pane {
            Layout.fillWidth: true
            Layout.preferredHeight: _col10.implicitHeight * 1.1
            QC2.Material.elevation: 1
            ColumnLayout{
                id: _col10
                anchors.fill: parent
                Item{
                    Layout.fillWidth: true
                    Layout.preferredHeight: _customerName.implicitHeight
                    ValidatedField {
                        id: _customerName
                        anchors.fill: parent
                        label: qsTr("Customer name")
                        placeholderText: qsTr("Enter customer full name")
                        errorMessage: qsTr("You must enter the customer's full name")
                        isRequired: true
                        validator: _custNameValidator
                        textField.onActiveFocusChanged: {
                            hasError = _customerName.textField.length === 0
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
                        Item {
                            Layout.bottomMargin: 8
                            Layout.preferredWidth: 80
                            Layout.preferredHeight: _item.implicitHeight / 1.618
                            //color: "red"
                            ColumnLayout {
                                anchors.fill: parent
                                QC2.ComboBox {
                                    id: _phonePrefix
                                    model: ["+255"]
                                    Layout.fillWidth: true
                                    QC2.Material.accent: Qt.color("#8196FE")
                                    flat: true
                                }
                            }
                        }
                        Item{
                            id: _item
                            Layout.fillWidth: true
                            Layout.preferredHeight: implicitHeight
                            implicitHeight: _mobileNumber.implicitHeight
                            ValidatedField {
                                id: _mobileNumber
                                anchors.fill: parent
                                label: qsTr("Mobile number")
                                placeholderText: qsTr("742 036 609")
                                errorMessage: qsTr("Please, enter a valid phone number")
                                validator: _mobileNumberValidator
                                textField.onActiveFocusChanged: {

                                    hasError = !textField.activeFocus && !textField.acceptableInput
                                }

                            }
                        }
                    }
                }
                Item{
                    id: _emailItem
                    Layout.fillWidth: true
                    Layout.preferredHeight: implicitHeight
                    implicitHeight: _emailField.implicitHeight
                    ValidatedField {
                        id: _emailField
                        anchors.fill: parent
                        label: qsTr("Email address")
                        placeholderText: qsTr("yourName@example.com")
                        errorMessage: qsTr("Please, enter a valid email address")
                        isRequired: false
                        validator: _emailValidator
                        textField.onActiveFocusChanged: {
                            hasError = !textField.activeFocus && !textField.acceptableInput
                        }
                    }
                }
                Item{
                    Layout.fillWidth: true
                    Layout.preferredHeight: _row11.implicitHeight
                    Layout.bottomMargin: 20
                    z: -1
                    RowLayout{
                        id: _row11
                        anchors.right: parent.right
                        anchors.top: parent.top
                        anchors.bottom: parent.bottom
                        CustomButton_v3 {
                            text: qsTr("Reset")
                        }
                        CustomButton_v2 {
                            text: qsTr("Submit")
                            onClicked: {
                                _customerForm.qmlValidate()
                            }
                        }
                    }
                }
            }
        }
    }
    Component.onCompleted: {
        _customersPage._routes.forEach((elem) => {
                                        _listModel.append({"label": elem})
                                       })
    }
}
