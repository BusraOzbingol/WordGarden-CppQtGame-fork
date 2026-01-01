#ifndef PLAYER_H
#define PLAYER_H

#include <QString>
#include <QMap>
#include <QStringList>
#include "0_Enums/PlayerLevel.h"
#include "1_Entities/Score.h"
#include "0_Enums/CategoryEnum.h"

/**
 * @class Player
 * @brief Represents a player in the game.
 */
class Player {
private:
    QString name;                // Player's display name
    PlayerLevel level;           // Player's current skill level
    Score score;                 // Player's score
    int avatarId = 0;            // ID of the player's selected avatar
    int lastGameTime = 0;        // Duration of player's last game session (in seconds)
    QMap<CategoryEnum, QStringList> completedWords;
    // Stores completed words grouped by categories

public:
    /**
     * @brief Constructor for Player
     * @param name Player name
     * @param level Player level
     */
    Player(const QString& name, PlayerLevel level);

    int getAvatarId() const;
    // Returns the player's avatar ID
    void setAvatarId(int id);
    // Sets the player's avatar ID
    QString getName() const;
    // Returns the player's name
    QString getLevel() const;
    // Returns the player's level as string
    int getScore() const;
    // Returns the player's score value

    void increaseScoreForCorrectGuess();
    // Increases score for a correct guess
    void decreaseScoreForIncorrectGuess();
    // Decreases score for an incorrect guess
    void resetScore();
    // Resets the player's score to default
    void setScore(int savedScore);
    // Sets the player's score manually
    void setLevel(PlayerLevel newLevel);
    // Sets player's level enum value
    void setLastGameTime(int seconds);
    // Saves the player's last game time
    int getLastGameTime() const;
    // Returns the last recorded game time

    void addCompletedWord(CategoryEnum cat, const QString& word);
    // Adds a completed word under a specific category
    void clearCompletedWords();
    // Clears all completed word data
    QStringList getCompletedWords(CategoryEnum cat) const;
    // Returns completed words for a category
    int getCategoryProgress(CategoryEnum cat) const;
    // Returns how many words the player completed in a category
    int getTotalCompletedCategoriesCount() const;
    // Returns total number of categories in which player completed words
    void checkAndUpgradeLevel();
    // Checks progress and upgrades player's level if needed
    PlayerLevel getLevelEnum() const { return level; }
    // Returns the enum level value
};

#endif // PLAYER_H

