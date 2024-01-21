import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Dialogs 1.2
import QtQuick.Window 2.15
import QtQuick.Layouts 1.0
import Backend 1.0

Window {
    id: applicationWindow

    property color backgroundColor: "#333333"
    property color textColor: "#ffffff"

    width: 1000
    height: 480
    visible: true
    title: qsTr("Image info")
    color: backgroundColor

    Backend {
        id: backend
    }

    FileDialog {
        id: fileDialogFile

        title: "Please choose a file"
        folder: shortcuts.home
        selectMultiple: true

        onAccepted: {
            console.log(fileDialogFile.fileUrls)
            backend.getInfo(fileDialogFile.fileUrls)
        }
    }

    ScrollView {
        id: scrollView

        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: labelProperties.bottom
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        anchors.rightMargin: 10
        anchors.leftMargin: 10
        anchors.topMargin: 10

        Text {
            id: content

            text: backend.scrollViewText
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.leftMargin: 0
            anchors.bottomMargin: 0
            anchors.rightMargin: 0
            anchors.topMargin: 0
            color: textColor
        }
    }

    Button {
        id: buttonChooseFile

        text: qsTr("Choose file")
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.leftMargin: 10

        onClicked: {
            fileDialogFile.visible = true
        }
    }

    Label {
        id: labelProperties

        y: 64
        text: "pixel size:\t\tdot/meterX:\t\tdot/meterY:\t\tdepth:\t\tfile name: \n"
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.leftMargin: 10
        color: textColor
    }
}
