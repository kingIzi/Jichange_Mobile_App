import QtQuick
import QtQuick.Layouts
import Felgo as Felgo

ColumnLayout {
  id: root
  //anchors { left: parent.left; right: parent.right }
  property real secondaryTextSize: sp(12)
  property bool isInputCorrect: textInput.acceptableInput && !hasError && textInput.text.length > 0
  property bool hasError: false
  property bool isRequired: false
  property string errorMessage: qsTr("Error")

  property alias label: label.text
  property alias textField: textInput
  property alias placeholderText: textInput.placeholderText
  property alias validator: textInput.validator

  QtObject {
    id: internal
    // we only display the error message when textfield is not in focus
    property bool displayError: root.hasError && !textInput.activeFocus
    readonly property color errorColor: "red"
    readonly property real borderWidth: dp(1)
  }
  Item {
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
    text: root.errorMessage
    color: internal.errorColor
    font.pixelSize: secondaryTextSize
    opacity: internal.displayError ? 1.0 : 0.0
    Layout.fillWidth: true

    // we display a short fade animation when the error message changes state
    Behavior on opacity { NumberAnimation { } }
  }
}
