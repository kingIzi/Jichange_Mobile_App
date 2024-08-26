import QtQuick
import Felgo as Felgo

Felgo.AppText{
    FontLoader {
        id: _fontLoader
        source: "../../assets/fonts/Inter-ExtraBold.ttf"
    }
    text: qsTr("Overview")
    font.family: _fontLoader.name
    font.pixelSize: sp(20)
}
