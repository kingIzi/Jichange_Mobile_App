import QtQuick
import QtQuick.Layouts
import QtQml
import QtQuick.Controls.Material as QC2
import Felgo as Felgo

ColumnLayout {
  id: _datePickerRoot
  //anchors { left: parent.left; right: parent.right }
  signal accepted(var date)
  property real secondaryTextSize: sp(12)
  property bool isInputCorrect: textInput.acceptableInput && !hasError && textInput.text.length > 0
  property bool hasError: false
  property bool isRequired: false
  property string errorMessage: qsTr("Error")

  property alias label: label.text
  property alias textField: textInput
  readonly property alias placeholderText: textInput.placeholderText
  property alias validator: textInput.validator

  QtObject {
    id: internal
    // we only display the error message when textfield is not in focus
    property bool displayError: _datePickerRoot.hasError && !textInput.activeFocus
    readonly property color errorColor: "red"
    readonly property real borderWidth: dp(1)
    readonly property FontLoader _fontBoldLoader: FontLoader {
        source: "../../assets/fonts/Inter-ExtraBold.ttf"
    }
    readonly property FontLoader _fontRegularLoader: FontLoader {
        source: "../../assets/fonts/Inter-Regular.ttf"
    }
  }

  Item {
      id: _fieldItem
      Layout.fillWidth: true
      Layout.preferredHeight: _row15.implicitHeight
      RowLayout{
          id: _row15
          //anchors.fill: parent
          anchors.left: parent.left
          anchors.top: parent.top
          anchors.bottom: parent.bottom
          Felgo.AppText {
            id: label
            font.bold: true
            Layout.fillWidth: true
          }
          Felgo.AppText {
            font.bold: true
            font.pixelSize: sp(12)
            Layout.fillWidth: true
            text: "*"
            color: "red"
            visible: isRequired
          }
      }
  }

  Felgo.AppTextField {
    id: textInput
    //anchors { left: parent.left; right: parent.right }
    Layout.fillWidth: true
    borderWidth: internal.borderWidth
    font.pixelSize: sp(14)
    placeholderText: qsTr("dd/MM/yyyy")
    validator: RegularExpressionValidator {
        regularExpression: /^(0[1-9]|[12][0-9]|3[01])\/(0[1-9]|1[0-2])\/(?!0000)\d{4}$/
    }

    Felgo.IconButton {
        id: _calendarBtn
        enabled: true
        iconType: Felgo.IconType.calendar
        anchors.right: parent.right
        anchors.verticalCenter: parent.verticalCenter
        onClicked: {
            _dateLoader.visible = true
            Felgo.NativeUtils.displayDatePicker()
        }
    }
    Loader {
        id: _dateLoader
        active: visible
        visible: false
        sourceComponent: Item {
            Connections {
                target: Felgo.NativeUtils
                function onDatePickerFinished(isAccepted,date) {
                    if (isAccepted) {
                        _datePickerRoot.textField.text = date.toLocaleDateString(Qt.locale(),"dd/MM/yyyy")
                        accepted(date)
                        _dateLoader.visible = false
                    }
                }
            }
        }
    }

//    QC2.Popup {
//        id: _datePicker
//        //anchors.right: parent.right
//        y: (-_calendarBtn.y * 3.3)
//        //x: (-_calendarBtn.x)
//        width: parent.width
//        height: _col7.implicitHeight * 1.1
//        z: 50
//        clip: true
//        onAboutToHide: {
//            _datePickerRoot.textField.text = _picker.selectedMonthYear.toLocaleDateString(Qt.locale(),"dd/MM/yyyy")
//            //_datePickerRoot.textField.text = _picker.selectedMonthYear.toLocaleDateString()
//        }

//        //color: "red"
//        contentItem: ColumnLayout {
//            id: _col7
//            anchors.fill: parent
//            anchors.margins: 2
//            DatePickerExpandingSections {
//                id: _picker
//                Layout.fillWidth: true
//                Layout.preferredHeight: implicitHeight
//            }
//            Item {
//                visible: !_picker.expand
//                Layout.fillWidth: true
//                Layout.preferredHeight: _col8.implicitHeight
//                ColumnLayout{
//                    id: _col8
//                    anchors.fill: parent
//                    QC2.DayOfWeekRow {
//                        Layout.fillWidth: true
//                        locale: Qt.locale("en_US")
//                    }
//                    QC2.MonthGrid {
//                        id: grid
//                        month: _picker.selectedMonthYear.getMonth()
//                        year: _picker.selectedMonthYear.getFullYear()
//                        locale: Qt.locale("en_US")
//                        Layout.fillWidth: true
//                        delegate: Rectangle {
//                            id: _rect
//                            implicitHeight: 30
//                            implicitWidth: 20
//                            border.color: Felgo.Theme.colors.dividerColor
//                            border.width: 1
//                            color: "transparent"
//                            required property var model
//                            opacity: _rect.model.month === grid.month ? 1 : 0
//                            Felgo.AppText {
//                                id: _dateText
//                                horizontalAlignment: Felgo.AppText.AlignHCenter
//                                verticalAlignment: Felgo.AppText.AlignVCenter
//                                text: _rect.model.day
//                                font.family: internal._fontRegularLoader.name
//                                anchors.fill: parent
//                                states: [
//                                    State {
//                                        //when: _rect.model.today
//                                        when: _picker.selectedMonthYear === new Date(model.year,model.month,model.date)
//                                        PropertyChanges {
//                                            target: _rect
//                                            color: Qt.color("#8196FE")
//                                        }
//                                        PropertyChanges {
//                                            target: _dateText
//                                            color: Qt.color("#ffffff")
//                                        }
//                                    },
//                                    State {
//                                        when: _mouse3.pressed
//                                        PropertyChanges {
//                                            target: _dateText
//                                            color: Qt.color("#ffffff")
//                                        }
//                                        PropertyChanges {
//                                            target: _rect
//                                            color: Qt.color("#8196FE")
//                                        }
//                                    }
//                                ]
//                                MouseArea{
//                                    id: _mouse3
//                                    anchors.fill: parent
//                                    onClicked: {
//                                        //_picker.selectedMonthYear = new Date(model.year,model.month,model.date)
//                                        _picker.selectedMonthYear.setDate(model.date)
//                                        console.log(_picker.selectedMonthYear.toLocaleDateString(Qt.locale(),"dd/MM/yyyy"))
//                                        //_datePicker.close()
//                                    }
//                                }
//                            }
//                        }
//                    }
//                }
//            }
//        }

//    }

    // here we change borderColor depending on the current textinput state
    states: [
      State {
        when: internal.displayError
        PropertyChanges {
          target: textInput
          borderColor: internal.errorColor
        }
      },
      State {
        when: textInput.activeFocus
        PropertyChanges {
          target: textInput
          borderColor: Felgo.Theme.colors.tintColor
        }
      },
      State {
        PropertyChanges {
          target: textInput
          borderColor: Felgo.Theme.colors.dividerColor
        }
      }
    ]

    // display a nice color transition when changing borderColor
    Behavior on borderColor { ColorAnimation { } }
  }

  Felgo.AppText {
    id: textError
    text: _datePickerRoot.errorMessage
    color: internal.errorColor
    font.pixelSize: secondaryTextSize
    opacity: internal.displayError ? 1.0 : 0.0
    Layout.fillWidth: true

    // we display a short fade animation when the error message changes state
    Behavior on opacity { NumberAnimation { } }
  }
}
