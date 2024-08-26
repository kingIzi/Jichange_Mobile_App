import QtQuick
import QtQuick.Layouts
import QtQuick.Controls.Material as QC2
import Felgo as Felgo
import "../reusables"
import "../pages"
import "../list_models"

Item{
    implicitHeight: _col11.implicitHeight
    FontLoader {
        id: _fontLoader
        source: "../../assets/fonts/Inter-ExtraBold.ttf" // loaded from your assets folder
    }
    Component {
        id: _addInvoicePage
        AddInvoicePage{}
    }
    ColumnLayout{
        id: _col11
        anchors.fill: parent
        spacing: 8
        Item {
            Layout.fillWidth: true
            Layout.preferredHeight: _row12.implicitHeight
            RowLayout{
                id: _row12
                anchors.fill: parent
                TitleText {
                    text: qsTr("Overview")
                    Layout.alignment: Qt.AlignLeft
                }

                CustomButton_v1 {
                    Layout.alignment: Qt.AlignRight
                    text: qsTr("Create Invoice")
                    onClicked: {
                        _dashboardStack.push(_addInvoicePage)
                    }
                }

            }
        }
        ListView {
            Layout.fillWidth: true
            Layout.preferredHeight: 140
            orientation: ListView.Horizontal
            spacing: 8
            model: DashboardOverviewModel {
                id: _dashboardOverviewModel
            }

//            model: [
//                {
//                    "stat": 12,
//                    "label": "Transaction",
//                    "img": "../../assets/img/transaction.png",
//                    "increased": true,
//                    "navToIndex": 2
//                },
//                {
//                    "stat": 0,
//                    "label": "Due",
//                    "img": "../../assets/img/check-mark.png",
//                    "increased": false,
//                    "navToIndex": 2
//                },
//                {
//                    "stat": 0,
//                    "label": "Expired",
//                    "img": "../../assets/img/man.png",
//                    "increased": false,
//                    "navToIndex": 3
//                },
//                {
//                    "stat": 0,
//                    "label": "Customer(s)",
//                    "img": "../../assets/img/customer-review.png",
//                    "increased": true,
//                    "navToIndex": 1
//                },
//            ]
            delegate: QC2.Pane{
                id: _pane
                width: 200
                height: 100
                QC2.Material.elevation: 1
                Binding {
                    target: _pane.background
                    property: "radius"
                    value: 10
                }
                implicitHeight: _row8.implicitHeight
                RowLayout{
                    id: _row8
                    anchors.fill: parent
                    Item {
                        Layout.fillWidth: true
                        Layout.preferredHeight: _col12.implicitHeight
                        ColumnLayout{
                            id: _col12
                            anchors.fill: parent
                            Felgo.AppText{
                                Layout.alignment: Qt.AlignLeft
                                text: model.stat
                                font.pixelSize: sp(20)
                                font.family: _fontLoader.name
                            }
                            Felgo.AppText{
                                Layout.alignment: Qt.AlignLeft
                                text: model.label
                                font.pixelSize: sp(14)
                            }
                            Item{
                                Layout.preferredHeight: _row7.implicitHeight
                                Layout.preferredWidth: _row7.implicitWidth
                                MouseArea{
                                    id: _mouse
                                    anchors.fill: parent
                                    onClicked: {
                                        _vendorNavigation.currentIndex = navToIndex
                                    }
                                }
                                RowLayout{
                                    id: _row7
                                    anchors.fill: parent
                                    Felgo.AppIcon {
                                        iconType: model.increased ? Felgo.IconType.arrowup : Felgo.IconType.arrowdown
                                        color: model.increased ? "green" : "orange"
                                        size: 12
                                    }
                                    Felgo.AppText {
                                        id: _lbl
                                        text: "View more"
                                        color: Qt.color("#8196FE")
                                        font.underline: _mouse.pressed
                                        font.pixelSize: sp(12)
                                        //font: Constants.bold.h6
                                        //Material.foreground: Qt.color(Constants.colors.linkBlue)
                                    }
                                }
                            }
                        }
                    }
                    Felgo.AppImage{
                        source: model.img
                        sourceSize: Qt.size(48,48)
                        fillMode: Image.PreserveAspectFit
                    }
                }
            }
        }
    }
}
