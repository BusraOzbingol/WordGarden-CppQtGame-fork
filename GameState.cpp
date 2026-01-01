/**
 * @file GameState.cpp
 * @brief Implementation of the GameState class which manages game sessions, timing, and guess limits.
 */

#include "GameState.h"
#include <QDateTime> 
#include <QString>   

/**
 * @brief Constructor for the GameState class.
 * @param word Pointer to the Word object to be guessed in the game.
 * @param maxSeconds The maximum time allowed for the game session in seconds.
 */
 

GameState::GameState(Word* word, int maxSeconds)
    : m_currentWord(word),
      m_maxTimeSeconds(maxSeconds),
      m_remainingGuesses(6) 
{
    
}
/**
 * @brief Starts the game timer by recording the current date and time.
 */

void GameState::startTimer() {
    m_dateTimeStart = QDateTime::currentDateTime();
    m_dateTimeEnd = QDateTime(); 
}
/**
 * @brief Stops the game timer by recording the final date and time.
 */

void GameState::endTimer() {
    m_dateTimeEnd = QDateTime::currentDateTime();
}

/**
 * @brief Calculates the total time elapsed since the game started.
 * @return The elapsed time in seconds. Returns 0 if the timer was never started.
 */

int GameState::getElapsedTime() const {
    if (m_dateTimeStart.isNull()) return 0;
    QDateTime end = m_dateTimeEnd.isNull() ? QDateTime::currentDateTime() : m_dateTimeEnd;
    return static_cast<int>(m_dateTimeStart.msecsTo(end) / 1000);
}
/**
 * @brief Retrieves the string representation of the word currently being guessed.
 * @return A QString containing the current word's text.
 */

QString GameState::getCurrentWordDisplayText() const {
    if (!m_currentWord) return "";
    return QString::fromStdString(m_currentWord->getWord());
}
    
   /**
    * @brief Decreases the number of remaining guesses by one.
    * * This method is typically called after an incorrect letter guess.
    */

void GameState::decreaseRemainingGuesses() {
    if (m_remainingGuesses > 0) {
        m_remainingGuesses--;
    }
}
   /**
    * @brief Checks if the player has successfully guessed all the letters in the word.
    * @return True if the word is fully guessed, false otherwise.
    */
    
bool GameState::isGameWon() const {
    if (!m_currentWord) return false;
    return m_currentWord->isGuessed();
}
    /**
	 * @brief Evaluates all termination conditions (win, out of guesses, or timeout).
	 * @return True if any game-over condition is met, false if the game continues.
	 */
	 
bool GameState::isGameOver() const {
    
    // Condition 1: Word is guessed
    if (isGameWon()) return true;

   // Condition 2: No guesses left
    if (m_remainingGuesses <= 0) return true;

   // Condition 3: Time limit reached    
    if (m_maxTimeSeconds > 0 && getElapsedTime() >= m_maxTimeSeconds) return true;

    return false;
}

/** * @brief Gets the pointer to the current word object.
 * @return Word* pointer. 
 */
Word* GameState::getCurrentWord() const { return m_currentWord; }
/** * @brief Gets the number of incorrect guesses the player has left.
 * @return Remaining guesses count. 
 */
int GameState::getRemainingGuesses() const { return m_remainingGuesses; }

/** * @brief Gets the total time limit for the game.
 * @return Maximum time in seconds. 
 */
int GameState::getMaxTimeSeconds() const { return m_maxTimeSeconds; }
