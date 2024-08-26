import QtQuick
import QtQuick.Layouts
import QtQuick.Controls.Material as QC2
import Felgo as Felgo
import LatestTransactionsTableModel 1.0
import "../reusables"


Item{
    implicitHeight: _col14.implicitHeight
    FilterDrawer {
        id: _filterDrawer
        _insets: _dashboardPage.safeArea.insets
    }
    ColumnLayout {
        id: _col14
        anchors.fill: parent
        Item {
            Layout.fillWidth: true
            Layout.preferredHeight: _row16.implicitHeight
            RowLayout{
                id: _row16
                anchors.fill: parent
                TitleText {
                    Layout.alignment: Qt.AlignLeft
                    text: qsTr("Latest transactions")
                }

            }
        }
        QC2.Pane{
            Layout.fillWidth: true
            Layout.preferredHeight: _col21.implicitHeight * 1.1
            Layout.maximumHeight: 600
            Layout.bottomMargin: 10
            clip: true
            padding: 4
            QC2.Material.elevation: 1
            QC2.Material.background: Qt.color("#ffffff")
            contentItem: ColumnLayout{
                id: _col21
                //anchors.fill: parent
//                Item {
//                    Layout.fillWidth: true
//                    Layout.preferredHeight: _row17.implicitHeight
//                    RowLayout{
//                        id: _row17
//                        anchors.fill: parent
//                        Felgo.SearchBar {
//                            id: _searchBar
//                            iconRightPadding: 2
//                            inputBackgroundColor: Qt.color("#F3F5FE")
//                            Layout.fillWidth: true
//                        }
//                        DateRangeComboBox {
//                            Layout.alignment: Qt.AlignRight
//                            Layout.preferredWidth: implicitWidth
//                        }
//                    }
//                }
                Item {
                    Layout.fillWidth: true
                    Layout.preferredHeight: _col22.implicitHeight
                    ColumnLayout {
                        id: _col22
                        anchors.fill: parent
                        Felgo.SearchBar {
                            id: _searchBar
                            iconRightPadding: 2
                            inputBackgroundColor: Qt.color("#F3F5FE")
                            Layout.fillWidth: true
                        }
                        Item {
                            Layout.fillWidth: true
                            Layout.preferredHeight: _row17.implicitHeight
                            Layout.rightMargin: dp(16)
                            Layout.leftMargin: dp(16)
                            RowLayout {
                                id: _row17
                                anchors.fill: parent
                                FilterButton {
                                    id: _filterButton
                                    Layout.alignment: Qt.AlignRight
                                    onClicked: {
                                        _filterDrawer.open()
                                    }
                                }
                            }
                        }
                    }
                }
                QC2.HorizontalHeaderView {
                    id: _tableHeader
                    syncView: _latestTransactionsTable
                    Layout.fillWidth: true
                    Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                    QC2.Material.background: Qt.color("#F3F5FE")
                    delegate: QC2.ItemDelegate{
                        implicitHeight: 30
                        implicitWidth: 140
                        Rectangle {
                            anchors.fill: parent
                            color: Qt.color("#F3F5FE")
                            Felgo.AppText{
                                id: _tableHeaderText
                                text: model.display
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.left: parent.left
                                z: 10
                            }
                            Felgo.IconButton {
                                iconType: Felgo.IconType.sort
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.right: parent.right
                                z: 10
                            }
                        }
                    }
                }
                Item{
                    Layout.fillWidth: true
                    Layout.preferredHeight: _latestTransactionsTable.contentHeight
                    TableView {
                        id: _latestTransactionsTable
                        anchors.fill: parent
                        columnSpacing: 1
                        rowSpacing: 1
                        clip: true
                        pointerNavigationEnabled: false
                        model: LatestTransactionsTableModel {
                            id: _latestTransactionsTableModel
                            isEmpty: true
                        }
                        delegate: Rectangle {
                            implicitWidth: 140
                            implicitHeight: 50
                            opacity: _latestTransactionsTableModel.isEmpty ? 0 : 1
                            Felgo.AppText {
                                text: model.display
                            }
                        }
                    }
                    Felgo.AppText{
                        topPadding: 10
                        text: "No data found"
                        anchors.centerIn: parent
                        visible: _latestTransactionsTableModel.isEmpty
                    }
                }
                Item{
                    Layout.fillWidth: true
                    Layout.preferredHeight: _row20.implicitHeight
                    Layout.rightMargin: dp(6)
                    Layout.leftMargin: dp(16)
                    RowLayout{
                        id: _row20
                        anchors.fill: parent
                        CustomTextComboBox{
                            flat: true
                            model: [5,10,20]
                            Layout.maximumWidth: 80
                            Layout.alignment: Qt.AlignLeft
                            currentIndex: 0
                        }
                        Item{
                            Layout.alignment: Qt.AlignRight
                            Layout.preferredHeight: _row18.implicitHeight
                            Layout.preferredWidth: _row18.implicitWidth
                            RowLayout{
                                id: _row18
                                anchors.fill: parent
                                Felgo.IconButton{
                                    iconType: Felgo.IconType.chevronleft
                                    color: Qt.color("#000000")
                                }
                                QC2.ComboBox {
                                    id: _paginationComboBox
                                    model: [1,2,3,4,5,6]
                                    Layout.maximumWidth: 70
                                    flat: true
                                    Binding {
                                        target: _paginationComboBox.background
                                        property: "border.width"
                                        value: 1
                                    }
                                    Binding {
                                        target: _paginationComboBox.background
                                        property: "border.color"
                                        value: Felgo.Theme.colors.dividerColor
                                    }
                                }
                                Felgo.IconButton{
                                    iconType: Felgo.IconType.chevronright
                                    color: Qt.color("#000000")
                                }
                            }
                        }
                    }
                }
//                Item{
//                    Layout.fillWidth: true
//                    Layout.preferredHeight: _row20.implicitHeight
//                    RowLayout{
//                        id: _row20
//                        anchors.fill: parent
//                        CustomTextComboBox{
//                            flat: true
//                            model: [5,10,20]
//                            Layout.maximumWidth: 80
//                            Layout.alignment: Qt.AlignLeft
//                            currentIndex: 0
//                        }
//                        Item{
//                            Layout.alignment: Qt.AlignRight
//                            Layout.preferredHeight: _row18.implicitHeight
//                            Layout.preferredWidth: _row18.implicitWidth
//                            RowLayout{
//                                id: _row18
//                                anchors.fill: parent
//                                spacing: 10
//                                Felgo.AppIcon{
//                                    iconType: Felgo.IconType.chevronleft
//                                }

//                                Felgo.AppText{
//                                    text: "1"
//                                }
//                                Felgo.AppIcon{
//                                    iconType: Felgo.IconType.chevronright
//                                }
//                            }
//                        }
//                    }
//                }
            }
        }
    }
}
