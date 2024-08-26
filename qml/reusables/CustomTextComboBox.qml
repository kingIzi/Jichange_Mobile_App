import QtQuick
import QtQuick.Controls.Material as QC2
import Felgo as Felgo

QC2.ComboBox {
    id: _comboBox
    QC2.Material.accent: Qt.color("#8196FE")
    currentIndex: -1
    displayText: currentIndex === -1 ? qsTr("Please select") : currentText
    font.family: _fontLoader.name
    font.pixelSize: sp(12)
    flat: true
    FontLoader {
        id: _fontLoader
        source: "../../assets/fonts/Inter-Regular.ttf" // loaded from your assets folder
    }
    Binding{
        target: _comboBox.background
        property: "border.width"
        value: 1
    }
    Binding{
        target: _comboBox.background
        property: "border.color"
        value: Felgo.Theme.colors.dividerColor
    }
}

//QC2.ComboBox {
//    id: _branchComboBox
//    signal itemModelClicked(int index)
//    model: ["HQ Dar es Salaam", "Branch #2", "Branch #3"]
//    QC2.Material.accent: Qt.color("#8196FE")
//    currentIndex: -1
//    displayText: currentIndex === -1 ? qsTr("Please select") : currentText
//    FontLoader {
//        id: _fontLoader
//        source: "../../assets/fonts/Inter-Regular.ttf" // loaded from your assets folder
//    }
//    font.family: _fontLoader.name
//    font.pixelSize: sp(12)
//    flat: true
//    Binding{
//        target: _branchComboBox.background
//        property: "border.width"
//        value: 1
//    }
//    Binding{
//        target: _branchComboBox.background
//        property: "border.color"
//        value: Felgo.Theme.colors.dividerColor
//    }
//    Component {
//        id: _delegate
//        QC2.ItemDelegate {
//            width: _branchComboBox.width
//            contentItem: Felgo.AppText {
//                id: _delegateText
//                text: model[textRole]
//                color: Qt.color("#000000")
//                font: _branchComboBox.font
//                elide: Text.ElideRight
//                verticalAlignment: Text.AlignVCenter
//                states: [
//                    State {
//                        when: _branchComboBox.currentIndex === index
//                        PropertyChanges {
//                            target: _delegateText
//                            color: Qt.color("#8196FE")
//                        }
//                    }
//                ]
//            }
//            highlighted: _branchComboBox.highlightedIndex === index
//            onClicked: {
//                _branchComboBox.currentIndex = index
//                //_branchComboBox.itemModelClicked(index)
//            }
//        }
//    }
//    delegate: _delegate
//    popup: QC2.Popup {
//        y: _branchComboBox.height - 1
//        width: _branchComboBox.width
//        implicitHeight: contentItem.implicitHeight
//        padding: 1
//        contentItem: ListView {
//            clip: true
//            implicitHeight: contentHeight
//            model: _branchComboBox.popup.visible ? _branchComboBox.delegateModel : null
//            currentIndex: _branchComboBox.highlightedIndex
//            QC2.ScrollIndicator.vertical: QC2.ScrollIndicator { }
//        }
//    }
//}


