import QtQuick
import QtQuick.Controls.Material as QC2
import QtQuick.Layouts
import Felgo as Felgo

ColumnLayout {
  id: _validatedComboBoxField
  //anchors { left: parent.left; right: parent.right }
  property real secondaryTextSize: sp(12)
  property bool isInputCorrect: _comboBox.acceptableInput && !hasError
  property bool hasError: false
  property bool isRequired: false
  property string errorMessage: qsTr("Error")
  property bool isEditable: false
  property alias label: label.text
  property alias comboxBox: _comboBox
  property alias validator: _comboBox.validator

  QtObject {
    id: internal
    // we only display the error message when textfield is not in focus
    property bool displayError: _validatedComboBoxField.hasError && !_comboBox.activeFocus
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
  CustomTextComboBox {
      id: _comboBox
      Layout.fillWidth: true
      font.pixelSize: sp(14)
      editable: _validatedComboBoxField.isEditable
      Binding {
          id: _binding
          target: _comboBox.background
          property: "border.color"
          value: Felgo.Theme.colors.dividerColor
      }
      states: [
        State {
          when: internal.displayError
          PropertyChanges {
            target: _binding
            value: internal.errorColor
          }
        },
        State {
          when: _comboBox.activeFocus
          PropertyChanges {
            target: _binding
            value: Felgo.Theme.colors.tintColor
          }
        },
        State {
          PropertyChanges {
            target: _binding
            value: Felgo.Theme.colors.dividerColor
          }
        }
      ]
  }
  Felgo.AppText {
    id: textError
    text: _validatedComboBoxField.errorMessage
    color: internal.errorColor
    font.pixelSize: secondaryTextSize
    opacity: internal.displayError ? 1.0 : 0.0
    Layout.fillWidth: true
    // we display a short fade animation when the error message changes state
    Behavior on opacity { NumberAnimation { } }
  }
}
