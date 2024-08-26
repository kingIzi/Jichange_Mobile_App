import QtQuick
import QtQuick.Controls.Material as QC2
import QtQuick.Layouts
import QtCharts
import Felgo as Felgo
import "../components"
import "../reusables"
import "../scripts/utilities.js" as Utils

Felgo.FlickablePage {
    id: _dashboardPage
    title: qsTr("Home")
    backgroundColor: Qt.color("#F6F8FC")
    flickable.contentHeight: _col4.implicitHeight * 1.1
    navigationBarHidden: false
    FontLoader {
        id: _fontLoader
        source: "../../assets/fonts/Inter-Regular.ttf"
    }
    FontLoader {
        id: _fontBoldLoader
        source: "../../assets/fonts/Inter-ExtraBold.ttf"
    }
    ColumnLayout {
        id: _col4
        anchors.fill: parent
        anchors.leftMargin: 10
        anchors.rightMargin: 10
        anchors.topMargin: 10
        DashboardOverview {
            id: _dashboardOverview
            Layout.fillWidth: true
            Layout.preferredHeight: implicitHeight
        }
        Item{
            Layout.fillWidth: true
            Layout.preferredHeight: _col12.implicitHeight
            ColumnLayout{
                id: _col12
                anchors.fill: parent
                Item {
                    Layout.fillWidth: true
                    Layout.preferredHeight: _row13.implicitHeight
                    RowLayout{
                        id: _row13
                        anchors.fill: parent
                        TitleText {
                            Layout.alignment: Qt.AlignLeft
                            text: qsTr("Transaction")
                        }

                        DateRangeComboBox {
                            Layout.alignment: Qt.AlignRight
                        }
                    }
                }
                Item{
                    Layout.fillWidth: true
                    Layout.preferredHeight: 300
                    ChartView {
                        id: _chart
                        title: "Transactions"
                        anchors.fill: parent
                        antialiasing: true
                        titleFont.family: _fontLoader.name
                        DateTimeAxis {
                            id: _dateTimeAxis
                            format: "yyyy MMM"
                            tickCount: 5
                            labelsVisible: false
                            visible: false
                            //min: new Date(2023, 1, 8)
                            labelsFont.family: _fontLoader.name
                        }
                        ValuesAxis{
                            id: _valueAxis
                            min: 0
                            max: 8000000
                            titleText: "Amount TZS"
                            labelFormat: "%d TZS\n"
                            labelsFont.family: _fontLoader.name
                        }
                        BarSeries {
                            id: myBarSeries
                            axisX: BarCategoryAxis {
                                id: barCategoriesAxis
                                titleText: "Status"
                                categories: ["Pending","In Progress","Paid","Cancelled"]
                                labelsFont.family: _fontLoader.name
                            }
                            axisY: ValuesAxis{
                                min: 0
                                max: 150
                                titleText: "Volume"
                                labelFormat: "%.0f \n"
                                labelsFont.family: _fontLoader.name
                            }
                            labelsVisible: false
                            BarSet {
                                color: "#3B70CA"
                                label: "Volume";
                                values: [146, 20, 120, 50]
                                labelFont.family: _fontLoader.name
                            }
                        }
                        LineSeries {
                            id: _lineSeries
                            name: "Transactions"
                            color: "#94DFD7"
                            axisX: _dateTimeAxis
                            axisYRight: _valueAxis
                            capStyle: "RoundCap"
                            width: 2
                            pointsVisible: true
                            XYPoint { x: Utils.toMsecsSinceEpoch(new Date(2023, 1, 8)); y: 1500000 }
                            XYPoint { x: Utils.toMsecsSinceEpoch(new Date(2023, 1, 18)); y: 3500000 }
                            XYPoint { x: Utils.toMsecsSinceEpoch(new Date(2023, 2, 13)); y: 1000000 }
                            XYPoint { x: Utils.toMsecsSinceEpoch(new Date(2023, 3, 3)); y: 600000 }
                            XYPoint { x: Utils.toMsecsSinceEpoch(new Date(2023, 3, 8)); y: 2000000 }
                            XYPoint { x: Utils.toMsecsSinceEpoch(new Date(2023, 3, 13)); y: 4200000 }
                            XYPoint { x: Utils.toMsecsSinceEpoch(new Date(2023, 3, 19)); y: 7400000 }
                        }
                    }
                }
            }
        }
        Item{
            Layout.fillWidth: true
            Layout.preferredHeight: _col13.implicitHeight
            ColumnLayout{
                id: _col13
                anchors.fill: parent
                Item {
                    Layout.fillWidth: true
                    Layout.preferredHeight: _row15.implicitHeight
                    RowLayout{
                        id: _row15
                        anchors.fill: parent
                        TitleText {
                            Layout.alignment: Qt.AlignLeft
                            text: qsTr("All Operations")
                        }

                        DateRangeComboBox {
                            Layout.alignment: Qt.AlignRight
                        }
                    }
                }
                Item{
                    Layout.fillWidth: true
                    Layout.preferredHeight: 300
                    ChartView {
                        id: _allOperationsChart
                        anchors.fill: parent
                        antialiasing: true
                        titleFont.family: _fontLoader.name
                        title: qsTr("All operations")
                        BarSeries {
                            id: mySeries
                            axisX: BarCategoryAxis {
                                labelsFont.family: _fontLoader.name
                                categories: ["Done", "Approved", "Pending", "Cancelled"]
                            }
                            BarSet {
                                label: "Paid Amount";
                                values: [2, 2, 3, 4, 5, 6]
                                color: "#3B70CA"
                                labelFont.family: _fontLoader.name
                            }
                            BarSet {
                                label: "Balance";
                                values: [5, 1, 2, 4, 1, 7]
                                color: "#94DFD7"
                                labelFont.family: _fontLoader.name
                            }
                        }
                    }
                }
            }
        }
        DashboardLatestTransactionsTable {
            Layout.fillWidth: true
            Layout.preferredHeight: implicitHeight
            Layout.topMargin: 20
        }
    }
}
