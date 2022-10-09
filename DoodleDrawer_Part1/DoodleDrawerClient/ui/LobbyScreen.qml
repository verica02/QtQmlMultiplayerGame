import QtQuick 2.0

Item {
    Rectangle {
        id: background
        anchors.fill: parent
        color: "#000014"
    }

    Text {
        id: titleText
        font.pixelSize: 72
        font.bold: true
        anchors {
            top: parent.top
            topMargin: 40
            horizontalCenter: parent.horizontalCenter
        }
        color: "white"
        text: "Lobby code: " + gameManager.roomLobbyCode
    }

    Rectangle {
        id: roomLobbyListBackground
        radius: 5
        color: "transparent"
        width: 345
        height: 418
        anchors {
            top: titleText.bottom
            left: parent.left
            topMargin: 20
            leftMargin: 40
        }
        border.color:"#263ba3"
        border.width: 2

    }

    ListView {
        id: roomLobbyList
        model: gameManager.clientsInLobby
        delegate: Text {
            id: userID
            anchors.horizontalCenter: parent.horizontalCenter
            text: modelData
            font.pixelSize: 36
            color: "white"
            font.bold: true

            Image {
                id: checkImage
                visible: gameManager.isClientReady( modelData )

                Connections {
                    target: gameManager
                    onReadyListChanged: checkImage.visible = gameManager.isClientReady( modelData )
                }

                anchors {
                    left: userID.right
                    leftMargin: 15
                    topMargin: 5
                    verticalCenter: userID.verticalCenter
                }

                source: "qrc:/ui/assets/verified (2).png"
                width: 30
                height: 30
                fillMode: Image.PreserveAspectFit
            }
        }
        anchors.fill: roomLobbyListBackground
    }

    Rectangle {
        id: messageWindowBackground
        radius: 5
        color: "#A4A9AD"
        anchors {
            left: roomLobbyListBackground.right
            leftMargin: 20
            right: parent.right
            rightMargin: 40
            top: roomLobbyListBackground.top
            bottom: roomLobbyListBackground.bottom
        }

    }

//    Rectangle{
//        id:rightRoomLobbyBorder
//        color:"#263ba3"
//        anchors{
//            left:roomLobbyListBackground.right
//            top:roomLobbyListBackground.top
//            bottom:roomLobbyListBackground.bottom
//        }
//        width: 2
//    }

    TextEdit {
        id: messageWindow
        anchors.fill: messageWindowBackground
        font.pixelSize: 24
        color: "white"
        readOnly: true
    }

    Connections {
        target: gameManager
        onNewLobbyMessage: messageWindow.append( message )
    }


    GameButton {
        id: readyButton
        buttonText: "Ready"
        buttonTextPixelSize: 36
        width: 314
        height: 80
        anchors {
            top: roomLobbyListBackground.bottom
            topMargin: 20
            horizontalCenter: roomLobbyListBackground.horizontalCenter
        }

    }

    GameButton {
        id: sendTextButton
        buttonText: "Send"
        buttonTextPixelSize: 36
        width: 174
        anchors {
            top: readyButton.top
            bottom: readyButton.bottom
            right: messageWindowBackground.right
        }
        onButtonClicked: {
            gameManager.sendMessageToLobby( sendTextInput.text )
            sendTextInput.text = ""
        }
    }

    Rectangle {
        id: sendTextFieldBackground
        color: "#232339"
        anchors {
            top: readyButton.top
            bottom: readyButton.bottom
            left: messageWindowBackground.left
            right: sendTextButton.left
            rightMargin: 20
        }
    }

    TextInput {
        id: sendTextInput
        anchors.fill: sendTextFieldBackground
        font.pixelSize: 36
        color: "white"
        clip: true
        onAccepted: {
            gameManager.sendMessageToLobby( sendTextInput.text )
            sendTextInput.text = ""
        }
    }
}
