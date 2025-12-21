#include "Player.h"

Player::Player(const QString& name, PlayerLevel level)
    : name(name), level(level), lastGameTime(0) {}

QString Player::getName() const {
    return name;
}

PlayerLevel Player::getLevel() const {
    return level;
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