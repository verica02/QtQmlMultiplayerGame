import QtQuick 2.0

Item {
    id: mainMenuScreen

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
        id: playButton
        anchors.centerIn: parent
        buttonText: "Play"
        width: 336
        height: 105
        onButtonClicked: mainLoader.source = "GameSelectScreen.qml"
    }

    GameButton {
        id: quitButton
        anchors {
            top: playButton.bottom
            topMargin: 40
            horizontalCenter: parent.horizontalCenter
        }

        buttonText: "Quit"
        width: 336
        height: 105
        onButtonClicked: Qt.quit()
    }
}
