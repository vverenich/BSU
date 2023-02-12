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
    color: "#ffffff"
    visible: true
    title: qsTr("Search Engine")


    property int textSize: 18
    property int textSizeHeader: 20
    property var tagsWindowComponent: Qt.createComponent("Tags.qml");
    property var tagsWindow: tagsWindowComponent.createObject(mainWindow)

    BackEnd {
        id: backEnd
    }

    GroupBox {
        id: groupBoxAddTextToDB
        x: 22
        width: 1058
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 30
        anchors.rightMargin: 120
        anchors.topMargin: 390
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

            RowLayout {
                y: 0
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.rightMargin: 0
                anchors.leftMargin: 0

                Text {
                    id: labelInformativeWordsPOD
                    color: "#000000"
                    text: qsTr("Канонизированнные информативные слова и их вес:")
                    font.pixelSize: 12
                }

                Text {
                    id: labelTaggedText
                    color: "#000000"
                    text: qsTr("Текст с разметкой:")
                    font.pixelSize: 12
                }
            }

            RowLayout {
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.topMargin: 30

                ScrollView {
                    id: scrollViewInformativeWordsPOD
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    clip: true
                    Text {
                        id: textInformativeWordsPOD
                        color: "#000000"
                        anchors.left: parent.left
                        anchors.right: parent.right
                        anchors.top: parent.top
                        anchors.bottom: parent.bottom
                        clip: false
                        anchors.bottomMargin: 10
                        anchors.leftMargin: 0
                        anchors.topMargin: 10
                    }
                    hoverEnabled: true
                    activeFocusOnTab: false
                }

                ScrollView {
                    id: scrollViewTaggedText
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    clip: true
                    Text {
                        id: textTaggedText
                        color: "#000000"
                        anchors.left: parent.left
                        anchors.right: parent.right
                        anchors.top: parent.top
                        anchors.bottom: parent.bottom
                        clip: false
                        anchors.bottomMargin: 10
                        anchors.leftMargin: 0
                        anchors.topMargin: 10
                    }
                    activeFocusOnTab: false
                    hoverEnabled: true
                }
            }
        }
    }

    GroupBox {
        id: groupBoxSearch
        height: 343
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.rightMargin: 30
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

        RowLayout {
            y: 0
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.leftMargin: 0

            GroupBox {
                id: groupBoxFormPOZ
                Layout.fillHeight: true
                Layout.fillWidth: true
                Layout.preferredHeight: 226
                Layout.preferredWidth: 200
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

                        color: "#000000"
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
                    color: "#000000"
                }
            }

            GroupBox {
                id: groupBoxSearchResults
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.preferredWidth: 200
                title: qsTr("Результаты поиска")

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
                        color: "#000000"
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
                    color: "#000000"
                    text: qsTr("Найденные документы и их релевантность:")
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.top: parent.top
                    font.pixelSize: 12
                    anchors.topMargin: 0
                }
            }
        }
    }

    Button {
        id: buttonTags
        x: 1089
        width: 100
        text: qsTr("Tags")
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.rightMargin: 5
        anchors.bottomMargin: 5

        onClicked: {
            tagsWindow.show()
        }
    }

}


