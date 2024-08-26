import QtQuick
import QtQuick.Layouts
import QtQuick.Controls.Material as QC2
import Validator 1.0
import Felgo as Felgo
import "../reusables"

Item{
    id: _invoiceItemDelegate
    implicitHeight: _grid.implicitHeight
    property bool displayAddIcon: true
    signal addItem()
    signal removeItemAt(int index)
//    readonly property string _description: _descriptionInput.textField.text
//    readonly property int _quantity: _quantityInput.textField.text
//    readonly property real _unitPrice: _unitPriceInput.textField.text
//    readonly property real _totalPrice: _totalPriceInput.textField.text
    signal totalAmountChanged(real amount,int index)
    readonly property list<Validator> _validators: [
        Validator {
            name: "item_description"
            validator: RegularExpressionValidator {
                id: _descriptionValidator
            }
            value: _descriptionInput.textField.text
            required: true
            errors: [qsTr("Please provide an item description for item %1").arg(index),qsTr("")]
        },
        Validator {
            name: "item_qty"
            validator: IntValidator {
                id: _quantityValidator
                top: 5000
                bottom: 1
            }
            value: Number(_quantityInput.textField.text)
            required: true
            errors: [qsTr("Item %1 quantity cannot be 0.").arg(index),qsTr("Cannot be 0")]
        },
        Validator {
            name: "item_unit_price"
            validator: DoubleValidator {
                id: _unitPriceValidator
                top: 90000000.00
                bottom: 1.00
                decimals: 2
            }
            value: Number(_unitPriceInput.textField.text)
            required: true
            errors: [qsTr("Item %1 unit price cannot be 0."),qsTr("Cannot be 0")]
        },
        Validator {
            name: "remarks"
            validator: RegularExpressionValidator {
                id: _remarksValidator
            }
            value: _remarksInput.textField.text
            required: false
            errors: [qsTr("Please fill."),qsTr("Cannot be 0")]
        },
        Validator {
            name: "item_total_amount"
            validator: DoubleValidator {
                id: _totalAmountValidator
                top: 90000000.00
                bottom: 1.00
                decimals: 2
            }
            value: Number(_unitPriceInput.textField.text) * Number(_quantityInput.textField.text)
            required: true
            errors: [qsTr("Please fill."),qsTr("Cannot be 0")]
        }
    ]
    GridLayout{
        id: _grid
        anchors.fill: parent
        columns: 3
        Item{
            Layout.fillWidth: true
            Layout.columnSpan: 3
            Layout.preferredHeight: _descriptionInput.implicitHeight
            ValidatedField {
                id: _descriptionInput
                anchors.fill: parent
                label: qsTr("Description")
                placeholderText: qsTr("Enter description")
                errorMessage: qsTr("Please fill")
                validator: _descriptionValidator
                textField.text: model.item_description
                textField.onEditingFinished: {
                    model.item_description = _descriptionInput.textField.text
                }
            }
        }
        Item{
            Layout.fillWidth: true
            Layout.preferredHeight: _quantityInput.implicitHeight
            ValidatedField {
                id: _quantityInput
                anchors.fill: parent
                label: qsTr("Quantity")
                placeholderText: qsTr("Enter quantity")
                errorMessage: qsTr("Please specify")
                validator: _quantityValidator
                textField.text: model.item_qty
                textField.onEditingFinished: {
                    model.item_qty = Number(_quantityInput.textField.text)
                    //model.item_total_amount = model.item_unit_price * model.item_qty
                }
            }
        }
        Item{
            Layout.fillWidth: true
            Layout.preferredHeight: _unitPriceInput.implicitHeight
            ValidatedField {
                id: _unitPriceInput
                anchors.fill: parent
                label: qsTr("Unit Price")
                placeholderText: qsTr("0.00 TZS")
                errorMessage: qsTr("Please fill")
                validator: _unitPriceValidator
                textField.text: model.item_unit_price
                textField.onEditingFinished: {
                    model.item_unit_price = Number(_unitPriceInput.textField.text)
                }
            }
        }
        Item{
            Layout.fillWidth: true
            Layout.preferredHeight: _totalPriceInput.implicitHeight
            ValidatedField {
                id: _totalPriceInput
                anchors.fill: parent
                label: qsTr("Total Price")
                placeholderText: qsTr("0.00 TZS")
                errorMessage: qsTr("Please fill")
                enabled: false
                validator: _totalAmountValidator
                textField.text: Number(_quantityInput.textField.text) * Number(_unitPriceInput.textField.text)
                textField.onTextChanged: {
                    model.item_total_amount = Number(_totalPriceInput.textField.text)
                }
            }
        }
        Item{
            Layout.columnSpan: 3
            Layout.fillWidth: true
            Layout.preferredHeight: _remarksInput.implicitHeight
            ValidatedField {
                id: _remarksInput
                anchors.fill: parent
                label: qsTr("Remarks")
                placeholderText: qsTr("Enter remark")
                errorMessage: qsTr("Please fill")
                validator: _remarksValidator
                textField.text: model.remarks
                textField.onEditingFinished: {
                    model.remarks = _remarksInput.textField.text
                }
            }
        }
        Item {
            Layout.columnSpan: 3
            Layout.fillWidth: true
            Layout.preferredHeight: 50
            Felgo.IconButton {
                id: _icon
                iconType: Felgo.IconType.plus
                color: "green"
                anchors.centerIn: parent
                states: [
                    State {
                        when: _invoiceItemDelegate.displayAddIcon
                        PropertyChanges {
                            target: _icon
                            iconType: Felgo.IconType.plus
                            color: "green"
                        }
                    },
                    State {
                        when: !_invoiceItemDelegate.displayAddIcon
                        PropertyChanges {
                            target: _icon
                            iconType: Felgo.IconType.trash
                            color: "red"
                        }
                    }
                ]
                onClicked: {
                    if (_invoiceItemDelegate.displayAddIcon) {
                        _invoiceItemDelegate.addItem()
                    }
                    else {
                        _invoiceItemDelegate.removeItemAt(index)
                    }
                }
            }
        }
    }
}
