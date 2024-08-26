import QtQuick
import QtQuick.Layouts
import QtLocation
import QtQuick.Shapes
import QtQuick.Controls.Material as QC2
import Felgo as Felgo
import "../reusables"
import "../components"
import "../scripts/requester.js" as Req

Felgo.FlickablePage {
    id: _generatedInvoicePage
    title: qsTr("Generated Invoice")
    backgroundColor: Qt.color("#F6F8FC")
    flickable.contentHeight: _col5.implicitHeight + 40
    navigationBarHidden: false
    tabBarHidden: true
    rightBarItem: Felgo.ActivityIndicatorBarItem {
        animating: Felgo.HttpNetworkActivityIndicator.enabled
        visible: animating
    }
    property int page: 1
    readonly property int limit: 5
    readonly property var _userProfile: _authRequests.getCurrentUser()
    FilterDrawer {
        id: _filterDrawer
        _insets: _generatedInvoicePage.safeArea.insets
    }
    Felgo.JsonListModel {
        id: _jsonListModel
        keyField: "Inv_Mas_Sno"
    }
    Felgo.SortFilterProxyModel {
        id: _sortProxyJsonListModel
        sourceModel: _jsonListModel
    }

//    CustomPaginator {
//        id: _customPaginator
//        _pageSize: 5
//        _pageIndex: 13
//        _maxPageSize: Math.ceil(_generatedInvoiceObj._generatedInvoicesListData.length / _customPaginator._pageSize)
//    }
    ColumnLayout {
        id: _col5
        anchors.fill: parent
        anchors.leftMargin: 10
        anchors.rightMargin: 10
        anchors.topMargin: 10
        Item {
            id: _item3
            Layout.fillWidth: true
            Layout.preferredHeight: _row12.implicitHeight
            RowLayout{
                id: _row12
                anchors.fill: parent
                Felgo.AppText{
                    Layout.alignment: Qt.AlignLeft
                    text: qsTr("Generated Invoice(s)")
                    font.pixelSize: sp(20)
                }
//                Felgo.IconButton {
//                    iconType: Felgo.IconType.barchart
//                    color: "orange"
//                }
            }
        }
        QC2.Pane {
            Layout.fillWidth: true
            Layout.preferredHeight: _gridView.contentHeight
            QC2.Material.elevation: 1
            QC2.Material.background: Qt.color("#ffffff")
            contentItem: ListView {
                id: _gridView
                anchors.fill: parent
                interactive: false
                model: _jsonListModel
                header: Item {
                    id: _item4
                    implicitHeight: _col22.implicitHeight
                    implicitWidth: _gridView.width
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
                            }
                        }
                    }
                }
                footer: Item{
                    implicitHeight: _row20.implicitHeight
                    implicitWidth: _gridView.width
                    RowLayout{
                        id: _row20
                        anchors.fill: parent
                        anchors.rightMargin: dp(16)
                        anchors.leftMargin: dp(16)
                        Felgo.AppText {
                            text: qsTr("Showing 1-5 of 61 items.")
                        }
                        Item{
                            Layout.alignment: Qt.AlignRight
                            Layout.preferredHeight: _row18.implicitHeight
                            Layout.preferredWidth: _row18.implicitWidth
                            RowLayout{
                                id: _row18
                                anchors.fill: parent
//                                Felgo.IconButton{
//                                    iconType: Felgo.IconType.chevronleft
//                                    color: Qt.color("#000000")
//                                    enabled: _customPaginator._maxPageSize > 1
//                                    onClicked: {
//                                        _customPaginator._pageIndex--
//                                    }
//                                }
//                                Felgo.IconButton{
//                                    iconType: Felgo.IconType.chevronright
//                                    color: Qt.color("#000000")
//                                    enabled: _customPaginator._pageIndex <= _customPaginator._maxPageSize
//                                    onClicked: {
//                                        _customPaginator._pageIndex++
//                                    }
//                                }
                            }
                        }
                    }
                }
                delegate: QC2.ItemDelegate {
                    id: _delegate
                    readonly property var _invoice: model
                    anchors.left: parent.left
                    anchors.right: parent.right
                    QC2.Material.elevation: 1
                    height: _pane3.implicitHeight
                    width: _gridView.width
                    contentItem: QC2.Pane {
                        id: _pane3
                        implicitHeight: _col30.implicitHeight * 1.4
                        QC2.Material.elevation: 1
                        states: [
                            State {
                                when: index % 2 === 0
                                PropertyChanges {
                                    target: _pane3
                                    QC2.Material.background: "#FFFFFF"
                                }
                            },
                            State {
                                when: index % 2 !== 0
                                PropertyChanges {
                                    target: _pane3
                                    QC2.Material.background: "#F6F8FC"
                                }
                            }
                        ]
                        ColumnLayout {
                            id: _col30
                            anchors.fill: parent
                            Item {
                                Layout.fillWidth: true
                                Layout.preferredHeight: _row23.implicitHeight
                                RowLayout{
                                    id: _row23
                                    anchors.fill: parent
                                    Felgo.AppText {
                                        text: qsTr("Customer")
                                        font.bold: true
                                        Layout.alignment: Qt.AlignLeft
                                    }
                                    Felgo.AppText {
                                        text: _delegate._invoice.Chus_Name
                                        Layout.alignment: Qt.AlignRight
                                    }
                                }
                            }
                            Rectangle {
                                Layout.fillWidth: true
                                Layout.preferredHeight: 1
                                color: QC2.Material.color(QC2.Material.Grey,QC2.Material.Shade300)
                            }
                            Item {
                                Layout.fillWidth: true
                                Layout.preferredHeight: _row24.implicitHeight
                                RowLayout{
                                    id: _row24
                                    anchors.fill: parent
                                    Felgo.AppText {
                                        text: qsTr("Invoice No.")
                                        font.bold: true
                                        Layout.alignment: Qt.AlignLeft
                                    }
                                    Felgo.AppText {
                                        text: _delegate._invoice.Invoice_No
                                        Layout.alignment: Qt.AlignRight
                                    }
                                }
                            }
                            Rectangle {
                                Layout.fillWidth: true
                                Layout.preferredHeight: 1
                                color: QC2.Material.color(QC2.Material.Grey,QC2.Material.Shade300)
                            }
                            Item {
                                Layout.fillWidth: true
                                Layout.preferredHeight: _row25.implicitHeight
                                RowLayout{
                                    id: _row25
                                    anchors.fill: parent
                                    Felgo.AppText {
                                        text: qsTr("Invoice Date")
                                        font.bold: true
                                        Layout.alignment: Qt.AlignLeft
                                    }
                                    Felgo.AppText {
                                        text: new Date(_delegate._invoice.Invoice_Date).toDateString()
                                        Layout.alignment: Qt.AlignRight
                                    }
                                }
                            }
                            Rectangle {
                                Layout.fillWidth: true
                                Layout.preferredHeight: 1
                                color: QC2.Material.color(QC2.Material.Grey,QC2.Material.Shade300)
                            }
                            Item {
                                Layout.fillWidth: true
                                Layout.preferredHeight: _row26.implicitHeight
                                RowLayout{
                                    id: _row26
                                    anchors.fill: parent
                                    Felgo.AppText {
                                        text: qsTr("Payment Type")
                                        font.bold: true
                                        Layout.alignment: Qt.AlignLeft
                                    }
                                    QC2.Label {
                                        id: _lbl2
                                        text: _delegate._invoice.Payment_Type
                                        Layout.alignment: Qt.AlignRight
                                        leftPadding: 12
                                        rightPadding: 12
                                        states: [
                                            State {
                                                name: "flexible"
                                                when: _delegate._invoice.Payment_Type.toLocaleLowerCase() === "flexible"
                                                PropertyChanges {
                                                    target: _lbl2
                                                    //QC2.Material.background: QC2.Material.color(QC2.Material.Teal,QC2.Material.Shade100)
                                                    QC2.Material.foreground: QC2.Material.color(QC2.Material.Teal,QC2.Material.Shade900)
                                                }
                                            },
                                            State {
                                                name: "fixed"
                                                when: _delegate._invoice.Payment_Type.toLocaleLowerCase() === "fixed"
                                                PropertyChanges {
                                                    target: _lbl2
                                                    //QC2.Material.background: QC2.Material.color(QC2.Material.Purple,QC2.Material.Shade100)
                                                    QC2.Material.foreground: QC2.Material.color(QC2.Material.Purple,QC2.Material.Shade900)
                                                }
                                            }
                                        ]
                                        background: Rectangle {
                                            color: _lbl2.state === "flexible" ? QC2.Material.color(QC2.Material.Teal,QC2.Material.Shade100) : QC2.Material.color(QC2.Material.Purple,QC2.Material.Shade100)
                                            radius: 10
                                        }
                                    }
                                }
                            }
                            Rectangle {
                                Layout.fillWidth: true
                                Layout.preferredHeight: 1
                                color: QC2.Material.color(QC2.Material.Grey,QC2.Material.Shade300)
                            }
                            Item {
                                id: _item6
                                Layout.fillWidth: true
                                Layout.preferredHeight: _row27.implicitHeight
                                function formatNumberWithCommas(value) {
                                        var numberString = value.toString();
                                        return numberString.replace(/\B(?=(\d{3})+(?!\d))/g, ",");
                                }
                                RowLayout{
                                    id: _row27
                                    anchors.fill: parent
                                    Felgo.AppText {
                                        text: qsTr("Total Amount")
                                        font.bold: true
                                        Layout.alignment: Qt.AlignLeft
                                    }
                                    Felgo.AppText {
                                        id: _text2
                                        readonly property string _amount: _delegate._invoice.Total.toString()
                                        readonly property string _currencyCode: _delegate._invoice.Currency_Code
                                        text: qsTr("%1 %2").arg(_text2._amount.replace(/\B(?=(\d{3})+(?!\d))/g,",")).arg(_text2._currencyCode)
                                        Layout.alignment: Qt.AlignRight
                                    }
                                }
                            }
                            Rectangle {
                                Layout.fillWidth: true
                                Layout.preferredHeight: 1
                                color: QC2.Material.color(QC2.Material.Grey,QC2.Material.Shade300)
                            }
                            Item {
                                Layout.fillWidth: true
                                Layout.preferredHeight: _row28.implicitHeight
                                RowLayout{
                                    id: _row28
                                    anchors.fill: parent
                                    Felgo.AppText {
                                        text: qsTr("Control No.")
                                        font.bold: true
                                        Layout.alignment: Qt.AlignLeft
                                    }
                                    Felgo.AppText {
                                        text: _delegate._invoice.Control_No
                                        Layout.alignment: Qt.AlignRight
                                    }
                                }
                            }
                            Rectangle {
                                Layout.fillWidth: true
                                Layout.preferredHeight: 1
                                color: QC2.Material.color(QC2.Material.Grey,QC2.Material.Shade300)
                            }
                            Item {
                                Layout.fillWidth: true
                                Layout.preferredHeight: _row29.implicitHeight
                                RowLayout{
                                    id: _row29
                                    anchors.fill: parent
                                    Felgo.AppText {
                                        text: qsTr("Action(s)")
                                        font.bold: true
                                        Layout.alignment: Qt.AlignLeft
                                    }
                                    Item {
                                        Layout.alignment: Qt.AlignRight
                                        Layout.fillWidth: true
                                        Layout.preferredHeight: _row19.implicitHeight
                                        RowLayout {
                                            id: _row19
                                            anchors.fill: parent
                                            layoutDirection: Qt.RightToLeft
                                            Felgo.IconButton {
                                                iconType: Felgo.IconType.download
                                            }
                                            Felgo.IconButton {
                                                iconType: Felgo.IconType.eye
                                                color: QC2.Material.color(QC2.Material.Yellow,QC2.Material.Shade500)
                                            }
                                            Felgo.IconButton {
                                                iconType: Felgo.IconType.close
                                                color: QC2.Material.color(QC2.Material.Red,QC2.Material.Shade500)
                                            }
                                            Felgo.IconButton {
                                                iconType: Felgo.IconType.bus
                                                color: QC2.Material.color(QC2.Material.Orange,QC2.Material.Shade500)
                                            }
                                            Felgo.IconButton {
                                                iconType: Felgo.IconType.arrowsalt
                                                color: QC2.Material.color(QC2.Material.Purple,QC2.Material.Shade500)
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
    }
    Component.onCompleted: {
        Felgo.HttpNetworkActivityIndicator.activationDelay = 0;
        let res = Req.requestGeneratedInvoiceDetails(Felgo,_generatedInvoicePage._userProfile,_generatedInvoicePage.page,_generatedInvoicePage.limit);
        res.then(function (res) {
            let [signedDetails] = res;
            _jsonListModel.source = signedDetails.response
        });
    }
}
