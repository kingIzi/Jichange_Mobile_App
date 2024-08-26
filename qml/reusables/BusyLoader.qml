import QtQuick
import QtQuick.Controls.Material as QC2

QC2.Popup {
    id: _busy
    property bool _isRunning: false
    width: 100
    height: 100
    anchors.centerIn: parent
    modal: true
    background: Item{}
    closePolicy: QC2.Popup.NoAutoClose
    contentItem: QC2.BusyIndicator {
        QC2.Material.accent: Qt.color("#8196FE")
        running: _busy._isRunning
        anchors.centerIn: parent
        z: 50
    }
}
