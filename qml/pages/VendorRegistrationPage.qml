import QtQuick
import QtQuick.Layouts
import QtQuick.Controls.Material as QC2
import Felgo as Felgo
import BranchListModel 1.0
import SetupBranch 1.0
import VendorRegistrationForm 1.0
import CompanyUsersRequests 1.0
import Validator 1.0
import "../components"
import "../reusables"

Felgo.FlickablePage {
    id: _vendorRegistrationPage
    navigationBarHidden: true
    backgroundColor: Qt.color("#F6F8FC")
    BusyLoader {
        id: _loginBusyLoader
        _isRunning: _companyUsersRequests.isWorking
        on_IsRunningChanged: {
            if (_isRunning) {
                _loginBusyLoader.open()
            }
            else {
                _loginBusyLoader.close()
            }
        }
    }
    SetupBranch {
        id: _setupBranch
    }
    VendorRegistrationForm {
        id: _vendorRegistrationForm
        compsno: 0
        compname: _vendorName.textField.text
        mob: _mobileNumber.textField.text
        mobCountryCode: _phonePrefix.currentText.substring(1)
        branch: Number(_branchComboBox.currentValue)
        accno: _accountNumberField.textField.text
        check_status: _checkStatusGroup.checkedButton.text
        property var _body: ({})
        validatorListReference: _validators
        readonly property list<Validator> _validators: [
            Validator {
                name: "compsno"
                validator: IntValidator { bottom: 0; top: 9000000 }
                required: false
                errors: [qsTr("Opps! Something went wrong! Please try again."),qsTr("Opps! Something went wrong! Please try again or contact support.")]
            },
            Validator {
                name: "compname"
                validator: _vendorNameValidator
                required: true
                errors: [qsTr("Please, provide a vendor name."),qsTr("Vendor name must contain at least one first and last name, separated by a space.")]
            },
            Validator {
                name: "mob"
                required: true
                validator: _vendorMobileNumberValidator
                errors: [qsTr("Please, provide a mobile number."),qsTr("Please enter a valid mobile number without leading zeros or country code."),qsTr("Please select the mobile number's country code.")]
            },
            Validator {
                name: "branch"
                validator: IntValidator { bottom: 0; top: 9000000 }
                required: true
                errors: [qsTr("Please, select a branch."),qsTr("The branch you have selected is invalid.")]
            },
            Validator {
                name: "accno"
                validator: _accountNumberValidator
                required: true
                errors: [qsTr("Please, provide the account number."),qsTr("The account number you have entered is incorrect.")]
            },
            Validator {
                name: "check_status"
                validator: RegularExpressionValidator {
                    regularExpression: /^(Yes|No)$/
                }
                required: true
                errors: [qsTr("Please, specify the need for an approval check."),qsTr("Opps! Something went wrong! Please try again or contact support.")]
            }
        ]
    }

    CompanyUsersRequests {
        id: _companyUsersRequests
    }

    Connections {
        target: _vendorRegistrationForm
        function onIsInvalidForm(message) {
            Felgo.NativeUtils.displayMessageBox(qsTr("Invalid"),message,2)
        }
        function onIsValidForm(payload) {
            _vendorRegistrationForm._body = payload
            Felgo.NativeUtils.displayAlertDialog(qsTr("Confirm"), qsTr("Save changes?"), qsTr("Confirm"), qsTr("Cancel"))
        }
    }
    Connections {
        target: Felgo.NativeUtils
        function onAlertDialogFinished(accepted) {
            if (accepted) {
                _companyUsersRequests.requestAddCompanyL(_vendorRegistrationForm._body)
            }
            else {
                _vendorRegistrationForm._body = ({})
            }
        }
    }
    Connections {
        target: _companyUsersRequests
        function onInternalServerError(message) {
            Felgo.NativeUtils.displayMessageBox(qsTr("Failed"),message,2)
        }
        function onAddCompanyLFailed(message) {
            Felgo.NativeUtils.displayMessageBox(qsTr("Failed"),message,2)
        }
    }


    Item {
        id: _vendorRegItem
        anchors.centerIn: parent
        implicitWidth: parent.width
        implicitHeight: _pane2.implicitHeight * 1.1
        QC2.Pane {
            id: _pane2
            QC2.Material.background: Qt.color("#ffffff")
            QC2.Material.elevation: 1
            anchors.fill: parent
            anchors.leftMargin: 10
            anchors.rightMargin: 10
            contentItem: ColumnLayout{
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
                                    id: _vendorNameValidator
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
                                        validator: RegularExpressionValidator {
                                            id: _vendorMobileNumberValidator
                                            regularExpression: /^[67]\d{8}$/
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
                                    id: _branchComboBox
                                    Layout.fillWidth: true
                                    textRole: "Name"
                                    valueRole: "Sno"
                                    model: BranchListModel {
                                        id: _branchListModel
                                    }
                                }
                            }
                            Connections {
                                target: _setupBranch
                                function onBranchList(branchList) {
                                    _branchListModel.populate(branchList)
                                }
                            }

                            Component.onCompleted: {
                                _setupBranch.requestBranchList({})
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
                                validator: RegularExpressionValidator {
                                    id: _accountNumberValidator
                                    regularExpression: /^(01|02)(J|\d)\d{10}$/
                                }
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
                                    QC2.ButtonGroup {
                                        id: _checkStatusGroup
                                        buttons: _row6.children
                                    }
                                    RowLayout {
                                        id: _row6
                                        anchors.top: parent.top
                                        anchors.bottom: parent.bottom
                                        anchors.left: parent.left
                                        QC2.RadioButton {
                                            text: qsTr("Yes")
                                            font.family: _fontLoader.name
                                            font.pixelSize: sp(12)
                                            QC2.Material.accent: Qt.color("#8196FE")
                                        }
                                        QC2.RadioButton {
                                            text: qsTr("No")
                                            font.family: _fontLoader.name
                                            font.pixelSize: sp(12)
                                            QC2.Material.accent: Qt.color("#8196FE")
                                            checked: true
                                        }
                                    }
                                }
                            }
                        }
                        CustomButton {
                            text: qsTr("Register")
                            Layout.fillWidth: true
                            onClicked: {
                                _vendorRegistrationForm.qmlValidate()
                                //_vendorRegistrationForm.validate()
                            }
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
                                    //_vendorRegistrationPage.navigationStack.pop()
                                    _authStack.pop()
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

