import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 1.4
import QtQuick.Controls 2.12

import QtQuick.Controls.Material 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls.Styles 1.4

Window {
    id: mainWindow

    property color lightColor: "#ECE9E9"
    property color darkColor: "#4B4747"

    //width: 400
    //height: 225
    //width: 550
    //height: 310
    //width: 650
    //height: 365
    //width: 850
    //height: 475
    //width: 1050
    //height: 590
    //width: 1440
    //height: 810
    //width: 480
    //height: 800
    //width: 360
    //height: 640
    width: 320
    height: 480
    visible: true
    title: qsTr("Train schedule")

    color: lightColor

    Material.theme: Material.Light
    Material.accent: Material.Red

    StackLayout {
        id: stackLayout

        anchors.fill: parent
        currentIndex: 0

        Rectangle {
            id: rectangleLogIn

            color: "transparent"
            anchors.fill: parent

            ComboBox {
                id: comboBoxLanguageLogIn

                x: 330
                y: 0
                z: 100
                width: 70
                height: 40
                anchors.top: parent.top
                anchors.right: parent.right

                model: ListModel {
                    id: modelLanguageLogIn

                    ListElement { text: "BY" }
                    ListElement { text: "EN" }
                }
            }

            ColumnLayout {
                id: columnLayoutLogIn

                x: 56
                y: 93
                z: 1
                width: 314
                height: 40
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.leftMargin: 10
                anchors.rightMargin: 10

                TextField {
                    Layout.fillWidth: true
                    //Layout.maximumWidth: 110
                    placeholderText: qsTr("username")
                }

                TextField {
                    //Layout.maximumWidth: 110
                    Layout.fillWidth: true
                    placeholderText: qsTr("password")
                }

                Button {
                    text: qsTr("Log In")
                    Layout.fillWidth: true
                    //Layout.preferredHeight: 40
                    //Layout.preferredWidth: 56

                    onClicked: {
                        stackLayout.currentIndex = 2
                    }
                }

                Button {
                    text: qsTr("I don't have account")
                    Layout.fillWidth: true
                    background: Rectangle {
                        color: "transparent"
                    }

                    //Layout.preferredHeight: 40
                    //Layout.preferredWidth: 56

                    onClicked: {
                        stackLayout.currentIndex = 1
                    }
                }
            }


        }

        Rectangle {
            id: rectangleSignIn

            color: "transparent"
            anchors.fill: parent

            ComboBox {
                id: comboBoxLanguageSignIn

                x: 330
                y: 0
                z: 100
                width: 70
                height: 40
                anchors.top: parent.top
                anchors.right: parent.right

                model: ListModel {
                    id: modelLanguageSignIn

                    ListElement { text: "BY" }
                    ListElement { text: "EN" }
                }
            }

            ColumnLayout {
                id: columnLayoutSignIn

                x: 56
                y: 93
                z: 1
                width: 314
                height: 40
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.leftMargin: 10
                anchors.rightMargin: 10

                TextField {
                    Layout.fillWidth: true
                    //Layout.maximumWidth: 110
                    placeholderText: qsTr("username")
                }

                TextField {
                    //Layout.maximumWidth: 110
                    Layout.fillWidth: true
                    placeholderText: qsTr("password")
                }

                TextField {
                    //Layout.maximumWidth: 110
                    Layout.fillWidth: true
                    placeholderText: qsTr("repeat password")
                }

                Button {
                    text: qsTr("Sign In")
                    Layout.fillWidth: true
                    //Layout.preferredHeight: 40
                    //Layout.preferredWidth: 56

                    onClicked: {
                        stackLayout.currentIndex = 2
                    }
                }

                Button {
                    text: qsTr("Already have account")
                    Layout.fillWidth: true
                    background: Rectangle {
                        color: "transparent"
                    }

                    //Layout.preferredHeight: 40
                    //Layout.preferredWidth: 56

                    onClicked: {
                        stackLayout.currentIndex = 0
                    }
                }
            }
        }

        Rectangle {
            id: rectangleSearch

            color: "transparent"

            ComboBox {
                id: comboBoxLanguageSearch

                x: 330
                y: 0
                z: 100
                width: 70
                height: 40
                anchors.top: parent.top
                anchors.right: parent.right

                model: ListModel {
                    id: modelLanguageSearch

                    ListElement { text: "BY" }
                    ListElement { text: "EN" }
                }
            }

            Button {
                id: buttonMenu

                anchors.top: parent.top
                anchors.left: parent.left
                text: "menu"

                onClicked: {
                    drawerMenu.visible = true
                }
            }

            Calendar {
                id: calendar

                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
                visible: false
                z: 100
                onSelectedDateChanged: {
                    textFieldWhen.text = Qt.formatDate(calendar.selectedDate, "dd.MM.yyyy")
                    visible = false
                }
            }

            Drawer {
                id: drawerMenu

                edge: Qt.LeftEdge
                width: 200
                height: parent.height


                ColumnLayout {
                    id: columnLayoutMenu

                    Button {
                        text: qsTr("My Profile")
                        Layout.fillWidth: true
                        background: Rectangle {
                            color: "transparent"
                        }

                        onClicked: {
                            drawerMenu.close()
                            stackLayout.currentIndex = 5
                        }
                    }

                    Button {
                        text: qsTr("My Tickets")
                        Layout.fillWidth: true
                        background: Rectangle {
                            color: "transparent"
                        }

                        onClicked: {
                            drawerMenu.close()
                            stackLayout.currentIndex = 4
                        }
                    }

                    Button {
                        text: qsTr("Settings")
                        Layout.fillWidth: true
                        background: Rectangle {
                            color: "transparent"
                        }

                        onClicked: {
                            drawerMenu.close()
                            stackLayout.currentIndex = 3
                        }
                    }

                    Button {
                        text: qsTr("Log Out")
                        Layout.fillWidth: true
                        background: Rectangle {
                            color: "transparent"
                        }

                        onClicked: {
                            drawerMenu.close()
                            stackLayout.currentIndex = 1
                        }
                    }
                }
            }


            ColumnLayout {
                x: 56
                y: 93
                z: 1
                width: 314
                height: 40
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.leftMargin: 10
                anchors.rightMargin: 10

                TextField {
                    id: textField
                    Layout.fillWidth: true
                    //Layout.maximumWidth: 110
                    placeholderText: qsTr("From")
                }

                TextField {
                    id: textField1
                    //Layout.maximumWidth: 110
                    Layout.fillWidth: true
                    placeholderText: qsTr("To")
                }

                RowLayout {
                    TextField {
                        id: textFieldWhen
                        //Layout.minimumWidth: 20
                        //Layout.maximumWidth: 110
                        Layout.fillWidth: true
                        placeholderText: qsTr("When")
                    }

                    Button {
                        id: buttonChooseDate

                        icon.source : "qrc:/calendar.png"

                        onClicked : {
                            calendar.visible = !calendar.visible
                        }

                        /*
                        style: ButtonStyle {
                            background: Image {
                                source: "qrc:/assets/calendar.png"
                            }
                        }
                        */
                    }
                }

                Button {
                    id: button
                    text: qsTr("Go!")
                    Layout.fillWidth: true
                    //Layout.preferredHeight: 40
                    //Layout.preferredWidth: 56
                }
            }
        }
        Rectangle {
            id: rectangleSettings

            color: "transparent"
            anchors.fill: parent

            ComboBox {
                id: comboBoxLanguageSettings

                x: 330
                y: 0
                z: 100
                width: 70
                height: 40
                anchors.top: parent.top
                anchors.right: parent.right

                model: ListModel {
                    id: modelLanguageSettings

                    ListElement { text: "BY" }
                    ListElement { text: "EN" }
                }
            }

            ColumnLayout {
                id: columnLayoutSettings

                x: 56
                y: 93
                z: 1
                width: 314
                height: 40
                anchors.left: parent.left
                anchors.leftMargin: 30
                anchors.right: parent.right
                anchors.rightMargin: 30

                Button {
                    text: qsTr("Change password")
                    Layout.fillWidth: true
                }

                GroupBox {
                    title: qsTr("Application Style:")
                    Layout.fillWidth: true

                    ColumnLayout {
                        RadioDelegate {
                            text: "Dark"

                            onClicked: {
                                mainWindow.Material.theme = Material.Dark
                                mainWindow.color = mainWindow.darkColor
                            }
                        }

                        RadioDelegate {
                            text: "Light"

                            onClicked: {
                                mainWindow.Material.theme = Material.Light
                                mainWindow.color = mainWindow.lightColor
                            }
                        }
                    }
                }


                Button {
                    text: qsTr("Back")
                    Layout.fillWidth: true
                    background: Rectangle {
                        color: "transparent"
                    }

                    //Layout.preferredHeight: 40
                    //Layout.preferredWidth: 56

                    onClicked: {
                        stackLayout.currentIndex = 2
                    }
                }
            }


        }

        Rectangle {
            id: rectangleMyTickets

            color: "transparent"
            anchors.fill: parent

            ComboBox {
                id: comboBoxLanguageMyTickets

                x: 330
                y: 0
                z: 100
                width: 70
                height: 40
                anchors.top: parent.top
                anchors.right: parent.right

                model: ListModel {
                    id: modelLanguageMyTickets

                    ListElement { text: "BY" }
                    ListElement { text: "EN" }
                }
            }

            ColumnLayout {
                id: columnLayoutMyTickets

                x: 56
                y: 93
                z: 1
                width: 314
                height: 40
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.leftMargin: 10
                anchors.rightMargin: 10

                Button {
                    text: qsTr("Back")
                    Layout.fillWidth: true
                    background: Rectangle {
                        color: "transparent"
                    }

                    //Layout.preferredHeight: 40
                    //Layout.preferredWidth: 56

                    onClicked: {
                        stackLayout.currentIndex = 2
                    }
                }
            }
        }

        Rectangle {
            id: rectangleMyProfile

            color: "transparent"
            anchors.fill: parent

            ComboBox {
                id: comboBoxLanguageMyProfile

                x: 330
                y: 0
                z: 100
                width: 70
                height: 40
                anchors.top: parent.top
                anchors.right: parent.right

                model: ListModel {
                    id: modelLanguageMyProfile

                    ListElement { text: "BY" }
                    ListElement { text: "EN" }
                }
            }

            ColumnLayout {
                id: columnLayoutMyProfile

                x: 56
                y: 93
                z: 1
                width: 314
                height: 40

                anchors.left: parent.left
                anchors.right: parent.right
                anchors.leftMargin: 30
                anchors.rightMargin: 30

                Image {
                    id: name

                    Layout.fillWidth: true
                    Layout.maximumWidth: 100
                    Layout.maximumHeight: 100
                    source: "qrc:/Profile.png"
                }

                Label {
                    Layout.fillWidth: true
                    text: "username: "
                }

                Label {
                    Layout.fillWidth: true
                    text: "first log in date: "
                }

                Label {

                    Layout.fillWidth: true
                    text: "phone number: "
                }


                Button {
                    text: qsTr("Back")
                    Layout.fillWidth: true
                    background: Rectangle {
                        color: "transparent"
                    }

                    //Layout.preferredHeight: 40
                    //Layout.preferredWidth: 56

                    onClicked: {
                        stackLayout.currentIndex = 2
                    }
                }
            }
        }
    }
}
