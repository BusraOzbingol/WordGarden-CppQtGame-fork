#ifndef PLAYERMANAGER_H
#define PLAYERMANAGER_H

#include "2_Repository/PlayerRepository.h"

class PlayerManager {
private:
    PlayerRepository* repository;

public:
    PlayerManager(PlayerRepository* repository);

    Player* createPlayer(const QString& name, PlayerLevel level);
    Player* getPlayer(const QString& name);
};

#endif // PLAYERMANAGER_H

