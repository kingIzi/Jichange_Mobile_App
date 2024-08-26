import QtQuick
import QtQuick.Controls.Material as QC2
import QtQuick.Layouts
import QtQuick.Shapes
import Felgo as Felgo

Felgo.FlickablePage {
    id: _userProfilePage
    title: qsTr("Profile")
    backgroundColor: Qt.color("#F6F8FC")
    flickable.contentHeight: _col6.implicitHeight
    navigationBarHidden: false
    ColumnLayout{
        id: _col6
        anchors.fill: parent
        Item {
            id: _rect
            readonly property int _height: 150
            Layout.fillWidth: true
            Layout.preferredHeight: _rect._height
            Shape{
                anchors.fill: parent
                ShapePath {
                    strokeWidth: 0
                    strokeColor: "transparent"
                    strokeStyle: ShapePath.SolidLine
                    startX: 0; startY: _rect._height
                    capStyle: ShapePath.RoundCap
                    fillColor: Qt.color("#004D40")
                    PathAngleArc {
                        centerX: _rect.width / 2
                        radiusY: _rect._height
                        radiusX: _rect.width / 2
                        startAngle: 0
                        sweepAngle: 180
                    }
                }
                Felgo.AppText {
                    text: "S"
                    anchors.centerIn: parent
                    font.pixelSize: sp(48)
                    color: Qt.color("#ffffff")
                }
            }
        }
        Item {
            Layout.fillWidth: true
            Layout.preferredHeight: _col7.implicitHeight * 1.1
            ColumnLayout {
                id: _col7
                anchors.fill: parent
                anchors.margins: 10
                spacing: 10
                Felgo.AppListItem {
                    Layout.fillWidth: true
                    detailTextFontSize: sp(16)
                    detailTextColor: Qt.color("#000000")
                    textColor: Felgo.Theme.colors.dividerColor
                    textFontSize: sp(14)
                    text: qsTr("Full name")
                    detailText: qsTr("Solange Amaye Kapinga")
                    backgroundColor: "transparent"
                    muted: true
                    mutedOpacity: 1
                }
                Felgo.AppListItem {
                    Layout.fillWidth: true
                    detailTextFontSize: sp(16)
                    detailTextColor: Qt.color("#000000")
                    textColor: Felgo.Theme.colors.dividerColor
                    textFontSize: sp(14)
                    text: qsTr("E-Mail")
                    detailText: qsTr("solange.k.amaye@gmail.com")
                    backgroundColor: "transparent"
                    muted: true
                    mutedOpacity: 1
                }
                Felgo.AppListItem {
                    Layout.fillWidth: true
                    detailTextFontSize: sp(16)
                    detailTextColor: Qt.color("#000000")
                    textColor: Felgo.Theme.colors.dividerColor
                    textFontSize: sp(14)
                    text: qsTr("Phone number")
                    detailText: qsTr("+255 742036609")
                    backgroundColor: "transparent"
                    muted: true
                    mutedOpacity: 1
                }
                QC2.ToolSeparator {
                    Layout.topMargin: 10
                    orientation: "Horizontal"
                    Layout.fillWidth: true
                }
                Felgo.AppListItem {
                    Layout.fillWidth: true
                    detailTextFontSize: sp(16)
                    detailTextColor: Qt.color("#000000")
                    textColor: Felgo.Theme.colors.dividerColor
                    textFontSize: sp(14)
                    text: qsTr("Role")
                    detailText: qsTr("Vendor")
                    backgroundColor: "transparent"
                    muted: true
                    mutedOpacity: 1
                }
                Felgo.AppListItem {
                    Layout.fillWidth: true
                    detailTextFontSize: sp(16)
                    detailTextColor: Qt.color("#000000")
                    textColor: Felgo.Theme.colors.dividerColor
                    textFontSize: sp(14)
                    text: qsTr("Business")
                    detailText: qsTr("Biz Logic Solutions")
                    backgroundColor: "transparent"
                    muted: true
                    mutedOpacity: 1
                }
                QC2.ToolSeparator {
                    Layout.topMargin: 10
                    orientation: "Horizontal"
                    Layout.fillWidth: true
                }
                Felgo.AppListItem {
                    id: _logout
                    Layout.fillWidth: true
                    textColor: "red"
                    textFontSize: sp(16)
                    text: qsTr("Logout")
                    backgroundColor: "transparent"
                    Connections {
                        target: _logout.mouseArea
                        function onClicked() {
                            _mainLoader.state = "Auth"
                        }
                    }
                    rightItem: Rectangle {
                        width: 40
                        height: 40
                        color: "transparent"
                        Felgo.AppIcon {
                            anchors.centerIn: parent
                            iconType: Felgo.IconType.signout
                            color: "red"
                            anchors.topMargin: 10
                        }
                    }
                }
            }
        }
    }
}
