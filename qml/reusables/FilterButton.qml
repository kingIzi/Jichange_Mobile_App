import QtQuick
import QtQuick.Layouts
import QtQuick.Controls.Material as QC2
import Felgo as Felgo

QC2.Button {
    id: _filterBtn
    QC2.Material.elevation: 0
    flat: true
    QC2.Material.background: Qt.color("#ffffff")
    Binding {
        target: _filterBtn.background
        property: "border.width"
        value: 1
    }
    Binding {
        target: _filterBtn.background
        property: "border.color"
        value: Felgo.Theme.colors.dividerColor
    }
    Binding {
        target: _filterBtn.background
        property: "radius"
        value: 5
    }
    contentItem: RowLayout {
        Felgo.AppIcon{
            iconType: Felgo.IconType.filter
            size: 20
        }
        Felgo.AppText {
            text: qsTr("Filter")
        }
        Felgo.AppIcon{
            iconType: Felgo.IconType.chevrondown
            size: 12
        }
    }
}
