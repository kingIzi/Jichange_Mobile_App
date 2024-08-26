import QtQuick
import QtQuick.Controls.Material as QC2


QC2.Button{
    id: _customBtn3
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
    QC2.Material.foreground: "red"
    flat: true
    Binding {
        target: _customBtn3.background
        property: "color"
        value: "transparent"
    }
    Binding {
        target: _customBtn3.background
        property: "radius"
        value: 5
    }
    Binding {
        target: _customBtn3.background
        property: "border.color"
        value: "red"
    }
    Binding {
        target: _customBtn3.background
        property: "border.width"
        value: 1
    }
}
