import QtQuick
import QtQuick.Controls.Material as QC2
import QtQuick.Layouts
import Felgo as Felgo

Item {
    id: _item4
    signal breadcrumbClicked(int index)
    implicitWidth: _root.width
    implicitHeight: _row18.implicitHeight
    property ListModel _listModel: ListModel{
        id: _breadCrumbsListModel
    }
    RowLayout {
        id: _row18
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        Repeater {
            model: _item4._listModel
            delegate: Item {
                Layout.preferredWidth: _row12.implicitWidth
                Layout.preferredHeight: _row12.implicitHeight
                RowLayout{
                    id: _row12
                    anchors.fill: parent
                    Felgo.AppText {
                        id: _breadcrumbText
                        text: label
                        Layout.fillWidth: true
                        font.underline: false
                        color: Qt.color("#000000")
                        states: [
                            State {
                                when: _mouse.pressed && index !== _item4._listModel.rowCount() - 1
                                PropertyChanges {
                                    target: _breadcrumbText
                                    color: Qt.color("#8196FE")
                                    font.underline: true
                                }
                            }
                        ]
                    }
                    Felgo.AppIcon {
                        iconType: Felgo.IconType.chevronright
                        size: 8
                        visible: _listModel.rowCount() > 1 && index !== _listModel.rowCount() - 1
                        Layout.fillWidth: true
                    }
                }
                MouseArea{
                    id: _mouse
                    anchors.fill: parent
                    onClicked: {
                        _item4.breadcrumbClicked(index)
                    }
                }
            }
        }
    }
}
