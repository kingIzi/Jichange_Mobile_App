import QtQuick
import QtQuick.Controls.Material as QC2

QC2.Button {
    id: _customBtn
    text: qsTr("Sign In")
    FontLoader {
        id: _fontLoader
        source: "../../assets/fonts/Inter-ExtraBold.ttf" // loaded from your assets folder
    }
    font.family:  _fontLoader.name
    font.pixelSize: sp(18)
    font.capitalization: Font.AllUppercase
    QC2.Material.background: Qt.color("#8196FE")
    QC2.Material.foreground: Qt.color("#ffffff")
    //font.capitalization: "AllUppercase"
}
