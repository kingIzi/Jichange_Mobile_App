import QtQuick
import QtQuick.Layouts
import QtQuick.Controls.Material as QC2
import Felgo as Felgo
import "../scripts/utilities.js" as Utils

Flickable {
    id: _flickable
    implicitHeight: expand ? 200 : 50
    contentHeight: _pane.implicitHeight
    boundsBehavior: Flickable.OvershootBounds
    function toggleExpand() {
        _flickable.expand = !_flickable.expand
    }

    property bool expand: false
    property date selectedMonthYear: new Date()
    readonly property var months: [
        qsTr("Jan"),
        qsTr("Feb"),
        qsTr("Mar"),
        qsTr("Apr"),
        qsTr("May"),
        qsTr("Jun"),
        qsTr("Jul"),
        qsTr("Aug"),
        qsTr("Sep"),
        qsTr("Oct"),
        qsTr("Nov"),
        qsTr("Dec")
    ]
    property var settingsModel: Utils.yearsDatePickerList(new Date().getFullYear(),2100)

    QC2.Pane {
        id: _pane
        anchors.fill: parent

        Column {
            anchors.right: parent.right
            anchors.left: parent.left
            anchors.verticalCenter: parent.verticalCenter
            spacing: 4
            Felgo.AppText {
                id: _selectedDateText
                readonly property string _month: Utils.switchMonth(_flickable.selectedMonthYear.getMonth())
                readonly property string _year: _flickable.selectedMonthYear.getFullYear().toString()
                horizontalAlignment: Qt.AlignHCenter
                text: qsTr("%1, %2").arg(_month).arg(_year)
                width: parent.width
                Felgo.AppIcon {
                    iconType: _flickable.expand ? Felgo.IconType.chevronup : Felgo.IconType.chevrondown
                    size: 11
                    anchors.right: parent.right
                    anchors.verticalCenter: parent.verticalCenter
                }
                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        toggleExpand()
                    }
                }
            }

            populate: Transition {
                NumberAnimation {
                    properties: "x,y"
                    duration: 300
                }

            }

            Repeater {
                id: _rept
                model: _flickable.expand ? settingsModel : []
                visible: false
                delegate: Column {
                    id: _colDelegate
                    readonly property int _yearModel: modelData.title
                    property bool showList: false
                    readonly property alias _paneSettingsList: paneSettingsList
                    anchors.left: parent.left
                    anchors.right: parent.right
                    QC2.ItemDelegate {
                        id: _yearDelegate
                        anchors.left: parent.left
                        anchors.right: parent.right
                        text: modelData.title.toString()
                        onClicked: {
                            for (let i = 0; i < _rept.count; i++) {
                                if (i === index && _rept.itemAt(index)._paneSettingsList.shown) {
                                    _rept.itemAt(index)._paneSettingsList.shown = false
                                }
                                else if (i === index && !_rept.itemAt(index)._paneSettingsList.shown) {
                                    _rept.itemAt(index)._paneSettingsList.shown = true
                                }
                                else {
                                    _rept.itemAt(i)._paneSettingsList.shown = false
                                }
                            }
                        }

                        Binding {
                            target: _yearDelegate.background
                            property: "color"
                            value: "#eeeeee"
                        }
                    }
                    QC2.Pane {
                        id: paneSettingsList
                        property bool shown: false
                        visible: height > 0
                        height: shown ? implicitHeight : 0
                        Behavior on height {
                            NumberAnimation {
                                easing.type: Easing.InOutQuad
                            }
                        }
                        clip: true
                        QC2.Material.background: "transparent"
                        padding: 0
                        anchors.left: parent.left
                        anchors.right: parent.right
                        contentItem: GridLayout {
                            anchors.fill: parent
                            columns: 4
                            Repeater {
                                id: listSettings1
                                //model: modelData.settings
                                model: _flickable.months
                                delegate: QC2.ItemDelegate {
                                    id: itemDelegateSettings1
                                    text: modelData
                                    width: parent.width
                                    readonly property date _today: new Date()
                                    QC2.Material.foreground: Qt.color("#000000")
                                    state: "Default"
                                    onClicked: {
                                        _flickable.selectedMonthYear = new Date(_colDelegate._yearModel,index)
                                        toggleExpand()
                                    }
                                    Binding {
                                        target: itemDelegateSettings1.background
                                        property: "color"
                                        value: itemDelegateSettings1.state === "Selected" ? Qt.color("#8196FE") : "transparent"
                                    }
                                    states: [
                                        State {
                                            name: "Selected"
                                            when: _colDelegate._yearModel === _flickable.selectedMonthYear.getFullYear() && index === _flickable.selectedMonthYear.getMonth()
                                            PropertyChanges {
                                                target: itemDelegateSettings1
                                                QC2.Material.foreground: Qt.color("#fff")
                                            }
                                        }
                                    ]
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    QC2.ScrollIndicator.vertical: QC2.ScrollIndicator { }
}

