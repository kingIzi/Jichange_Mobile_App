import QtQuick
import QtQuick.Controls.Material as QC2
import QtQuick.Layouts
import Felgo as Felgo
import CustomersTableModel 1.0
import "../reusables"
import "../components"

Felgo.FlickablePage {
    id: _customersPage
    title: qsTr("Customer(s)")
    backgroundColor: Qt.color("#F6F8FC")
    flickable.contentHeight: _col5.implicitHeight * 1.1
    navigationBarHidden: false
    FontLoader {
        id: _fontLoader
        source: "../../assets/fonts/Inter-Regular.ttf"
    }
    FontLoader {
        id: _fontBoldLoader
        source: "../../assets/fonts/Inter-ExtraBold.ttf"
    }
    Component {
        id: _addCustomerComponent
        AddCustomerPage{}
    }
    FilterDrawer {
        id: _filterDrawer
        _insets: _customersPage.safeArea.insets
    }
    ColumnLayout {
        id: _col5
        anchors.fill: parent
        anchors.leftMargin: 10
        anchors.rightMargin: 10
        anchors.topMargin: 10
        Item {
            Layout.fillWidth: true
            Layout.preferredHeight: _row12.implicitHeight
            RowLayout{
                id: _row12
                anchors.fill: parent
                Felgo.AppText{
                    Layout.alignment: Qt.AlignLeft
                    text: qsTr("Available customer(s)")
                    font.family: _fontLoader.name
                    font.pixelSize: sp(20)
                }
                CustomButton_v1 {
                    Layout.alignment: Qt.AlignRight
                    text: qsTr("Add Customer")
                    onClicked: {
                        _customerStack.push(_addCustomerComponent)
                    }
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
                spacing: dp(10)
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
                                TableListTabBar {
                                    id: _tableListTabBar
                                    Layout.alignment: Qt.AlignLeft
                                    Layout.maximumWidth: dp(100)
                                }
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
                Item{
                    Layout.fillWidth: true
                    Layout.preferredHeight: _col23.implicitHeight
                    ColumnLayout {
                        id: _col23
                        anchors.fill: parent
                        QC2.HorizontalHeaderView {
                            id: _tableHeader
                            syncView: _customersTable
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
                            Layout.preferredHeight: _customersTable.contentHeight
                            TableView {
                                id: _customersTable
                                anchors.fill: parent
                                columnSpacing: 1
                                rowSpacing: 1
                                clip: true
                                pointerNavigationEnabled: false
                                model: CustomersTableModel {
                                    id: _customersTableModel
                                    isEmpty: true
                                }
                                delegate: Rectangle {
                                    implicitWidth: 140
                                    implicitHeight: 50
                                    opacity: _customersTableModel.isEmpty ? 0 : 1
                                    Felgo.AppText {
                                        text: model.display
                                    }
                                }
                            }
                            Felgo.AppText{
                                topPadding: 10
                                text: "No data found"
                                anchors.centerIn: parent
                                visible: _customersTableModel.isEmpty
                            }
                        }
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
//                                    text: qsTr("1")
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
