#ifndef PLAYERREPOSITORY_H
#define PLAYERREPOSITORY_H

#include <QList>
#include "1_Entities/Player.h"

class PlayerRepository {
private:
    QList<Player*> players;

public:
    void addPlayer(Player* player);
    Player* getPlayerByName(const QString& name);
    QList<Player*> getAllPlayers() const;
    void clear();
};

#endif // PLAYERREPOSITORY_H

