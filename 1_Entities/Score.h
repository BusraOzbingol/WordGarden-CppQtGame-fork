#ifndef SCORE_H
#define SCORE_H

/**
 * @class Score
 * @brief Manages the scoring system for a player.
 * This class handles all score-related operations such as increasing, decreasing, resetting, and retrieving the total score value.
 */
class Score {
private:
    int totalScore;
    ///< Holds the current total score value.

public:
    /**
     * @brief Constructs a Score object with default initialization.
     */
    Score();

    /**
     * @brief Increases the score due to a correct guess.
     */
    void correctGuess();

    /**
     * @brief Decreases the score due to an incorrect guess.
     */
    void incorrectGuess();

    /**
     * @brief Gets the current total score value.
     * @return The total score as integer.
     */
    int getTotalScore() const;

    /**
     * @brief Resets the total score back to its default value.
     */
    void resetScore();

    /**
     * @brief Sets the total score to a specific value.
     * @param score New total score value.
     */
    void setTotalScore(int score);
};

#endif // SCORE_H

