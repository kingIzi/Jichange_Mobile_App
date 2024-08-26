import QtQuick
import QtQuick.Layouts
import QtLocation
import QtQuick.Shapes
import QtQuick.Controls.Material as QC2
import Felgo as Felgo
import "../reusables"
import "../components"

Felgo.FlickablePage {
    id: _companyUsersPage
    title: qsTr("Company Users")
    backgroundColor: Qt.color("#F6F8FC")
    flickable.contentHeight: _col5.implicitHeight
    navigationBarHidden: false
    tabBarHidden: true
    FilterDrawer {
        id: _filterDrawer
        _insets: _companyUsersPage.safeArea.insets
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
                    text: qsTr("Company Users(s)")
                    font.pixelSize: sp(20)
                }
                CustomButton_v1 {
                    Layout.alignment: Qt.AlignRight
                    text: qsTr("Add")
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
            }
        }
    }
}
