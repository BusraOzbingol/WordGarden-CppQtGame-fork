#ifndef PLAYER_H
#define PLAYER_H

#include <QString>
#include <QMap>
#include <QStringList>
#include "0_Enums/PlayerLevel.h"
#include "1_Entities/Score.h"
#include "0_Enums/CategoryEnum.h"

class Player {
private:
    QString name;
    PlayerLevel level;
    Score score;
    int avatarId = 0;
    int lastGameTime = 0;
    QMap<CategoryEnum, QStringList> completedWords;

public:
    Player(const QString& name, PlayerLevel level);
    int getAvatarId() const;
    void setAvatarId(int id);
    QString getName() const;
    QString getLevel() const;
    int getScore() const;

    void increaseScoreForCorrectGuess();
    void decreaseScoreForIncorrectGuess();
    void resetScore();
    void setScore(int savedScore);
    void setLevel(PlayerLevel newLevel);
    void setLastGameTime(int seconds);
    int getLastGameTime() const;

    void addCompletedWord(CategoryEnum cat, const QString& word);
    void clearCompletedWords();
    QStringList getCompletedWords(CategoryEnum cat) const;
    int getCategoryProgress(CategoryEnum cat) const;
    int getTotalCompletedCategoriesCount() const;
    void checkAndUpgradeLevel();
    PlayerLevel getLevelEnum() const { return level; }
};

#endif // PLAYER_H
