#include "gamemanager.h"
#include <random>
#include <QDateTime>

GameManager::GameManager(QObject *parent) : QObject(parent)
{
    m_socketHandler = new WebSocketHandler( this );

    m_messageProcessHandler = new MessageProcessorHandler( this );

    connect( m_socketHandler, &WebSocketHandler::newMessageToProcess, m_messageProcessHandler, &MessageProcessorHandler::processMessage );

    connect( m_messageProcessHandler, &MessageProcessorHandler::createGameRequest, this, &GameManager::createGameLobbyRequest );
    connect( m_messageProcessHandler, &MessageProcessorHandler::joinGameLobbyRequest, this, &GameManager::joinGameLobbyRequest );
    connect( m_messageProcessHandler, &MessageProcessorHandler::messageLobbyRequest, this, &GameManager::messageLobbyRequest );

}

GameManager::~GameManager()
{
    m_socketHandler->deleteLater();
}

void GameManager::createGameLobbyRequest(QString uniqueID)
{
    std::default_random_engine generator;
    generator.seed( QDateTime::currentMSecsSinceEpoch() );

    std::uniform_int_distribution<int> idGenerator( 1000, 9999 );
    QString newLobbyID = QString::number( idGenerator( generator ) );

    while ( m_gameLobbyMap.keys().contains( newLobbyID ))
    {
        newLobbyID = QString::number( idGenerator( generator ) );
    }

    GameLobbyHandler * newGameLobby = new GameLobbyHandler(newLobbyID, this );

    newGameLobby->addClient( uniqueID );

    m_gameLobbyMap[ newLobbyID ] = newGameLobby;

    qDebug() << "New game lobby created, ID: " << newLobbyID;
    m_socketHandler->sendTextMessageToClient("type:newLobbyCreated;payLoad:" + newLobbyID + ";clientList:" + newGameLobby->clientsInLobby(), uniqueID );

}

void GameManager::joinGameLobbyRequest(QString lobbyID, QString uniqueID)
{
    if ( m_gameLobbyMap.contains( lobbyID ) )
    {
        GameLobbyHandler * existingLobby = m_gameLobbyMap[ lobbyID ];
        existingLobby->addClient( uniqueID );

        m_socketHandler->sendTextMessageToMultipleClients( "type:updatedClientList;payLoad:" + existingLobby->clientsInLobby(), existingLobby->clientsInLobbyList() );

        m_socketHandler->sendTextMessageToClient("type:joinSuccess;payLoad:" + lobbyID + ";clientList:" + existingLobby->clientsInLobby(), uniqueID );
    }
    else
    {
        m_socketHandler->sendTextMessageToClient( "type:joinError;payLoad:DNE", uniqueID );
    }
}

void GameManager::messageLobbyRequest(QString message, QString lobbyID, QString senderID)
{
    qDebug() << "Sending message to clients in lobby: " << lobbyID;
    if ( m_gameLobbyMap.contains( lobbyID ) )
    {
        qDebug() << "Sending message to clients in lobby: " << lobbyID;
        GameLobbyHandler * existingLobby = m_gameLobbyMap[ lobbyID ];
        m_socketHandler->sendTextMessageToMultipleClients( "type:lobbyMessage;payLoad:" + message + ";sender:" + senderID, existingLobby->clientsInLobbyList() );
    }
}

