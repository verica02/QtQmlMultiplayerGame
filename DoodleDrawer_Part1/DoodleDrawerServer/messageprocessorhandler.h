#ifndef MESSAGEPROCESSORHANDLER_H
#define MESSAGEPROCESSORHANDLER_H

#include <QObject>

class MessageProcessorHandler : public QObject
{
    Q_OBJECT
public:
    explicit MessageProcessorHandler(QObject *parent = nullptr);

public slots:
    void processMessage( QString message );

signals:
    void createGameRequest( QString uniqueID );
    void joinGameLobbyRequest( QString lobbyID, QString uniqueID );
    void messageLobbyRequest( QString message, QString lobbyID, QString senderID );    
};

#endif // MESSAGEPROCESSORHANDLER_H
