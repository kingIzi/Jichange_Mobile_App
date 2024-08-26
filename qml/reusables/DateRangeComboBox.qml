import QtQuick
import QtQuick.Layouts
import QtQuick.Controls.Material as QC2
import Felgo as Felgo

QC2.ComboBox {
    id: _branchComboBox
    model: ["This week","Last month","Last 3 months","Last year"]
    QC2.Material.accent: Qt.color("#8196FE")
    font.family: _fontLoader.name
    font.pixelSize: sp(12)
    flat: true
    Binding{
        target: _branchComboBox.background
        property: "border.width"
        value: 1
    }
    Binding{
        target: _branchComboBox.background
        property: "border.color"
        value: Felgo.Theme.colors.dividerColor
    }
    contentItem: RowLayout {
        width: _branchComboBox.width
        Felgo.AppIcon {
            iconType: Felgo.IconType.calendar
            Layout.leftMargin: 5
        }
        Felgo.AppText {
            text: _branchComboBox.model[_branchComboBox.currentIndex]
            color: Qt.color("#000000")
            font: _branchComboBox.font
            elide: Text.ElideRight
            verticalAlignment: Text.AlignVCenter
        }
    }

    delegate: QC2.ItemDelegate {
        width: _branchComboBox.width
        contentItem: Felgo.AppText {
            id: _delegateText
            text: modelData
            color: Qt.color("#000000")
            font: _branchComboBox.font
            elide: Text.ElideRight
            verticalAlignment: Text.AlignVCenter
            states: [
                State {
                    when: _branchComboBox.currentIndex === index
                    PropertyChanges {
                        target: _delegateText
                        color: Qt.color("#8196FE")
                    }
                }
            ]
        }
        highlighted: _branchComboBox.highlightedIndex === index
    }
    popup: QC2.Popup {
        y: _branchComboBox.height - 1
        width: _branchComboBox.width
        implicitHeight: contentItem.implicitHeight
        padding: 1
        contentItem: ListView {
            clip: true
            implicitHeight: contentHeight
            model: _branchComboBox.popup.visible ? _branchComboBox.delegateModel : null
            currentIndex: _branchComboBox.highlightedIndex
            QC2.ScrollIndicator.vertical: QC2.ScrollIndicator { }
        }
    }
}
