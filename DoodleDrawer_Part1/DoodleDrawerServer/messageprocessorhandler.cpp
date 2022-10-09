#include "messageprocessorhandler.h"
#include <QDebug>

#include <QFile>

MessageProcessorHandler::MessageProcessorHandler(QObject *parent) : QObject(parent)
{

}

void MessageProcessorHandler::processMessage(QString message)
{
    //qDebug() << "Server App: Message to process: " << message;
    //type:createGame;payLoad:0;sender:5555
    //type:joinGame;payLoad:4000;sender:5555
    //type:message;payLoad:HelloWorld;lobbyID:5999;sender:5555
    //type:readyToPlay;payLoad:1;sender:5555
    //type:doodleData;payLoad:fileData;sender:clientID
    //type:drawData;payLoad:fileData;sender:clientID
    //type:castVote;payLoad:clientID;sender:1111
    QStringList separated = message.split( QRegExp( ";" ) );
    if ( separated.first() == "type:createGame" )
    {
        //create game
        qDebug() << "Create game request";
        separated.pop_front();
        separated.pop_front();
        if ( separated.first().contains( "sender:" ) )
        {
            QString senderID = separated.first();
            senderID = senderID.remove("sender:");
            emit createGameRequest( senderID );
        }

    }
    else if ( separated.first() == "type:joinGame" )
    {
        //join game
        qDebug() << "join game request";
        separated.pop_front();
        QString lobbyID = QString();
        QString senderID = QString();
        if ( separated.first().contains( "payLoad:") )
        {
            lobbyID = separated.first();
            lobbyID = lobbyID.remove("payLoad:");
        }
        separated.pop_front();
        if ( separated.front().contains( "sender:" ) )
        {
            senderID = separated.front();
            senderID = senderID.remove("sender:");
        }

        if ( ( lobbyID != QString() ) && ( senderID != QString() ) )
            emit joinGameLobbyRequest( lobbyID, senderID );

    }
    else if ( separated.first() == "type:message" )
    {
        // message to lobby
        //type:message;payLoad:HelloWorld;lobbyID:5999;sender:5555
        qDebug() << "lobby message request";
        QString payLoad = QString();
        QString lobbyID = QString();
        QString senderID = QString();

        separated.pop_front();

        if ( separated.front().contains("payLoad:") )
        {
            payLoad = separated.front();
            payLoad = payLoad.remove("payLoad:");
        }

        separated.pop_front();

        if ( separated.front().contains("lobbyID:") )
        {
            lobbyID = separated.front();
            lobbyID = lobbyID.remove("lobbyID:");
        }
        separated.pop_front();

        if ( separated.front().contains("sender:") )
        {
            senderID = separated.front();
            senderID = senderID.remove("sender:");
        }

        if ( payLoad != QString() && lobbyID != QString() && senderID != QString() )
            emit messageLobbyRequest( payLoad, lobbyID, senderID );
    }
    else if ( separated.front() == "type:readyToPlay" )
    {
        //type:readyToPlay;payLoad:1;sender:5555
        if ( separated.back().contains( "sender:") )
        {
            QString clientID = separated.back();
            clientID = clientID.remove( "sender:" );           
        }
    }   
}
