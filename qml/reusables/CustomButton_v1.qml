import QtQuick
import QtQuick.Controls.Material as QC2


QC2.Button{
    id: _createInvoiceBtn
    FontLoader {
        id: _fontLoader
        source: "../../assets/fonts/Inter-ExtraBold.ttf"
    }
    font.family:  _fontLoader.name
    font.pixelSize: sp(14)
    font.capitalization: Font.AllUppercase
    topPadding: 2
    bottomPadding: 2
    leftPadding: 10
    rightPadding: 10
    QC2.Material.background: Qt.color("#F3F5FE")
    QC2.Material.foreground: Qt.color("#8196FE")
    flat: true
    Binding {
        target: _createInvoiceBtn.background
        property: "radius"
        value: 5
    }
    Binding {
        target: _createInvoiceBtn.background
        property: "border.color"
        value: "transparent"
    }
}
