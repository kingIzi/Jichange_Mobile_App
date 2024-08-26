import QtQuick
import QtQuick.Controls.Material as QC2
import Felgo as Felgo

Felgo.AppTabBar {
    id: _tabBar
    showIcon: true
    QC2.Material.accent: Qt.color("#8196FE")
    currentIndex: 1
    Felgo.AppTabButton {
        id: _tableBtn
        property color colorOff: Qt.color("#dddddd")
        property color colorOn: Qt.color("#8196FE")
        property int   spacingContentItem: 2
        property int   fontPixelSize: 12
        property int   iconSize: 20
        property bool  showText: true
        showIcon: true
        tabIcon: Felgo.IconType.table
        readonly property color selColor: selected ? colorOn : colorOff
        contentItem: Felgo.AppIcon{
            iconType: _tableBtn.tabIcon
            color: _tableBtn.selColor
        }
    }
    Felgo.AppTabButton {
        id: _listBtn
        property color colorOff: Qt.color("#dddddd")
        property color colorOn: Qt.color("#8196FE")
        property int   spacingContentItem: 2
        property int   fontPixelSize: 12
        property int   iconSize: 20
        property bool  showText: true
        showIcon: true
        tabIcon: Felgo.IconType.list
        readonly property color selColor: selected ? colorOn : colorOff
        contentItem: Felgo.AppIcon{
            iconType: _listBtn.tabIcon
            color: _listBtn.selColor
        }
    }

}
