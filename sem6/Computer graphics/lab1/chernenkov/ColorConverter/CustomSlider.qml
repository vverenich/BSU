import QtQuick 2.4
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12

RowLayout {
    id: customSlider

    property alias slider: slider
    property alias label: label
    property color textColor: "#ffffff"
    property int textPixelSize: 17

    implicitHeight: 30
    implicitWidth: 150

    Slider {
        id: slider

        from: 0
        to: 255
        stepSize: 1
        Layout.fillWidth: true
    }

    Label {
        id: label

        color: textColor
        text: slider.value
        font.pixelSize: textPixelSize
        Layout.fillWidth: true
        Layout.maximumWidth: 20
    }
}
