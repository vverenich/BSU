import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Window 2.12

Window {
    id: tags

    width: 200
    height: 200
    minimumHeight: 200
    minimumWidth: 200
    color: "#ffffff"

    Label {
        id: label
        text: qsTr("Tags")
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.leftMargin: 11
        anchors.topMargin: 8
        color: "#000000"
    }

    ScrollView {
        id: scrollView
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: label.bottom
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        anchors.topMargin: 10

        Text {
            id: textTags

            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            font.pixelSize: 12
            color: "#000000"
            text: "\n
                   NN - Noun, singular\n
                   JJ - Adjective\n
                   VB - Verb, base form\n
                   RB - Adverb\n
                   PR - pronoun\n
                   PRE - preposition\n
                   CC - coordinating conjunction\n
                   UH - interjection\n
                   AJC - comparative adjective\n
                   AVP - adverb particle\n
                   CJC - coordinating conjunction\n
                   DPS - possessive determiner form\n
                   NN1 - singular noun\n
                   NN2 - plural noun\n
                   PNP - personal pronoun\n
"
        }
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:4}
}
##^##*/
