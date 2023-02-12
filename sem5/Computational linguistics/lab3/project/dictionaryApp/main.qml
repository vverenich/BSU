import QtQuick 2.12
import QtQuick.Window 2.15
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Layouts 1.0
import BackEnd 1.0

Window {
    id: mainWindow

    width: 1200
    height: 1000
    minimumWidth: 1200
    minimumHeight: 900
    color: "#252525"
    visible: true
    title: qsTr("Dictionary")

    Material.theme: Material.Dark
    Material.accent: Material.Green

    property int textSize: 18
    property int textSizeHeader: 20

    BackEnd {
        id: backEnd
    }

    GroupBox {
        id: groupBoxFind

        width: 573
        height: 452
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.topMargin: 30
        anchors.leftMargin: 30
        title: qsTr("Find the word in the dictionary by match")

        TextField {
            id: textFieldFindWord

            color: "#ffffff"
            anchors.left: buttonFind.right
            anchors.right: parent.right
            anchors.top: parent.top
            font.pixelSize: 12
            placeholderText: "Type here..."
            anchors.leftMargin: 20
            anchors.topMargin: 0
            anchors.rightMargin: 0
        }

        Button {
            id: buttonFind

            text: qsTr("Find")
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.leftMargin: 0
            anchors.topMargin: 0

            onClicked: {
                if (!switchDelegateBeginEnd.checked) {
                    backEnd.getMatchesBegin(textFieldFindWord.text)
                } else {
                    backEnd.getMatchesEnd(textFieldFindWord.text)
                }

                textNumberOfWordsTotal.text = backEnd.getTotalNumberOfMatches()
                textUniqueWords.text = backEnd.getNumberOfUniqueMatches()
            }
        }

        SwitchDelegate {
            id: switchDelegateBeginEnd

            height: 52
            text: qsTr("By match at the beginning(OFF) or at the end(ON) of the word")
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: columnLayoutSortByFrequencyMatch.bottom
            anchors.topMargin: 20
            anchors.leftMargin: 0
            anchors.rightMargin: 9
        }

        ScrollView {
            id: scrollViewMatch

            anchors.top: switchDelegateBeginEnd.bottom
            anchors.topMargin: 20
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.bottom: rowLayoutNumberOfWordsMatch.top
            clip: true
            activeFocusOnTab: false
            hoverEnabled: true
            anchors.bottomMargin: 30
            anchors.left: parent.left
            anchors.leftMargin: 0
            ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
            ScrollBar.vertical.policy: ScrollBar.AlwaysOn

            Text {
                id: textWordsThatWasFound

                width: scrollViewMatch.width * 0.95
                height: scrollViewMatch.height * 0.95
                color: "#ffffff"
                clip: false
            }
        }

        RowLayout {
            id: rowLayoutNumberOfWordsMatch

            y: 401
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.rightMargin: 0
            anchors.leftMargin: 0

            Label {
                id: labelNumberOfUniqueWords

                color: "#ffffff"
                text: qsTr("Unique words:")
            }

            Text {
                id: textUniqueWords

                color: "#ffffff"
                text: qsTr("0")
                font.pixelSize: 12
            }

            Label {
                id: labelNumberOfWordsMatch

                color: "#ffffff"
                text: qsTr("Total number of words:")
            }

            Text {
                id: textNumberOfWordsTotal

                color: "#ffffff"
                text: qsTr("0")
                font.pixelSize: 12
            }
        }

        Button {
            id: buttonSortAlphabeticallyMatch

            width: 176
            height: 49
            text: qsTr("Sort alphabetically")
            anchors.left: parent.left
            anchors.top: buttonFind.bottom
            anchors.leftMargin: -5
            anchors.topMargin: 20

            onClicked: {
                textWordsThatWasFound.text = backEnd.getMatchesSortedAlphabetically()
            }
        }

        ColumnLayout {
            id: columnLayoutSortByFrequencyMatch

            x: 215
            width: 325
            height: 98
            anchors.top: textFieldFindWord.bottom
            anchors.topMargin: 20
            Button {
                id: buttonSortByFrequencyMatch

                text: qsTr("Sort by frequency")
                Layout.preferredHeight: 40
                Layout.preferredWidth: 255
                Layout.fillWidth: true

                onClicked: {
                    if (radioDelegateAscendingMatch.checked) {
                        textWordsThatWasFound.text = backEnd.getMatchesSortedByFrequencyAsc()
                    } else {
                        textWordsThatWasFound.text = backEnd.getMatchesSortedByFrequencyDesc()
                    }
                }
            }

            RowLayout {
                id: rowLayoutAscDesc1

                Layout.preferredHeight: 52
                Layout.preferredWidth: 260

                RadioDelegate {
                    id: radioDelegateAscendingMatch

                    text: qsTr("Ascending")
                    Layout.fillHeight: true
                    checked: true
                    Layout.fillWidth: true
                }

                RadioDelegate {
                    id: radioDelegateDescendingMatch

                    text: qsTr("Descending")
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                }

            }
        }
    }

    GroupBox {
        id: groupBoxSort

        y: 518
        width: 573
        height: 352
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 30
        anchors.leftMargin: 30
        title: qsTr("Sort words in the dictionary")

        Button {
            id: buttonSortAlphabetically

            width: 176
            height: 49

            text: qsTr("Sort alphabetically")
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.leftMargin: 0
            anchors.topMargin: 0

            onClicked: {
                textWordsSorted.text = backEnd.getWordsSortedAlphabetically()
            }
        }

        ScrollView {
            id: scrollViewSort

            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: columnLayoutSortByFrequency.bottom
            anchors.bottom: parent.bottom
            hoverEnabled: true
            anchors.bottomMargin: 20
            activeFocusOnTab: false
            anchors.leftMargin: 0
            anchors.rightMargin: 0
            clip: true
            anchors.topMargin: 0

            Text {

                id: textWordsSorted

                width: scrollViewSort.width * 0.95
                height: scrollViewSort.height * 0.95
                color: "#ffffff"
                clip: false
            }
        }

        ColumnLayout {
            id: columnLayoutSortByFrequency

            x: 220
            y: 0
            width: 325
            height: 98

            Button {
                id: buttonSortByFrequency

                text: qsTr("Sort by frequency")
                Layout.fillWidth: true
                Layout.preferredHeight: 40
                Layout.preferredWidth: 255

                onClicked: {
                    if (radioDelegateAscending.checked) {
                        textWordsSorted.text = backEnd.getWordsSortedByFrequencyAsc()
                    } else {
                        textWordsSorted.text = backEnd.getWordsSortedByFrequencyDesc()
                    }
                }
            }

            RowLayout {
                id: rowLayoutAscDesc

                Layout.preferredHeight: 52
                Layout.preferredWidth: 260

                RadioDelegate {
                    id: radioDelegateAscending

                    text: qsTr("Ascending")
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    checked: true
                }

                RadioDelegate {
                    id: radioDelegateDescending

                    text: qsTr("Descending")
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                }
            }
        }
    }

    ColumnLayout {
        id: columnLayoutBasicOperations

        x: 711
        width: 459
        height: 843
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.topMargin: 30
        anchors.rightMargin: 30

        GroupBox {
            id: groupBoxNumberOfWords
            Layout.fillHeight: true

            Layout.preferredHeight: 90
            Layout.preferredWidth: 459
            title: qsTr("Number of words")

            Button {
                id: buttonRefreshWordsCount

                width: 98
                text: qsTr("Refresh ")
                anchors.left: parent.left
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.topMargin: 0
                anchors.bottomMargin: 0
                anchors.leftMargin: 0

                onClicked: {
                    textUniqueWordsGeneral.text = backEnd.getNumberOfWordsInDictionary()
                    textNumberOfWordsTotalGeneral.text = backEnd.getTotalNumberOfWords()
                }
            }

            RowLayout {
                id: rowLayoutNumberOfWordsMatchGeneral

                x: -697
                anchors.left: buttonRefreshWordsCount.right
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.topMargin: 0
                anchors.leftMargin: 20
                anchors.rightMargin: -8
                anchors.bottomMargin: 0

                Label {
                    id: labelNumberOfUniqueWordsGeneral

                    color: "#ffffff"
                    text: qsTr("Unique words:")
                }

                Text {
                    id: textUniqueWordsGeneral

                    color: "#ffffff"
                    text: qsTr("0")
                    font.pixelSize: 12
                }

                Label {
                    id: labelNumberOfWordsMatchGeneral

                    color: "#ffffff"
                    text: qsTr("Total number of words:")
                }

                Text {
                    id: textNumberOfWordsTotalGeneral

                    color: "#ffffff"
                    text: qsTr("0")
                    font.pixelSize: 12
                }
            }
        }

        GroupBox {
            id: groupBoxNewWord
            Layout.fillHeight: true

            Layout.preferredHeight: 90
            Layout.preferredWidth: 459
            title: qsTr("Add the word to the dictionary")

            TextField {
                id: textFieldNewWord

                color: "#ffffff"
                anchors.left: buttonAddWord.right
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                placeholderText: "Type here..."
                font.pixelSize: 12
                anchors.rightMargin: 0
                anchors.leftMargin: 20
                anchors.bottomMargin: 0
                anchors.topMargin: 0
            }

            Button {
                id: buttonAddWord

                text: qsTr("Add")
                anchors.left: parent.left
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.topMargin: 0
                anchors.bottomMargin: 0
                anchors.leftMargin: 0

                onClicked: {
                    backEnd.addWordToTheDictionary(textFieldNewWord.text, 0)
                }
            }
        }

        GroupBox {
            id: groupBoxRemoveWord
            Layout.fillHeight: true

            Layout.preferredHeight: 90
            Layout.preferredWidth: 459
            title: qsTr("Remove word from the dictionary")

            TextField {
                id: textFieldRemoveWord

                color: "#ffffff"
                anchors.left: buttonRemoveWord.right
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                placeholderText: "Type here..."
                font.pixelSize: 12
                anchors.leftMargin: 20
            }

            Button {
                id: buttonRemoveWord

                text: qsTr("Remove")
                anchors.left: parent.left
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.topMargin: 0
                anchors.bottomMargin: 0
                anchors.leftMargin: 0

                onClicked: {
                    backEnd.removeWord(textFieldRemoveWord.text)
                }
            }
        }

        GroupBox {
            id: groupBoxCheckWord
            Layout.fillHeight: true

            Layout.preferredHeight: 90
            Layout.preferredWidth: 459
            title: qsTr("Check the word in the dictionary")

            TextField {
                id: textFieldCheckWord

                color: "#ffffff"
                anchors.left: buttonCheckWord.right
                anchors.right: checkBox.left
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                font.pixelSize: 12
                anchors.rightMargin: 0
                anchors.topMargin: 0
                anchors.bottomMargin: 0
                anchors.leftMargin: 20
                placeholderText: "Type here..."
            }

            CheckBox {
                id: checkBox

                x: 167
                width: 39
                text: qsTr("Check Box")
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                font.pixelSize: 8
                anchors.topMargin: 0
                anchors.bottomMargin: 0
                anchors.rightMargin: 0
                checkState: Qt.Unchecked
                checkable: false
            }

            Button {
                id: buttonCheckWord

                text: qsTr("Check")
                anchors.left: parent.left
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.topMargin: 0
                anchors.bottomMargin: 0
                anchors.leftMargin: 0

                onClicked: {
                    if(backEnd.isWordInTheDictionary(textFieldCheckWord.text)) {
                        checkBox.checkState = Qt.Checked
                    } else {
                        checkBox.checkState = Qt.Unchecked
                    }
                }
            }
        }

        GroupBox {
            id: groupBoxGetWordFrequency
            Layout.fillHeight: true

            Layout.preferredHeight: 90
            Layout.preferredWidth: 459
            title: qsTr("Get the word's frequency in the dictionary")

            TextField {
                id: textFieldGetFrequency

                color: "#ffffff"
                anchors.left: buttonGetFrequency.right
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                font.pixelSize: 12
                anchors.bottomMargin: 0
                anchors.rightMargin: 39
                placeholderText: "Type here..."
                anchors.topMargin: 0
                anchors.leftMargin: 20
            }

            Button {
                id: buttonGetFrequency

                text: qsTr("Get")
                anchors.left: parent.left
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 0
                anchors.topMargin: 0
                anchors.leftMargin: 0

                onClicked: {
                    textFrequency.text = (backEnd.getWordFrequency(textFieldGetFrequency.text)).toFixed(3)
                }
            }

            Text {
                id: textFrequency

                color: "#ffffff"
                text: qsTr("0")
                anchors.left: textFieldGetFrequency.right
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                font.pixelSize: 12
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                anchors.rightMargin: 0
                anchors.leftMargin: 0
                anchors.bottomMargin: 0
                anchors.topMargin: 0
            }
        }

        GroupBox {
            id: groupBoxReadText
            Layout.fillHeight: true

            Layout.preferredHeight: 90
            Layout.preferredWidth: 459
            title: qsTr("Read text")

            TextField {
                id: textFieldReadText

                color: "#ffffff"
                anchors.left: buttonReadText.right
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                font.pixelSize: 12
                placeholderText: "File with text"
                anchors.leftMargin: 20
            }

            Button {
                id: buttonReadText

                text: qsTr("Read")
                anchors.left: parent.left
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 0
                anchors.leftMargin: 0
                anchors.topMargin: 0

                onClicked: {
                    backEnd.readTextFromFile(textFieldReadText.text)
                }
            }
        }

        GroupBox {
            id: groupBoxReplace
            Layout.fillHeight: true

            Layout.preferredHeight: 90
            Layout.preferredWidth: 459
            title: qsTr("Replace")

            Button {
                id: buttonReplace

                text: qsTr("Replace")
                anchors.left: parent.left
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 0
                anchors.leftMargin: 0
                anchors.topMargin: 0

                onClicked: {
                    backEnd.replaceWord(textFieldInitialWord.text, textFieldReplacedWord.text)
                }
            }

            RowLayout {
                id: rawLayout

                anchors.left: buttonReplace.right
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.topMargin: 0
                anchors.bottomMargin: 0
                anchors.rightMargin: 0
                anchors.leftMargin: 20
                visible: true

                TextField {
                    id: textFieldInitialWord

                    color: "#ffffff"
                    font.pixelSize: 12
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    placeholderText: "Replace from"
                }

                TextField {
                    id: textFieldReplacedWord

                    color: "#ffffff"
                    font.pixelSize: 12
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    placeholderText: "Replace to"
                }
            }
        }

        GroupBox {
            id: groupBoxSaveDictionary

            x: 623
            y: 726
            Layout.fillHeight: true
            Layout.preferredHeight: 90
            Layout.preferredWidth: 459
            title: qsTr("Save current dictionary")

            TextField {
                id: textFieldSaveDictionary

                color: "#ffffff"
                anchors.left: buttonSaveDictionary.right
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                font.pixelSize: 12
                anchors.leftMargin: 20
                placeholderText: "Name of the new dictionary"
            }

            Button {
                id: buttonSaveDictionary

                text: qsTr("Save dictionary")
                anchors.left: parent.left
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.leftMargin: 0
                anchors.bottomMargin: 0

                onClicked: {
                    backEnd.saveDictionary(textFieldSaveDictionary.text)
                }
                anchors.topMargin: 0
            }
        }

        GroupBox {
            id: groupBoxRestoreDictionary
            Layout.fillHeight: true
            Layout.preferredWidth: 459
            title: qsTr("Save current dictionary")
            Layout.preferredHeight: 90
            TextField {
                id: textFieldRestoreDictionary
                color: "#ffffff"
                anchors.left: buttonRestoreDictionary.right
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                font.pixelSize: 12
                placeholderText: "Name of the dictionary"
                anchors.leftMargin: 20
            }

            Button {
                id: buttonRestoreDictionary
                text: qsTr("Restore dictionary")
                anchors.left: parent.left
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                onClicked: {
                    backEnd.restoreDictionary(textFieldRestoreDictionary.text)
                }
                anchors.leftMargin: 0
                anchors.topMargin: 0
                anchors.bottomMargin: 0
            }
        }
    }

    RowLayout {
        id: rowLayoutButtons

        x: 722
        y: 811
        width: 459
        height: 40
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.rightMargin: 30
        anchors.bottomMargin: 30

        Button {
            id: buttonSaveText

            text: qsTr("Save text")
            Layout.fillHeight: true
            Layout.fillWidth: true

            onClicked: {
                backEnd.saveText(textFieldReadText.text)
            }
        }

        Button {
            id: buttonClearDictionary

            text: qsTr("Clear dictionary")
            Layout.fillHeight: true
            Layout.fillWidth: true

            onClicked: {
                backEnd.clearDictionary()
            }
        }
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.75}D{i:61}
}
##^##*/
