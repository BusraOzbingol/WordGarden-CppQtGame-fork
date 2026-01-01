/**
 * @file GameState.h
 * @brief Header file for the GameState class.
 * * Defines the attributes and behaviors for a single game session, 
 * including word tracking, time management, and guess limits.
 */

#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <QDateTime> 
#include <QString>
#include "Word.h"

/**
 * @class GameState
 * @brief Manages the current state of a word-guessing game session.
 * * This class keeps track of the target word, calculates the elapsed time, 
 * and monitors the player's remaining attempts.
 */
class GameState {
public:
    /**
	     * @brief Constructs a new GameState object.
	     * @param word Pointer to the target Word object.
	     * @param maxSeconds Maximum duration allowed for the game in seconds.
	     */
    GameState(Word* word, int maxSeconds);

    /** @brief Starts the session timer. */
    void startTimer();

    /** @brief Ends the session timer. */
    void endTimer();
    /**
	 * @brief Calculates the time elapsed since the game started.
	 * @return Elapsed time in seconds.
	 */
    int getElapsedTime() const;
    
    /**
      * @brief Converts the current word string to a displayable format for the GUI.
	  * @return QString representation of the current word.
	  */
	QString getCurrentWordDisplayText() const;
	
	/** @brief Reduces the number of remaining incorrect guesses by one. */
    void decreaseRemainingGuesses();  
	
	/**
     * @brief Determines if the game has been won.
	 * @return true if the word has been fully guessed, false otherwise.
	 */ 
    bool isGameWon() const;
    
    /**
	  * @brief Checks if the game session has ended (Win, Loss, or Timeout).
	  * @return true if the game is over, false if it is still active.
	  */
    bool isGameOver() const; 
    
    /** @return Pointer to the current Word object. */   
    Word* getCurrentWord() const;
    
    /** @return Number of remaining incorrect guesses allowed. */
    int getRemainingGuesses() const;
    
    /** @return Maximum time limit for the game session in seconds. */
    int getMaxTimeSeconds() const;
        

private:
    Word* m_currentWord;  ///< Pointer to the word being guessed.
	int m_maxTimeSeconds;  ///< Total time limit in seconds.
    int m_remainingGuesses; ///< Number of lives/guesses remaining.
    QDateTime m_dateTimeStart;  ///< Timestamp for when the game started.
    QDateTime m_dateTimeEnd;  ///< Timestamp for when the game ended.
};
#endif // GAMESTATE_H
