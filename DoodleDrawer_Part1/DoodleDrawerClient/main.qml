import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

Window {
    width: 1280
    height: 720
    visible: true
    title: qsTr("DoodleDrawerClient")

    Connections {
        target: gameManager
        onInGameLobby: mainLoader.source = "qrc:/ui/LobbyScreen.qml"
        onGameStarting: mainLoader.source = "qrc:/ui/DoodleScreen.qml"
        onDrawInstructionTime: mainLoader.source = "qrc:/ui/DrawingInstructionScreen.qml"
        onVotingTime: mainLoader.source = "qrc:/ui/VoteScreen.qml"
        onGameOver: mainLoader.source = "qrc:/ui/WinnerScreen.qml"
    }

    Loader {
        id: mainLoader
        anchors.fill: parent
        source: "qrc:/ui/MainMenuScreen.qml"
    }
}
