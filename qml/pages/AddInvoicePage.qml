import QtQuick
import QtQuick.Controls.Material as QC2
import QtQuick.Layouts
import InvoiceForm 1.0
import Validator 1.0
import Felgo as Felgo
import "../reusables"
import "../components"
import "../delegates"
import "../scripts/requester.js" as Req
import "../scripts/utilities.js" as Utils

Felgo.FlickablePage {
    id: _addInvoicePage
    title: qsTr("Create invoice")
    backgroundColor: Qt.color("#F6F8FC")
    flickable.contentHeight: _col6.implicitHeight + 40
    navigationBarHidden: false
    readonly property var _userProfile: _authRequests.getCurrentUser()
    FontLoader {
        id: _fontLoader
        source: "../../assets/fonts/Inter-Regular.ttf"
    }
    FontLoader {
        id: _fontBoldLoader
        source: "../../assets/fonts/Inter-ExtraBold.ttf"
    }
    Component {
        id: _addCustomerComponent
        AddCustomerPage{}
    }
    Felgo.JsonListModel {
        id: _currencies
    }
    Felgo.JsonListModel {
        id: _customers
        keyField: "Cus_Mas_Sno"
        fields: ["Cus_Mas_Sno","Customer_Name"]
    }
    Felgo.JsonListModel {
        id: _paymentTypes
        source: [
            {
                name: "Flexible"
            },
            {
                name: "Fixed"
            }
        ]
    }
    rightBarItem: Felgo.ActivityIndicatorBarItem {
        animating: Felgo.HttpNetworkActivityIndicator.enabled
        visible: animating
    }
    InvoiceForm {
        id: _invoiceForm
        property var _body: ({})
        validatorListReference: _validators
        readonly property list<Validator> _validators: [
            Validator {
                name: "invno"
                required: true
                validator: RegularExpressionValidator {
                    id: _invnoValidator
                    regularExpression: /^(BIZ|BSL\/).*/
                }
                value: _invnoInput.textField.text
                errors: [qsTr("Please provide an invoice number."),qsTr("Invoice numbers must start with 'BIZ' or 'BSL/'.")]
            },
            Validator {
                name: "date"
                required: true
                validator: RegularExpressionValidator {
                    id: _invoiceDateValidator
                    regularExpression: /^(0[1-9]|[12][0-9]|3[01])\/(0[1-9]|1[0-2])\/(?!0000)\d{4}$/
                }
                //value: _invoiceDate.textField.text
                value: Utils.convertDateString(_invoiceDate.textField.text)
                errors: [qsTr("Please specify the invoice date."),qsTr("Invalid invoice date")]
            },
            Validator {
                //readonly property string _text: _invoiceDueDate.textField.text
                name: "edate"
                required: true
                validator: _invoiceDateValidator
                //value: _text ? splitDates(_text.split('/')) : ""
                value: Utils.convertDateString(_invoiceDueDate.textField.text)
                errors: [qsTr("Please specify the due date."),qsTr("Invalid due date.")]
            },
            Validator {
                name: "iedate"
                required: true
                validator: _invoiceDateValidator
                //value: _invoiceDateExpiry.textField.text
                value: Utils.convertDateString(_invoiceDateExpiry.textField.text)
                errors: [qsTr("Please specify the due date."),qsTr("Invalid due date.")]
            },
            Validator {
                name: "chus"
                required: true
                validator: RegularExpressionValidator {
                    id: _chusValidator
                }
                value: _customerComboBox.comboxBox.currentValue ? _customerComboBox.comboxBox.currentValue.toString() : ""
                errors: [qsTr("Please select a customer."),qsTr("Invalid customer selected.")]
            },
            Validator {
                name: "ptype"
                required: true
                validator: RegularExpressionValidator {
                    id: _ptypeValidator
                    regularExpression: /^(Flexible|Fixed)$/
                }
                value: _paymentTypeComboBox.comboxBox.currentValue
                errors: [qsTr("Please select a payment type."),qsTr("Invalid payment type selected.")]
            },
            Validator {
                name: "ccode"
                required: true
                validator: RegularExpressionValidator {
                    id: _ccodeValidator
                    regularExpression: /^(CAD|USD|TZS)$/
                }
                value: currenyComboBox.comboxBox.currentValue
                errors: [qsTr("Please select currency."),qsTr("Invalid currency selected.")]
            },
            Validator {
                name: "Inv_remark"
                required: true
                validator: RegularExpressionValidator {}
                value: _invRemark.textField.text
                errors: []
            },
            Validator {
                name: "compid"
                required: false
                validator: RegularExpressionValidator {}
                value: _addInvoicePage._userProfile.InstID
                errors: []
            },
            Validator {
                name: "userid"
                required: false
                validator: RegularExpressionValidator {}
                value: _addInvoicePage._userProfile.Usno
                errors: []
            },
            Validator {
                name: "sno"
                required: false
                validator: IntValidator {
                    bottom: 0
                    top: 90000
                }
                value: 0
                errors: []
            },
            Validator {
                name: "warrenty"
                required: false
                validator: RegularExpressionValidator {}
                value: ""
                errors: []
            },
            Validator {
                name: "goods_status"
                required: false
                validator: RegularExpressionValidator {}
                value: ""
                errors: []
            },
            Validator {
                name: "delivery_status"
                required: false
                validator: RegularExpressionValidator {}
                value: ""
                errors: []
            }
        ]
    }
    Felgo.Dialog {
        id: _saveChanges
        title: "Save changes?"
        positiveActionLabel: "Confirm"
        negativeActionLabel: "Cancel"
        onAccepted: {
            let res = Req.requestAddInvoice(Felgo,_invoiceForm._body)
            res.then(function (res) {
                let [addInvoiceResponse] = res;
                if (typeof addInvoiceResponse.response === 'number' && addInvoiceResponse.response > 0) {

                }
            });
            _saveChanges.close()
        }
        onCanceled: {
            _saveChanges.close()
        }
    }
    Felgo.Dialog {
        id: _successMessage
    }

    Connections {
        target: _invoiceForm
        function onIsInvalidForm(message) {
            Felgo.NativeUtils.displayMessageBox(qsTr("Invalid"),message,2)
        }
        function onIsValidForm(payload) {
            _invoiceForm._body = payload
            _saveChanges.open()
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
            text: qsTr("Add Invoice")
        }
        QC2.Pane {
            Layout.fillWidth: true
            Layout.preferredHeight: _col10.implicitHeight
            QC2.Material.elevation: 1
            ColumnLayout{
                id: _col10
                anchors.fill: parent
                Item{
                    Layout.fillWidth: true
                    Layout.preferredHeight: _invnoInput.implicitHeight
                    ValidatedField {
                        id: _invnoInput
                        anchors.fill: parent
                        label: qsTr("Invoice number")
                        placeholderText: qsTr("Enter invoice number")
                        errorMessage: qsTr("Please enter invoice number")
                        validator: _invnoValidator
                    }
                }
                Item{
                    Layout.fillWidth: true
                    Layout.preferredHeight: _invoiceDateGrid.implicitHeight
                    GridLayout{
                        id: _invoiceDateGrid
                        anchors.fill: parent
                        columns: 2
                        Item{
                            Layout.fillWidth: true
                            Layout.preferredHeight: _invoiceDate.implicitHeight
                            ValidatedDateField {
                                id: _invoiceDate
                                label: qsTr("Invoice date")
                                errorMessage: qsTr("Please enter a valid date")
                                anchors.fill: parent
                                textField.onActiveFocusChanged: {
                                    hasError = !textField.activeFocus && !textField.acceptableInput
                                }
                                Connections {
                                    target: _invoiceDate
                                    function onAccepted(date) {

                                        console.log(date)
                                    }
                                }
                            }
                        }
                        Item{
                            Layout.fillWidth: true
                            Layout.preferredHeight: _invoiceDueDate.implicitHeight
                            ValidatedDateField {
                                id: _invoiceDueDate
                                label: qsTr("Invoice due date")
                                errorMessage: qsTr("Please enter a valid date")
                                anchors.fill: parent
                                textField.onActiveFocusChanged: {
                                    hasError = !textField.activeFocus && !textField.acceptableInput
                                }
                                Connections {
                                    target: _invoiceDueDate
                                    function onAccepted(date) {
                                        console.log(date)
                                    }
                                }
                            }
                        }
                        Item{
                            Layout.fillWidth: true
                            Layout.preferredHeight: _invoiceDateExpiry.implicitHeight
                            ValidatedDateField {
                                id: _invoiceDateExpiry
                                label: qsTr("Invoice expiry date")
                                errorMessage: qsTr("Please enter a valid date")
                                anchors.fill: parent
                                textField.onActiveFocusChanged: {
                                    hasError = !textField.activeFocus && !textField.acceptableInput
                                }
                                Connections {
                                    target: _invoiceDateExpiry
                                    function onAccepted(date) {
                                        console.log(date)
                                    }
                                }
                            }
                        }
                    }
                }
                Item {
                    Layout.fillWidth: true
                    Layout.preferredHeight: _customerComboBox.implicitHeight
                    ValidatedComboBoxField {
                        id: _customerComboBox
                        label: qsTr("Customer")
                        comboxBox.model: _customers
                        comboxBox.textRole: "Customer_Name"
                        comboxBox.valueRole: "Cus_Mas_Sno"
                        isRequired: true
                        errorMessage: qsTr("Please select a customer")
                        validator: _chusValidator
                        anchors.fill: parent
                        isEditable: false
                        comboxBox.onActiveFocusChanged: {
                            hasError = _customerComboBox.comboxBox.currentIndex === -1
                        }
                    }
                }
                Item{
                    Layout.fillWidth: true
                    Layout.preferredHeight: _paymentTypeStatusGrid.implicitHeight
                    GridLayout{
                        id: _paymentTypeStatusGrid
                        anchors.fill: parent
                        columns: 2
                        Item {
                            Layout.fillWidth: true
                            Layout.preferredHeight: currenyComboBox.implicitHeight
                            ValidatedComboBoxField {
                                id: currenyComboBox
                                comboxBox.model: _currencies
                                comboxBox.textRole: "Currency_Code"
                                comboxBox.valueRole: "Currency_Code"
                                label: qsTr("Currency")
                                validator: _ccodeValidator
                                isRequired: true
                                errorMessage: qsTr("Select a status")
                                anchors.fill: parent
                                comboxBox.onActiveFocusChanged: {
                                    hasError = currenyComboBox.comboxBox.currentIndex === -1
                                }
                            }
                        }
                        Item {
                            Layout.fillWidth: true
                            Layout.preferredHeight: _paymentTypeComboBox.implicitHeight
                            ValidatedComboBoxField {
                                id: _paymentTypeComboBox
                                comboxBox.model: _paymentTypes
                                comboxBox.textRole: "name"
                                comboxBox.valueRole: "name"
                                label: qsTr("Payment type")
                                isRequired: true
                                errorMessage: qsTr("Select a payment type")
                                validator: _ptypeValidator
                                anchors.fill: parent
                                comboxBox.onActiveFocusChanged: {
                                    hasError = _paymentTypeComboBox.comboxBox.currentIndex === -1
                                }
                            }
                        }
                        Item{
                            Layout.fillWidth: true
                            Layout.preferredHeight: _invnoInput.implicitHeight
                            ValidatedField {
                                id: _invRemark
                                anchors.fill: parent
                                label: qsTr("Invoice remark")
                                placeholderText: qsTr("Enter remark")
                                errorMessage: qsTr("Please enter remark")
                            }
                        }
                    }
                }
                QC2.ToolSeparator {
                    orientation: "Horizontal"
                    Layout.fillWidth: true
                }
                Felgo.AppText {
                    text: "Item details"
                    Layout.fillWidth: true
                    font.pixelSize: sp(14)
                    font.capitalization: Font.AllUppercase
                }
                Item {
                    Layout.fillWidth: true
                    Layout.preferredHeight: _invoiceItemsListView.contentHeight
                    ListView{
                        id: _invoiceItemsListView
                        anchors.fill: parent
                        interactive: false
                        model: _invoiceForm.itemDetailsListModel
                        delegate: InvoiceItemDelegate{
                            id: _invoiceItem
                            displayAddIcon: index === _invoiceForm.itemDetailsLength - 1
                            implicitWidth: _invoiceItemsListView.width
                            Connections {
                                target: _invoiceItem
                                function onAddItem() {
                                    _invoiceForm.appendItemDetail()
                                }
                                function onRemoveItemAt(index) {
                                    _invoiceForm.removeItemDetail(index)
                                }
                                function onTotalAmountChanged(amount,index) {
                                    console.log(amount,index)
                                }
                            }
                        }
                        Component.onCompleted: {
                            _invoiceForm.appendItemDetail()
                        }
                    }
                }
                Item{
                    id: _item9
                    Layout.fillWidth: true
                    Layout.preferredHeight: _row14.implicitHeight
                    property real _total: 0
                    RowLayout {
                        id: _row14
                        anchors.fill: parent
                        CustomButton {
                            text: qsTr("Calculate total")
                            flat: true
                            onClicked: {
                                _item9._total = _invoiceForm.getItemDetailsTotal()
                            }
                        }
                        Felgo.AppText {
                            Layout.preferredHeight: implicitHeight
                            text: qsTr("<b>Total:</b> %1").arg(_item9._total)
                            Layout.fillWidth: true
                            font.pixelSize: sp(14)
                            font.capitalization: Font.AllUppercase
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
                                _invoiceForm.qmlValidate()
                            }
                        }
                    }
                }
            }
        }
    }
    Component.onCompleted: {
        let body = _addInvoicePage._userProfile
        let res = Req.addInvoiceRequests(Felgo,_authRequests.getCurrentUser())
        res.then(function (res) {
            let [currencies,customers] = res;
            _currencies.source = currencies.response
            _customers.source = customers.response
        });
    }
}
