import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Layouts 1.0
import BackEnd 1.0

Window {
    id: mainWindow

    width: 1200
    height: 950
    minimumWidth: 1200
    minimumHeight: 950
    color: "#252525"
    visible: true
    title: qsTr("Search Engine")

    Material.theme: Material.Dark
    Material.accent: Material.Green

    property int textSize: 18
    property int textSizeHeader: 20
    property var tagsWindowComponent: Qt.createComponent("Tags.qml");
    property var tagsWindow: tagsWindowComponent.createObject(mainWindow)

    BackEnd {
        id: backEnd
    }

    GroupBox {
        id: groupBoxAddTextToDB
        x: 588
        width: 582
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 30
        anchors.rightMargin: 30
        anchors.topMargin: 30
        title: qsTr("Добавление документа")

        RowLayout {
            id: rowLayoutAddDoc
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.topMargin: 0
            anchors.rightMargin: 0
            anchors.leftMargin: 0


            TextField {
                id: textFieldAddText
                text: qsTr("")
                Layout.fillWidth: true
                Layout.preferredHeight: 40
                placeholderText: "Название документа"
            }
            Button {
                id: buttonAddDoc
                text: qsTr("Добавить")
                Layout.alignment: Qt.AlignRight | Qt.AlignVCenter

                onClicked: {
                    backEnd.addDocument(textFieldAddText.text)
                    textInformativeWordsPOD.text = backEnd.getWordsAndWeight()
                    textTaggedText.text = backEnd.getTaggedText()
                }
            }
        }

        GroupBox {
            id: groupBoxFormPOD
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: rowLayoutAddDoc.bottom
            anchors.bottom: parent.bottom
            anchors.topMargin: 0
            anchors.bottomMargin: 0
            anchors.rightMargin: 0
            anchors.leftMargin: 0
            title: qsTr("Формирование ПОД")

            ScrollView {
                id: scrollViewInformativeWordsPOD
                x: -24
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: labelInformativeWordsPOD.bottom
                anchors.bottom: labelTaggedText.top
                anchors.bottomMargin: 18
                clip: true
                Text {
                    id: textInformativeWordsPOD
                    color: "#ffffff"
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.top: parent.top
                    anchors.bottom: parent.bottom
                    clip: false
                    anchors.bottomMargin: 10
                    anchors.leftMargin: 0
                    anchors.topMargin: 10
                }
                anchors.leftMargin: 0
                anchors.rightMargin: 0
                anchors.topMargin: 0
                hoverEnabled: true
                activeFocusOnTab: false
            }

            Text {
                id: labelInformativeWordsPOD
                color: "#ffffff"
                text: qsTr("Канонизированнные информативные слова и их вес:")
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: parent.top
                font.pixelSize: 12
                anchors.topMargin: 0
            }

            ScrollView {
                id: scrollViewTaggedText
                x: -24
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: labelTaggedText.bottom
                anchors.bottom: parent.bottom
                clip: true
                Text {
                    id: textTaggedText
                    color: "#ffffff"
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.top: parent.top
                    anchors.bottom: parent.bottom
                    clip: false
                    anchors.bottomMargin: 10
                    anchors.leftMargin: 0
                    anchors.topMargin: 10
                }
                anchors.leftMargin: 0
                anchors.rightMargin: 0
                activeFocusOnTab: false
                hoverEnabled: true
            }

            Text {
                id: labelTaggedText
                color: "#ffffff"
                text: qsTr("Текст с разметкой:")
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: parent.top
                font.pixelSize: 12
                anchors.rightMargin: 0
                anchors.leftMargin: 0
                anchors.topMargin: 294
            }
        }
    }

    GroupBox {
        id: groupBoxSearch
        width: 556
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 30
        anchors.leftMargin: 30
        anchors.topMargin: 30
        title: qsTr("Поиск документа")

        RowLayout {
            id: rowLayoutSearch
            x: 456
            y: -158
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top
            TextField {
                id: textFieldAddSearch
                text: qsTr("")
                Layout.fillWidth: true
                Layout.preferredHeight: 40
                placeholderText: "Искать"
            }

            Button {
                id: buttonAddDoc1
                text: qsTr("Искать")
                Layout.alignment: Qt.AlignRight | Qt.AlignVCenter

                onClicked: {
                    backEnd.handleSearch(textFieldAddSearch.text)
                    textInformativeWordsPOZ.text = backEnd.getInformativeWordsPOZ()
                    textDocumnets.text = backEnd.getResults()
                }
            }
            anchors.leftMargin: 0
            anchors.rightMargin: 0
            anchors.topMargin: 0
        }

        GroupBox {
            id: groupBoxFormPOZ
            width: 200
            height: 226
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: rowLayoutSearch.bottom
            anchors.rightMargin: 0
            anchors.leftMargin: 0
            anchors.topMargin: 0
            title: qsTr("Формирование ПОЗ")

            ScrollView {
                id: scrollViewInformativeWordsPOZ
                x: -24

                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: labelInformativeWordsPOZ.bottom
                anchors.bottom: parent.bottom
                hoverEnabled: true
                activeFocusOnTab: false
                anchors.leftMargin: 0
                anchors.rightMargin: 0
                clip: true
                anchors.topMargin: 0

                Text {

                    id: textInformativeWordsPOZ

                    color: "#ffffff"
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.top: parent.top
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: -159
                    anchors.leftMargin: 0
                    anchors.topMargin: 0
                    clip: false
                }
            }

            Text {
                id: labelInformativeWordsPOZ
                text: qsTr("Канонизированнные информативные слова:")
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: parent.top
                font.pixelSize: 12
                anchors.topMargin: 0
                color: "#ffffff"
            }
        }

        GroupBox {
            id: groupBoxSearchResults
            y: 322
            width: 200
            height: 544
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            title: qsTr("Результаты поиска")
            anchors.leftMargin: 0
            anchors.rightMargin: 0

            ScrollView {
                id: scrollViewDocuments
                x: -24
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: labelDocuments.bottom
                anchors.bottom: parent.bottom
                hoverEnabled: true
                clip: true
                Text {
                    id: textDocumnets
                    color: "#ffffff"
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.top: parent.top
                    anchors.bottom: parent.bottom
                    clip: false
                    anchors.bottomMargin: 10
                    anchors.topMargin: 10
                    anchors.leftMargin: 0
                }
                anchors.bottomMargin: 0
                anchors.topMargin: 0
                activeFocusOnTab: false
                anchors.rightMargin: 0
                anchors.leftMargin: 0
            }

            Text {
                id: labelDocuments
                color: "#ffffff"
                text: qsTr("Найденные документы и их релевантность:")
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: parent.top
                font.pixelSize: 12
                anchors.topMargin: 0
            }
        }
    }

    Button {
        id: buttonTags
        x: 1078
        text: qsTr("Tags")
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: groupBoxAddTextToDB.top
        anchors.rightMargin: 30
        anchors.topMargin: 0
        anchors.bottomMargin: 0

        onClicked: {
            tagsWindow.show()
        }
    }

}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.66}
}
##^##*/
