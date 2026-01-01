include "1_Entities/Player.h"
#include <QDebug>

Player::Player(const QString& name, PlayerLevel level)
    : name(name), level(level), lastGameTime(0) {}

QString Player::getName() const {
    return name;
}

QString Player::getLevel() const {
    switch(level) { // NEW UPDATE
        case PlayerLevel::Beginner:     return "Beginner";
        case PlayerLevel::Intermediate: return "Intermediate";
        case PlayerLevel::Expert:       return "Expert";
        default:                        return "Beginner";
    }
}

int Player::getScore() const {
    return score.getTotalScore();
}

void Player::increaseScoreForCorrectGuess() {
    score.correctGuess();
}

void Player::decreaseScoreForIncorrectGuess() {
    score.incorrectGuess();
}

void Player::resetScore() {
    score.resetScore();
}

void Player::setLevel(PlayerLevel newLevel) {
    level = newLevel;
}

void Player::setLastGameTime(int seconds) {
    lastGameTime = seconds;
}

int Player::getLastGameTime() const {
    return lastGameTime;
}

void Player::setScore(int savedScore) {
    score.setTotalScore(savedScore);
}

int Player::getAvatarId() const {
    return avatarId;
}

void Player::setAvatarId(int id) {
    avatarId = id;
}

void Player::addCompletedWord(CategoryEnum cat, const QString& word) {
    if (!completedWords[cat].contains(word) )
        completedWords[cat].append(word);
    qDebug() << "Added word" << word << "to category" << static_cast<int>(cat);
    qDebug() << "Current words in category:" << completedWords[cat];
}

int Player::getTotalCompletedCategoriesCount() const {
    int completedCount = 0;
    // 6 kategoriyi tara (Enum degerleri 0-5 arasi)
    for (int i = 0; i < 6; ++i) {
        CategoryEnum cat = static_cast<CategoryEnum>(i);
        // Eger o kategoride 10 kelime tamamlanmissa bitmis say
        if (completedWords.value(cat).size() >= 10) {
            completedCount++;
        }
    }
    return completedCount;
}

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

int Player::getCategoryProgress(CategoryEnum cat) const {
    return completedWords.value(cat).size();
}

QStringList Player::getCompletedWords(CategoryEnum cat) const {
    return completedWords.value(cat, QStringList());
}

void Player::clearCompletedWords(){
    completedWords.clear();
}
