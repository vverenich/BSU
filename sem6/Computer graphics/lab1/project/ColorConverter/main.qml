import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Layouts 1.12
import QtQuick.Dialogs 1.0

import View 1.0

Window {
    id: applicationWindow

    property int textPixelSize: 17
    property color textColor: "#ffffff"

    width: 800
    height: 980
    minimumWidth: 800
    minimumHeight: 980
    x: 50
    y: 50
    visible: true
    title: qsTr("Color converter")
    color: "#333333"


    Material.theme: Material.Dark
    Material.accent: Material.Orange

    View {
        id: view
    }

    ColorDialog {
        id: colorDialog

        title: "Please choose a color"
        visible: false
        onAccepted: {
            view.setRectangleColor(colorDialog.color)
            colorDialog.visible = false
        }
        onRejected: {
            colorDialog.visible = false
        }
    }

    GroupBox {
        id: groupBoxSlidersRGB
        y: 281
        height: 211
        anchors.left: parent.left
        anchors.right: groupBoxRGB.left
        anchors.leftMargin: 30
        anchors.rightMargin: 30
        title: qsTr("Color sliders RGB")

        GridLayout {
            id: gridLayoutColorSliders
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.leftMargin: 0
            anchors.topMargin: 0
            rows: 3
            columns: 2

            Label {
                id: labelRed

                text: qsTr("Red")
                color: applicationWindow.textColor
                font.pixelSize: applicationWindow.textPixelSize
            }

            CustomSlider {
                id: customSliderRed

                slider.value: Number(view.sliderRedValue)
                textColor: applicationWindow.textColor
                textPixelSize: applicationWindow.textPixelSize

                slider.onValueChanged: {
                    view.setSliderRedValue(slider.value)
                }

            }

            Label {
                id: labelGreen

                text: qsTr("Green")
                color: applicationWindow.textColor
                font.pixelSize: applicationWindow.textPixelSize
            }

            CustomSlider {
                id: customSliderGreen

                slider.value: Number(view.sliderGreenValue)
                textColor: applicationWindow.textColor
                textPixelSize: applicationWindow.textPixelSize

                slider.onValueChanged: {
                    view.setSliderGreenValue(slider.value)
                }
            }

            Label {
                id: labelBlue

                text: qsTr("Blue")
                color: applicationWindow.textColor
                font.pixelSize: applicationWindow.textPixelSize
            }

            CustomSlider {
                id: customSliderBlue

                slider.value: Number(view.sliderBlueValue)
                textColor: applicationWindow.textColor
                textPixelSize: applicationWindow.textPixelSize

                slider.onValueChanged: {
                    view.setSliderBlueValue(slider.value)
                }
            }
        }
    }

    Rectangle {
        id: rectangleResult

        width: 200
        height: 200
        color: view.rectangleColor
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.leftMargin: 30
        anchors.topMargin: 30
    }

    GroupBox {
        id: groupBoxRGB
        x: 578
        y: 281
        width: 120
        height: 211
        anchors.right: parent.right
        anchors.rightMargin: 30
        title: qsTr("RGB")

        GridLayout {
            id: gridLayoutRGB
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            rows: 3
            columns: 2

            Label {
                id: labelTextFieldRed

                text: qsTr("Red")
                font.pixelSize: textPixelSize
                color: textColor
            }

            TextField {
                id: textFieldRed

                property int realMaxValue: 255

                text: view.textFieldRedValue
                placeholderText: qsTr("0")
                font.pixelSize: textPixelSize
                Layout.fillHeight: true
                Layout.preferredHeight: 40
                Layout.preferredWidth: 53
                color: textColor

                validator: IntValidator {
                    id: intValidatorFrom

                    bottom: 0
                    top: 999
                }

                onEditingFinished: {
                    if (Number(textFieldRed.text) > realMaxValue) {
                        textFieldRed.text = realMaxValue
                    }

                    view.setTextFieldRedValue(Number(textFieldRed.text))
                }
            }

            Label {
                id: labelTextFieldGreen
                color: textColor
                text: qsTr("Green")
                font.pixelSize: textPixelSize
            }

            TextField {
                id: textFieldGreen

                text: view.textFieldGreenValue
                color: textColor
                font.pixelSize: textPixelSize
                Layout.fillHeight: true
                Layout.fillWidth: true
                Layout.preferredHeight: 40
                Layout.preferredWidth: 53
                validator: IntValidator {
                    id: intValidatorFrom1
                    bottom: 0
                    top: 999
                }
                onEditingFinished: {
                    if (Number(textFieldGreen.text) > realMaxValue) {
                        textFieldGreen.text = realMaxValue
                    }

                    view.setTextFieldGreenValue(Number(textFieldGreen.text))
                }
                placeholderText: qsTr("0")
                property int realMaxValue: 255
            }

            Label {
                id: labelTextFieldBlue
                color: textColor
                text: qsTr("Blue")
                font.pixelSize: textPixelSize
            }

            TextField {
                id: textFieldBlue

                text: view.textFieldBlueValue
                color: textColor
                font.pixelSize: textPixelSize
                Layout.fillHeight: true
                Layout.preferredHeight: 40
                Layout.preferredWidth: 53
                validator: IntValidator {
                    id: intValidatorFrom2
                    bottom: 0
                    top: 999
                }
                onEditingFinished: {
                    if (Number(textFieldBlue.text) > realMaxValue) {
                        textFieldBlue.text = realMaxValue
                    }

                    view.setTextFieldBlueValue(Number(textFieldBlue.text))
                }
                placeholderText: qsTr("0")
                property int realMaxValue: 255
            }
        }
    }

    GroupBox {
        id: groupBoxHSV
        x: 578
        y: 512
        width: 196
        height: 210
        anchors.right: parent.right
        anchors.rightMargin: 30
        title: qsTr("HSV")
        GridLayout {
            id: gridLayoutHSV
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            Label {
                id: labelTextFieldHue
                color: textColor
                text: qsTr("Hue")
                font.pixelSize: textPixelSize
            }

            TextField {
                id: textFieldHue

                property int realMaxValue: 360

                text: view.textFieldHueValue
                color: textColor
                font.pixelSize: textPixelSize
                Layout.fillHeight: true
                validator: IntValidator {
                    id: intValidatorFrom3
                    bottom: 0
                    top: 999
                }
                onEditingFinished: {
                    if (Number(textFieldHue.text) > realMaxValue) {
                        textFieldHue.text = realMaxValue
                    }

                    view.setTextFieldHueValue(Number(textFieldHue.text), Number(textFieldSaturation.text), Number(textFieldValue.text))
                }
                Layout.preferredWidth: 53
                Layout.preferredHeight: 40
                placeholderText: qsTr("0")
            }

            Label {
                id: labelHueUnit

                color: textColor
                text: qsTr("°")
                font.pixelSize: textPixelSize
            }

            Label {
                id: labelTextFieldSaturation
                color: textColor
                text: qsTr("Saturation")
                font.pixelSize: textPixelSize
            }

            TextField {
                id: textFieldSaturation

                property int realMaxValue: 100

                text: view.textFieldSaturationValue
                color: textColor
                font.pixelSize: textPixelSize
                Layout.fillHeight: true
                validator: IntValidator {
                    id: intValidatorFrom4
                    bottom: 0
                    top: 999
                }
                onEditingFinished: {
                    if (Number(textFieldSaturation.text) > realMaxValue) {
                        textFieldSaturation.text = realMaxValue
                    }

                    view.setTextFieldSaturationValue(Number(textFieldHue.text), Number(textFieldSaturation.text), Number(textFieldValue.text))
                }
                Layout.preferredWidth: 53
                Layout.preferredHeight: 40
                placeholderText: qsTr("0")
            }

            Label {
                id: labelSaturationUnit

                color: textColor
                text: qsTr("%")
                font.pixelSize: textPixelSize
            }

            Label {
                id: labelTextFieldValue
                color: textColor
                text: qsTr("Value")
                font.pixelSize: textPixelSize
            }

            TextField {
                id: textFieldValue

                property int realMaxValue: 100

                text: view.textFieldValueValue
                color: textColor
                font.pixelSize: textPixelSize
                Layout.fillHeight: true
                validator: IntValidator {
                    id: intValidatorFrom5
                    bottom: 0
                    top: 999
                }
                onEditingFinished: {
                    if (Number(textFieldValue.text) > realMaxValue) {
                        textFieldValue.text = realMaxValue
                    }

                    view.setTextFieldValueValue(Number(textFieldHue.text), Number(textFieldSaturation.text), Number(textFieldValue.text))
                }
                Layout.preferredWidth: 53
                Layout.preferredHeight: 40
                placeholderText: qsTr("0")
            }

            Label {
                id: labelValueUnit

                color: textColor
                text: qsTr("%")
                font.pixelSize: textPixelSize
            }

            rows: 3
            columns: 3
        }
    }

    GroupBox {
        id: groupBoxLAB
        x: 578
        y: 740
        width: 96
        height: 210
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 30
        anchors.rightMargin: 30
        title: qsTr("LAB")
        GridLayout {
            id: gridLayoutLAB
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            Label {
                id: labelTextFieldL
                color: textColor
                text: qsTr("L")
                font.pixelSize: textPixelSize
            }

            TextField {
                id: textFieldL

                text: view.textFieldLValue
                color: textColor
                font.pixelSize: textPixelSize
                validator: IntValidator {
                    id: intValidatorFrom6
                    bottom: 0
                    top: 999
                }
                onEditingFinished: {
                        if (Number(textFieldL.text) > realMaxValue) {
                            textFieldL.text = realMaxValue
                        }

                        view.setTextFieldLValue(Number(textFieldL.text), Number(textFieldA.text), Number(textFieldB.text))
                    }
                Layout.preferredWidth: 53
                Layout.preferredHeight: 40
                placeholderText: qsTr("0")
                property int realMaxValue: 100
            }

            Label {
                id: labelTextFieldA
                color: textColor
                text: qsTr("A")
                font.pixelSize: textPixelSize
            }

            TextField {
                id: textFieldA

                text: view.textFieldAValue
                color: textColor
                font.pixelSize: textPixelSize
                validator: IntValidator {
                    id: intValidatorFrom7
                    bottom: -128
                    top: 128
                }
                onEditingFinished: {
                    if (Number(textFieldA.text) > realMaxValue) {
                        textFieldA.text = realMaxValue
                    }

                    if (Number(textFieldA.text) < realMinValue) {
                        textFieldA.text = realMinValue
                    }

                    view.setTextFieldAValue(Number(textFieldL.text), Number(textFieldA.text), Number(textFieldB.text))
                }
                Layout.preferredWidth: 53
                Layout.preferredHeight: 40
                placeholderText: qsTr("0")
                property int realMaxValue: 128
                property int realMinValue: -128
            }

            Label {
                id: labelTextFieldB
                color: textColor
                text: qsTr("B")
                font.pixelSize: textPixelSize
            }

            TextField {
                id: textFieldB

                text: view.textFieldBValue
                color: textColor
                font.pixelSize: textPixelSize
                validator: IntValidator {
                    id: intValidatorFrom8
                    bottom: 0
                    top: 999
                }
                onEditingFinished: {
                    if (Number(textFieldB.text) > realMaxValue) {
                        textFieldB.text = realMaxValue
                    }

                    view.setTextFieldBValue(Number(textFieldL.text), Number(textFieldA.text), Number(textFieldB.text))
                }
                Layout.preferredWidth: 53
                Layout.preferredHeight: 40
                placeholderText: qsTr("0")
                property int realMaxValue: 255
            }
            rows: 3
            columns: 2
        }
    }

    Button {
        id: buttonPalette

        x: 466
        text: qsTr("Palette")
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.rightMargin: 30
        anchors.topMargin: 30

        onClicked: {
            colorDialog.visible = true
        }
    }

    GroupBox {
        id: groupBoxSlidersHSV
        y: 511
        height: 211
        anchors.left: parent.left
        anchors.right: groupBoxHSV.left
        anchors.rightMargin: 30
        anchors.leftMargin: 30
        GridLayout {
            id: gridLayoutSlidersHSV
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.topMargin: 0
            columns: 2
            Label {
                id: labelHue
                color: applicationWindow.textColor
                text: qsTr("Hue")
                font.pixelSize: applicationWindow.textPixelSize
            }

            CustomSlider {
                id: customSliderHue

                slider.value: view.textFieldHueValue
                slider.from: 0
                slider.to: 360
                textColor: applicationWindow.textColor
                slider.onValueChanged: {
                    view.setTextFieldHueValue(customSliderHue.slider.value, customSliderSaturation.slider.value, customSliderValue.slider.value)
                }
                textPixelSize: applicationWindow.textPixelSize
            }

            Label {
                id: labelSaturation
                color: applicationWindow.textColor
                text: qsTr("Saturation")
                font.pixelSize: applicationWindow.textPixelSize
            }

            CustomSlider {
                id: customSliderSaturation

                slider.value: view.textFieldSaturationValue
                slider.from: 0
                slider.to: 100
                textColor: applicationWindow.textColor
                slider.onValueChanged: {
                    view.setTextFieldSaturationValue(customSliderHue.slider.value, customSliderSaturation.slider.value, customSliderValue.slider.value)
                }
                textPixelSize: applicationWindow.textPixelSize
            }

            Label {
                id: labelValue
                color: applicationWindow.textColor
                text: qsTr("Value")
                font.pixelSize: applicationWindow.textPixelSize
            }

            CustomSlider {
                id: customSliderValue

                slider.value: view.textFieldValueValue
                slider.from: 0
                slider.to: 100
                textColor: applicationWindow.textColor
                slider.onValueChanged: {
                    view.setTextFieldValueValue(customSliderHue.slider.value, customSliderSaturation.slider.value, customSliderValue.slider.value)
                }
                textPixelSize: applicationWindow.textPixelSize
            }
            anchors.leftMargin: 0
            rows: 3
        }
        title: qsTr("Color sliders HSV")
    }

    GroupBox {
        id: groupBoxSlidersLAB
        y: 739
        height: 211
        anchors.left: parent.left
        anchors.right: groupBoxLAB.left
        anchors.bottom: parent.bottom
        anchors.rightMargin: 30
        anchors.bottomMargin: 30
        anchors.leftMargin: 30
        GridLayout {
            id: gridLayoutSlidersLAB
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.topMargin: 0
            columns: 2
            Label {
                id: labelL
                color: applicationWindow.textColor
                text: qsTr("L")
                font.pixelSize: applicationWindow.textPixelSize
            }

            CustomSlider {
                id: customSliderL

                slider.value: view.textFieldLValue
                slider.from: 0
                slider.to: 100
                textColor: applicationWindow.textColor
                slider.onValueChanged: {
                        view.setTextFieldLValue(customSliderL.slider.value, customSliderA.slider.value, customSliderB.slider.value)
                    }
                textPixelSize: applicationWindow.textPixelSize
            }

            Label {
                id: labelA
                color: applicationWindow.textColor
                text: qsTr("A")
                font.pixelSize: applicationWindow.textPixelSize
            }

            CustomSlider {
                id: customSliderA

                slider.value: view.textFieldAValue
                slider.from: -128
                slider.to: 128
                textColor: applicationWindow.textColor
                slider.onValueChanged: {
                        view.setTextFieldAValue(customSliderL.slider.value, customSliderA.slider.value, customSliderB.slider.value)
                    }
                textPixelSize: applicationWindow.textPixelSize
            }

            Label {
                id: labelBlue2

                color: applicationWindow.textColor
                text: qsTr("B")
                font.pixelSize: applicationWindow.textPixelSize
            }

            CustomSlider {
                id: customSliderB

                slider.value: view.textFieldBValue
                slider.from: 0
                slider.to: 255
                textColor: applicationWindow.textColor
                slider.onValueChanged: {
                        view.setTextFieldBValue(customSliderL.slider.value, customSliderA.slider.value, customSliderB.slider.value)
                    }
                textPixelSize: applicationWindow.textPixelSize
            }
            anchors.leftMargin: 0
            rows: 3
        }
        title: qsTr("Color sliders LAB")
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.75}D{i:3}D{i:11}D{i:48}D{i:49}D{i:57}
}
##^##*/
