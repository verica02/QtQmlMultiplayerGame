#ifndef GAMELOBBYHANDLER_H
#define GAMELOBBYHANDLER_H

#include <QObject>
#include <QMap>
class GameLobbyHandler : public QObject
{
    Q_OBJECT
public:
    explicit GameLobbyHandler( QString lobbyID, QObject *parent);
    void addClient( QString clientID );
    QString clientsInLobby();
    QStringList clientsInLobbyList();

signals:

private:
    QString m_lobbyID;
    QList< QString > m_gameClientList; 
};

#endif // GAMELOBBYHANDLER_H
