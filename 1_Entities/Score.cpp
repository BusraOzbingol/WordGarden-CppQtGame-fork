#include "1_Entities/Score.h"

Score::Score() : totalScore(0) {}

void Score::correctGuess() {
    totalScore += 5;
}

void Score::incorrectGuess() {
    totalScore -= 2;
    if (totalScore < 0)
        totalScore = 0;
}

int Score::getTotalScore() const {
    return totalScore;
}

void Score::resetScore() {
    totalScore = 0;
}

void Score::setTotalScore(int score) {
    totalScore = score;
    if (totalScore < 0)
        totalScore = 0;
}
