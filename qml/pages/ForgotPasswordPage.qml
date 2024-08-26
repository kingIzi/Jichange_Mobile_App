import QtQuick
import QtQuick.Controls.Material as QC2
import Felgo as Felgo
import "../components"

Felgo.AppPage {
    id: _loginPage
    navigationBarHidden: true
    backgroundColor: Qt.color("#F6F8FC")
    Item {
        anchors.centerIn: parent
        implicitWidth: parent.width
        implicitHeight: _pane3.implicitHeight * 1.1
        QC2.Pane {
            id: _pane3
            QC2.Material.background: Qt.color("#ffffff")
            QC2.Material.elevation: 1
            anchors.fill: parent
            anchors.leftMargin: 10
            anchors.rightMargin: 10
            contentItem: ForgotPassword{}
        }
    }
}
