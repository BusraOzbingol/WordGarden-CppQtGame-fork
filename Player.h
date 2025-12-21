#ifndef PLAYER_H
#define PLAYER_H

#include <QString>
#include "PlayerLevel.h"
#include "Score.h"

class Player {
private:
    QString name;
    PlayerLevel level;
    Score score;
    int lastGameTime;

public:
    Player(const QString& name, PlayerLevel level);

    QString getName() const;
    PlayerLevel getLevel() const;
    int getScore() const;

    void increaseScoreForCorrectGuess();
    void decreaseScoreForIncorrectGuess();
    void resetScore();

    void setLevel(PlayerLevel newLevel);
    void setLastGameTime(int seconds);
    int getLastGameTime() const;
};

#endif // PLAYER_H