import QtQuick 2.0

Item {
    id: gameSelectScreen

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
        text: "DoodleDrawer"
    }

    GameButton {
        id: createGameButton
        anchors {
            top: titleText.bottom
            topMargin: 160
            horizontalCenter: parent.horizontalCenter
        }

        buttonText: "Create Game"
        buttonTextPixelSize: 48
        width: 336
        height: 105
        onButtonClicked: gameManager.createGameRequest()
    }

    GameButton {
        id: joinGameButton
        anchors {
            top: createGameButton.bottom
            topMargin: 40
            horizontalCenter: parent.horizontalCenter
        }

        buttonText: "Join Game"
        buttonTextPixelSize: 48
        width: 336
        height: 105
        onButtonClicked: mainLoader.source = "JoinLobbyScreen.qml"
    }

    GameButton {
        id: backButton
        anchors {
            top: joinGameButton.bottom
            topMargin: 40
            horizontalCenter: parent.horizontalCenter
        }

        buttonText: "Back"
        buttonTextPixelSize: 48
        width: 336
        height: 105
        onButtonClicked: mainLoader.source = "MainMenuScreen.qml"
    }

}
