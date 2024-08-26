import QtQuick
import QtQuick.Layouts
import QtQuick.Controls.Material as QC2
import Felgo as Felgo
import "../reusables"

QC2.Drawer {
    id: _filterDrawer
    edge: "BottomEdge"
    width: _root.width
    height: 400
    padding: 20
    property var _insets: undefined
    background: Rectangle{
        id: _bgRect
        color: Qt.color("#ffffff")
        radius: 40
        Rectangle {
            width: parent.width
            height: _bgRect.radius
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.right: parent.right
        }
    }
    ColumnLayout {
        anchors.fill: parent
        Item {
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.maximumHeight: _filterDrawer.height - _filterDrawer._insets.bottom
            Layout.alignment: Qt.AlignTop
            ColumnLayout {
                anchors.fill: parent
                Felgo.AppText{
                    id: _filterText
                    Layout.fillWidth: true
                    Layout.topMargin: 20
                    Layout.leftMargin: 20
                    Layout.rightMargin: 20
                    Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                    text: qsTr("Filter by")
                    font.pixelSize: sp(20)
                    font.bold: true
                }
                Item {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    Layout.topMargin: 20
                    Layout.leftMargin: 20
                    Layout.rightMargin: 20
                    RowLayout {
                        id: _splitView
                        anchors.fill: parent
                        Item {
                            id: _itemFilterList
                            Layout.fillWidth: true
                            Layout.fillHeight: true
                            Felgo.AppListView {
                                id: _filterbyList
                                anchors.fill: parent
                                currentIndex: 0
                                model: [qsTr("Date(s)")]
                                highlight: Item {
                                    id: _itemHighlight
                                    z: 10
                                    Rectangle {
                                        anchors.left: parent.left
                                        anchors.top: parent.top
                                        anchors.bottom: parent.bottom
                                        color: Qt.color("#8196FE")
                                        width: 4
                                        height: parent.height
                                    }
                                }
                                delegate: Felgo.SimpleRow {
                                    id: _filterByItem
                                    text: modelData
                                    width: _itemFilterList.width
                                    Connections {
                                        target: _filterByItem.mouseArea
                                        function onClicked() {
                                            _filterbyList.currentIndex = index
                                        }
                                    }
                                }
                            }
                        }
                        Item {
                            Layout.fillWidth: true
                            Layout.fillHeight: true
                            clip: true
                            QC2.SwipeView {
                                id: _filterSwipe
                                orientation: "Vertical"
                                currentIndex: _filterbyList.currentIndex
                                anchors.fill: parent
                                interactive: false
                                Item {
                                    ColumnLayout {
                                        anchors.top: parent.top
                                        anchors.left: parent.left
                                        anchors.right: parent.right
                                        Item {
                                            Layout.fillWidth: true
                                            Layout.preferredHeight: _startDate.implicitHeight
                                            ValidatedDateField {
                                                id: _startDate
                                                label: qsTr("Start date")
                                                errorMessage: qsTr("Please enter a valid date")
                                                anchors.fill: parent
                                                textField.onActiveFocusChanged: {
                                                    hasError = !textField.activeFocus && !textField.acceptableInput
                                                }
                                                Connections {
                                                    target: _startDate
                                                    function onAccepted(date) {
                                                        console.log(date)
                                                    }
                                                }
                                            }
                                        }
                                        Item{
                                            Layout.fillWidth: true
                                            Layout.preferredHeight: _endDate.implicitHeight
                                            ValidatedDateField {
                                                id: _endDate
                                                label: qsTr("End date")
                                                errorMessage: qsTr("Please enter a valid date")
                                                anchors.fill: parent
                                                textField.onActiveFocusChanged: {
                                                    hasError = !textField.activeFocus && !textField.acceptableInput
                                                }
                                                Connections {
                                                    target: _endDate
                                                    function onAccepted(date) {
                                                        console.log(date)
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                Item {
                    Layout.rightMargin: 20
                    Layout.fillWidth: true
                    Layout.preferredHeight: _row13.implicitHeight
                    RowLayout {
                        id: _row13
                        anchors.fill: parent
                        CustomButton_v2 {
                            text: qsTr("Filter")
                            Layout.alignment: Qt.AlignRight
                        }
                    }
                }
            }
        }
    }
}
