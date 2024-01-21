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
    color: view.rectangleColor


    Material.theme: Material.Dark
    Material.accent: Material.Blue

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
        y: 141
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


    GroupBox {
        id: groupBoxRGB
        x: 650
        y: 141
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
        id: groupBoxCMYK
        x: 574
        y: 409
        width: 196
        height: 313
        anchors.right: parent.right
        anchors.rightMargin: 30
        title: qsTr("CMYK")
        GridLayout {
            id: gridLayoutCMYK
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            Label {
                id: labelTextFieldCyan

                color: textColor
                text: qsTr("Cyan")
                font.pixelSize: textPixelSize
            }

            TextField {
                id: textFieldCyan

                property int realMaxValue: 100

                text: view.textFieldCValue
                color: textColor
                font.pixelSize: textPixelSize
                Layout.fillHeight: true
                validator: IntValidator {
                    id: intValidatorFrom3
                    bottom: 0
                    top: 999
                }
                onEditingFinished: {
                    if (Number(textFieldCyan.text) > realMaxValue) {
                        textFieldCyan.text = realMaxValue
                    }

                    view.setCMYK(Number(textFieldCyan.text), Number(textFieldMagenta.text), Number(textFieldYellow.text), Number(textFieldBlackKey.text))
                }
                Layout.preferredWidth: 53
                Layout.preferredHeight: 40
                placeholderText: qsTr("0")
            }

            Label {
                id: labelCyanUnit

                color: textColor
                text: qsTr("%")
                font.pixelSize: textPixelSize
            }

            Label {
                id: labelTextFieldMagenta
                color: textColor
                text: qsTr("Magenta")
                font.pixelSize: textPixelSize
            }

            TextField {
                id: textFieldMagenta

                property int realMaxValue: 100

                text: view.textFieldMValue
                color: textColor
                font.pixelSize: textPixelSize
                Layout.fillHeight: true
                validator: IntValidator {
                    id: intValidatorFrom4
                    bottom: 0
                    top: 999
                }
                onEditingFinished: {
                    if (Number(textFieldMagenta.text) > realMaxValue) {
                        textFieldMagenta.text = realMaxValue
                    }

                    view.setCMYK(Number(textFieldCyan.text), Number(textFieldMagenta.text), Number(textFieldYellow.text), Number(textFieldBlackKey.text))
                }
                Layout.preferredWidth: 53
                Layout.preferredHeight: 40
                placeholderText: qsTr("0")
            }

            Label {
                id: labelMagentaUnit

                color: textColor
                text: qsTr("%")
                font.pixelSize: textPixelSize
            }

            Label {
                id: labelTextFieldYellow
                color: textColor
                text: qsTr("Yellow")
                font.pixelSize: textPixelSize
            }

            TextField {
                id: textFieldYellow

                property int realMaxValue: 100

                text: view.textFieldYValue
                color: textColor
                font.pixelSize: textPixelSize
                Layout.fillHeight: true
                validator: IntValidator {
                    id: intValidatorFrom5
                    bottom: 0
                    top: 999
                }
                onEditingFinished: {
                    if (Number(textFieldYellow.text) > realMaxValue) {
                        textFieldYellow.text = realMaxValue
                    }

                    view.setCMYK(Number(textFieldCyan.text), Number(textFieldMagenta.text), Number(textFieldYellow.text), Number(textFieldBlackKey.text))
                }
                Layout.preferredWidth: 53
                Layout.preferredHeight: 40
                placeholderText: qsTr("0")
            }

            Label {
                id: labelYellowUnit

                color: textColor
                text: qsTr("%")
                font.pixelSize: textPixelSize
            }


            Label {
                id: labelTextFieldBlackKey
                color: textColor
                text: qsTr("Black Key")
                font.pixelSize: textPixelSize
            }

            TextField {
                id: textFieldBlackKey

                property int realMaxValue: 100

                text: view.textFieldKValue
                color: textColor
                font.pixelSize: textPixelSize
                Layout.fillHeight: true
                validator: IntValidator {
                    id: intValidatorFrom6
                    bottom: 0
                    top: 999
                }
                onEditingFinished: {
                    if (Number(textFieldBlackKey.text) > realMaxValue) {
                        textFieldBlackKey.text = realMaxValue
                    }

                    view.setCMYK(Number(textFieldCyan.text), Number(textFieldMagenta.text), Number(textFieldYellow.text), Number(textFieldBlackKey.text))
                }
                Layout.preferredWidth: 53
                Layout.preferredHeight: 40
                placeholderText: qsTr("0")
            }

            Label {
                id: labelBlackKeyUnit

                color: textColor
                text: qsTr("%")
                font.pixelSize: textPixelSize
            }

            rows: 4
            columns: 3
        }
    }


    GroupBox {
        id: groupBoxHSL
        x: 574
        y: 759
        width: 196
        height: 210
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 30
        anchors.rightMargin: 30
        title: qsTr("HSL")
        GridLayout {
            id: gridLayoutHSL
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
                    id: intValidatorFrom10
                    bottom: 0
                    top: 999
                }
                onEditingFinished: {
                    if (Number(textFieldHue.text) > realMaxValue) {
                        textFieldHue.text = realMaxValue
                    }

                    view.setHSL(Number(textFieldHue.text), Number(textFieldSaturation.text), Number(textFieldLightness.text))
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
                    id: intValidatorFrom11
                    bottom: 0
                    top: 999
                }
                onEditingFinished: {
                    if (Number(textFieldSaturation.text) > realMaxValue) {
                        textFieldSaturation.text = realMaxValue
                    }

                    view.setHSL(Number(textFieldHue.text), Number(textFieldSaturation.text), Number(textFieldLightness.text))
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
                id: labelTextFieldLightness
                color: textColor
                text: qsTr("Lightness")
                font.pixelSize: textPixelSize
            }

            TextField {
                id: textFieldLightness

                property int realMaxValue: 100

                text: view.textFieldLightnessValue
                color: textColor
                font.pixelSize: textPixelSize
                Layout.fillHeight: true
                validator: IntValidator {
                    id: intValidatorFrom12
                    bottom: 0
                    top: 999
                }
                onEditingFinished: {
                    if (Number(textFieldLightness.text) > realMaxValue) {
                        textFieldLightness.text = realMaxValue
                    }


                    view.setHSL(Number(textFieldHue.text), Number(textFieldSaturation.text), Number(textFieldLightness.text))
                }
                Layout.preferredWidth: 53
                Layout.preferredHeight: 40
                placeholderText: qsTr("0")
            }

            Label {
                id: labelLightnessUnit

                color: textColor
                text: qsTr("%")
                font.pixelSize: textPixelSize
            }


            rows: 3
            columns: 3
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
        id: groupBoxSlidersCMYK
        y: 409
        height: 313
        anchors.left: parent.left
        anchors.right: groupBoxCMYK.left
        anchors.rightMargin: 30
        anchors.leftMargin: 30
        GridLayout {
            id: gridLayoutSlidersCMYK
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.topMargin: 0
            columns: 2
            Label {
                id: labelCyan
                color: applicationWindow.textColor
                text: qsTr("Cyan")
                font.pixelSize: applicationWindow.textPixelSize
            }

            CustomSlider {
                id: customSliderCyan

                slider.value: view.textFieldCValue
                slider.from: 0
                slider.to: 100
                textColor: applicationWindow.textColor
                slider.onValueChanged: {
                    view.setCMYK(customSliderCyan.slider.value, customSliderMagenta.slider.value, customSliderYellow.slider.value, customSliderBlackKey.slider.value)
                }
                textPixelSize: applicationWindow.textPixelSize
            }

            Label {
                id: labelMagenta
                color: applicationWindow.textColor
                text: qsTr("Magenta")
                font.pixelSize: applicationWindow.textPixelSize
            }

            CustomSlider {
                id: customSliderMagenta

                slider.value: view.textFieldMValue
                slider.from: 0
                slider.to: 100
                textColor: applicationWindow.textColor
                slider.onValueChanged: {
                    view.setCMYK(customSliderCyan.slider.value, customSliderMagenta.slider.value, customSliderYellow.slider.value, customSliderBlackKey.slider.value)

                }
                textPixelSize: applicationWindow.textPixelSize
            }

            Label {
                id: labelYellow
                color: applicationWindow.textColor
                text: qsTr("Yellow")
                font.pixelSize: applicationWindow.textPixelSize
            }

            CustomSlider {
                id: customSliderYellow

                slider.value: view.textFieldYValue
                slider.from: 0
                slider.to: 100
                textColor: applicationWindow.textColor
                slider.onValueChanged: {
                    view.setCMYK(customSliderCyan.slider.value, customSliderMagenta.slider.value, customSliderYellow.slider.value, customSliderBlackKey.slider.value)

                }
                textPixelSize: applicationWindow.textPixelSize
            }

            Label {
                id: labelBlackKey
                color: applicationWindow.textColor
                text: qsTr("Black Key")
                font.pixelSize: applicationWindow.textPixelSize
            }

            CustomSlider {
                id: customSliderBlackKey

                slider.value: view.textFieldKValue
                slider.from: 0
                slider.to: 100
                textColor: applicationWindow.textColor
                slider.onValueChanged: {
                    view.setCMYK(customSliderCyan.slider.value, customSliderMagenta.slider.value, customSliderYellow.slider.value, customSliderBlackKey.slider.value)
                }
                textPixelSize: applicationWindow.textPixelSize
            }
            anchors.leftMargin: 0
            rows: 4
        }
        title: qsTr("Color sliders CMYK")
    }
    GroupBox {
        id: groupBoxSlidersHSL
        y: 758
        width: 514
        height: 211
        anchors.left: parent.left
        anchors.right: groupBoxHSL.left
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 30
        anchors.rightMargin: 30
        anchors.leftMargin: 30
        GridLayout {
            id: gridLayoutSlidersHSL
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
                    view.setHSL(customSliderHue.slider.value, customSliderSaturation.slider.value, customSliderLightness.slider.value)
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

                    view.setHSL(customSliderHue.slider.value, customSliderSaturation.slider.value, customSliderLightness.slider.value)
                }
                textPixelSize: applicationWindow.textPixelSize
            }

            Label {
                id: labelValue
                color: applicationWindow.textColor
                text: qsTr("Lightness")
                font.pixelSize: applicationWindow.textPixelSize
            }

            CustomSlider {
                id: customSliderLightness

                slider.value: view.textFieldLightnessValue
                slider.from: 0
                slider.to: 100
                textColor: applicationWindow.textColor
                slider.onValueChanged: {

                    view.setHSL(customSliderHue.slider.value, customSliderSaturation.slider.value, customSliderLightness.slider.value)
                }
                textPixelSize: applicationWindow.textPixelSize
            }
            anchors.leftMargin: 0
            rows: 3
        }
        title: qsTr("Color sliders HSL")
    }

}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.75}D{i:3}D{i:11}D{i:48}D{i:49}D{i:57}
}
##^##*/
