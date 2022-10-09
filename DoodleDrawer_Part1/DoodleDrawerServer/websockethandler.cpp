#include "websockethandler.h"
#include <random>
#include <QDateTime>
#include <QDebug>

WebSocketHandler::WebSocketHandler(QObject *parent) : QObject(parent)
{
    m_socketServer = new QWebSocketServer( "DoodleDrawerServer", QWebSocketServer::NonSecureMode, this );

    connect( m_socketServer, &QWebSocketServer::newConnection, this, &WebSocketHandler::onNewSocketConnection );

    if ( m_socketServer->listen( QHostAddress::Any, 8585 ) )
    {
        qDebug() << "Server is running!";
    }
    else
    {
        qDebug() << "Server unable to start listening for connections!";
    }
}

WebSocketHandler::~WebSocketHandler()
{
    m_socketServer->deleteLater();
}

void WebSocketHandler::onNewSocketConnection()
{
    qDebug() << "New client connected!";

    std::default_random_engine generator;
    generator.seed( QDateTime::currentMSecsSinceEpoch() );

    std::uniform_int_distribution<int> idGenerator( 1000, 9999 );
    QString newClientID = QString::number( idGenerator( generator ) );

    while ( m_clientList.keys().contains( newClientID ))
    {
        newClientID = QString::number( idGenerator( generator ) );
    }

    qDebug() << "New client ID: " << newClientID;

    auto nextClient = m_socketServer->nextPendingConnection();
    nextClient->setParent( this );

    connect( nextClient, &QWebSocket::textMessageReceived, this, &WebSocketHandler::onTextMessageReceived );
    connect( nextClient, &QWebSocket::disconnected, this, &WebSocketHandler::onSocketDisconnected );

    nextClient->sendTextMessage("type:uniqueID;payLoad:" + newClientID );

    m_clientList[ newClientID ] = nextClient;
}

void WebSocketHandler::sendTextMessageToClient( QString message, QString clientID )
{
    if ( m_clientList.contains( clientID ) )
    {
        QWebSocket * existingClient = m_clientList[ clientID ];
        existingClient->sendTextMessage( message );
    }
}

void WebSocketHandler::sendTextMessageToMultipleClients(QString message, QStringList clientIDs)
{
    foreach( const QString & client, clientIDs )
    {
        sendTextMessageToClient( message, client );
    }
}

void WebSocketHandler::onTextMessageReceived(QString message)
{
    //qDebug() << "Server received:  " << message;
    emit newMessageToProcess( message );
}

void WebSocketHandler::onSocketDisconnected()
{
    auto client = qobject_cast< QWebSocket * >(sender());
    if ( client )
    {
        for ( QMap< QString, QWebSocket *>::iterator mapIterator = m_clientList.begin();
              mapIterator != m_clientList.end();
              mapIterator++ )
        {
            if ( mapIterator.value() == client )
            {
                QString uid = mapIterator.key();
                m_clientList.remove( uid );
                client->deleteLater();
            }
        }
    }
}
