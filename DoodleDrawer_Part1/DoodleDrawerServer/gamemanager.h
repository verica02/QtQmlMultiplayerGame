#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <QObject>
#include "websockethandler.h"
#include "messageprocessorhandler.h"
#include "gamelobbyhandler.h"

class GameManager : public QObject
{
    Q_OBJECT
public:
    explicit GameManager(QObject *parent = nullptr);
    ~GameManager();

signals:

public slots:
    void createGameLobbyRequest( QString uniqueID );
    void joinGameLobbyRequest( QString lobbyID, QString uniqueID );
    void messageLobbyRequest( QString message, QString lobbyID, QString senderID );


private:
    WebSocketHandler * m_socketHandler;
    MessageProcessorHandler * m_messageProcessHandler;

    QMap< QString, GameLobbyHandler * > m_gameLobbyMap;
};

#endif // GAMEMANAGER_H
