import QtQuick
import QtQuick.Layouts
import Felgo as Felgo
import QtQuick.Controls.Material as QC2
import "./pages"

Felgo.NavigationStack {
    id: _authStack
//    width: _root.screenWidth
//    height: _root.screenHeight
//    implicitWidth: width
//    implicitHeight: height
    initialPage: LoginPage{}
}
