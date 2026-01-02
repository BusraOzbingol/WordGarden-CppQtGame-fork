#include "1_Entities/Player.h"
#include <QDebug>

/**
 * @brief Constructs a Player object with a given name and level.
 * @param name The player's name.
 * @param level The initial PlayerLevel.
 */
Player::Player(const QString& name, PlayerLevel level)
    : name(name), level(level), lastGameTime(0) {}

/**
 * @brief Gets the player's name.
 * @return Player name as QString.
 */
QString Player::getName() const {
    return name;
}

/**
 * @brief Converts the player's level enum to a readable string format.
 * @return Player level as a QString.
 */
QString Player::getLevel() const {
    switch(level) {
        case PlayerLevel::Beginner:     return "Beginner";
        case PlayerLevel::Intermediate: return "Intermediate";
        case PlayerLevel::Expert:       return "Expert";
        default:                        return "Beginner";
    }
}

/**
 * @brief Gets the player's current score.
 * @return Total score as an integer.
 */
int Player::getScore() const {
    return score.getTotalScore();
}

/**
 * @brief Increases player's score by 5 for a correct guess.
 */
void Player::increaseScoreForCorrectGuess() {
    score.correctGuess();
}

/**
 * @brief Decreases player's score by 2 for an incorrect guess.
 */
void Player::decreaseScoreForIncorrectGuess() {
    score.incorrectGuess();
}

/**
 * @brief Resets the player's score to zero or default state.
 */
void Player::resetScore() {
    score.resetScore();
}

/**
 * @brief Sets the player's level manually.
 * @param newLevel New PlayerLevel value.
 */
void Player::setLevel(PlayerLevel newLevel) {
    level = newLevel;
}
/**
 * @brief Sets the player's last game duration.
 * @param seconds Playtime duration in seconds.
 */
void Player::setLastGameTime(int seconds) {
    lastGameTime = seconds;
}

/**
 * @brief Gets the duration of the player's last game.
 * @return Last game duration in seconds.
 */
int Player::getLastGameTime() const {
    return lastGameTime;
}

/**
 * @brief Sets the player's score from saved data.
 * @param savedScore Stored score value.
 */
void Player::setScore(int savedScore) {
    score.setTotalScore(savedScore);
}

/**
 * @brief Retrieves the player's avatar ID.
 * @return Avatar ID as integer.
 */
int Player::getAvatarId() const {
    return avatarId;
}

/**
 * @brief Sets the player's avatar ID.
 * @param id Avatar ID value.
 */
void Player::setAvatarId(int id) {
    avatarId = id;
}

/**
 * @brief Adds a completed word to a category if not already added.
 * @param cat The category of the word.
 * @param word The completed word.
 */
void Player::addCompletedWord(CategoryEnum cat, const QString& word) {
    if (!completedWords[cat].contains(word) )
        completedWords[cat].append(word);
    qDebug() << "Added word" << word << "to category" << static_cast<int>(cat);
    qDebug() << "Current words in category:" << completedWords[cat];
}

/**
 * @brief Calculates number of categories with at least 10 completed words.
 * @return Count of completed categories.
 */
int Player::getTotalCompletedCategoriesCount() const {
    int completedCount = 0;
    for (int i = 0; i < 6; ++i) {
        CategoryEnum cat = static_cast<CategoryEnum>(i);
        if (completedWords.value(cat).size() >= 10) {
            completedCount++;
        }
    }
    return completedCount;
}

/**
 * @brief Upgrades player's level based on completed category count.
 */
void Player::checkAndUpgradeLevel() {
    int count = getTotalCompletedCategoriesCount();
    if (count >= 4) {
        level = PlayerLevel::Expert;
    } else if (count >= 2) {
        level = PlayerLevel::Intermediate;
    } else {
        level = PlayerLevel::Beginner;
    }
}

/**
 * @brief Gets the number of completed words from a category.
 * @param cat CategoryEnum value.
 * @return Number of completed words.
 */
int Player::getCategoryProgress(CategoryEnum cat) const {
    return completedWords.value(cat).size();
}

/**
 * @brief Retrieves all completed words for a given category.
 * @param cat CategoryEnum value.
 * @return QStringList containing words.
 */
QStringList Player::getCompletedWords(CategoryEnum cat) const {
    return completedWords.value(cat, QStringList());
}

/**
 * @brief Clears all completed word records.
 */
void Player::clearCompletedWords(){
    completedWords.clear();
}



