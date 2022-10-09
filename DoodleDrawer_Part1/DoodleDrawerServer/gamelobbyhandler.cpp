#include "gamelobbyhandler.h"
#include <random>
#include <QDateTime>

GameLobbyHandler::GameLobbyHandler(QString lobbyID, QObject *parent)
    : QObject(parent)
    , m_lobbyID( lobbyID )
{

 }

void GameLobbyHandler::addClient(QString clientID)
{
    if ( !m_gameClientList.contains(clientID) )
        m_gameClientList.append(clientID);   
}

QString GameLobbyHandler::clientsInLobby()
{
    QString ret;
    foreach( const QString & client, m_gameClientList )
        ret.append( client + "," );

    //1111,2222,3333,4444,
    ret.chop( 1 );
    //1111,2222,3333,4444

    return ret;
}

QStringList GameLobbyHandler::clientsInLobbyList()
{
    return m_gameClientList;
}

