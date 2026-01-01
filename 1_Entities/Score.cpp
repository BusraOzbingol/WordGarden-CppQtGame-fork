#include "1_Entities/Score.h"

/**
 * @brief Constructs a Score object and initializes totalScore to zero.
 */
Score::Score() : totalScore(0) {}

/**
 * @brief Increases the total by 5 score for a correct guess.
 */
void Score::correctGuess() {
    totalScore += 5;
}

/**
 * @brief Decreases the total score for an incorrect guess
 * Subtracts 2 points. Ensures score does not fall below zero.
 */
void Score::incorrectGuess() {
    totalScore -= 2;
    if (totalScore < 0)
        totalScore = 0;
}

/**
 * @brief Retrieves the current total score.
 * @return The total score as an integer.
 */
int Score::getTotalScore() const {
    return totalScore;
}

/**
 * @brief Resets the total score to zero.
 */
void Score::resetScore() {
    totalScore = 0;
}

/**
 * @brief Sets the total score to a new value.
 * @param score The new score value to assign.
 * Ensures the score cannot go below zero.
 */
void Score::setTotalScore(int score) {
    totalScore = score;
    if (totalScore < 0)
        totalScore = 0;
}

