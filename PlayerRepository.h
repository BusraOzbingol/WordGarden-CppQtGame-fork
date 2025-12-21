#ifndef PLAYERREPOSITORY_H
#define PLAYERREPOSITORY_H

#include <QList>
#include "Player.h"

class PlayerRepository {
private:
    QList<Player*> players;

public:
    void addPlayer(Player* player);
    Player* getPlayerByName(const QString& name);
    QList<Player*> getAllPlayers() const;
};

#endif // PLAYERREPOSITORY_H