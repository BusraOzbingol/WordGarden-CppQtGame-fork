/**
 * @file GameStateManager.cpp
 * @brief Implementation of the GameStateManager class.
 * * This class coordinates between the WordManager and GameState to control 
 * the overall flow of the gameplay.
 */

#include "GameStateManager.h"
#include <QDebug>

/**
 * @brief Constructs the GameStateManager and attempts to load the last saved session.
 * @param repository Pointer to the GameStateRepository for data persistence.
 * @param wordManager Pointer to the WordManager for word and scoring logic.
 */
GameStateManager::GameStateManager(GameStateRepository* repository, WordManager* wordManager)
    : m_repository(repository), m_wordManager(wordManager), m_currentGameState(nullptr) {
    loadLastGame();
}

/**
 * @brief Cleans up resources used by the GameStateManager.
 */
GameStateManager::~GameStateManager() {
    // Memory management: delete m_currentGameState; could be added here if needed
}

/**
 * @brief Initializes a new game session with a word from the specified category.
 * @param categoryName The name of the word category as a QString.
 */
void GameStateManager::startNewGame(QString categoryName) {
    // Transition from Qt QString to standard C++ string for backend logic
    m_wordManager->startNewGame(categoryName.toStdString());
    Word* selectedWord = m_wordManager->getCurrentWord();

    if (selectedWord == nullptr) {
        qDebug() << "Error: Word could not be selected.";
        return;
    }

    // Create a new game state with a 180-second time limit
    m_currentGameState = new GameState(selectedWord, 180);
    m_currentGameState->startTimer();
}

/**
 * @brief Processes a letter guess and updates game progress.
 * @param letter The character guessed by the player as a QChar.
 */
void GameStateManager::makeGuess(QChar letter) {
    if (!m_currentGameState || !m_wordManager) return;

    // Send the guess to WordManager (converted to char)
    bool correct = m_wordManager->makeGuess(letter.toLatin1());

    // Decrease life in GameState if the guess was incorrect
    if (!correct) {
        m_currentGameState->decreaseRemainingGuesses();
    }

    // Notify WordManager if the session is successfully won
    if (m_currentGameState->isGameWon()) {
        m_wordManager->onGameWon();
    }

    // Automatically save progress if the game reaches a terminal state
    if (m_currentGameState->isGameOver()) {
        saveCurrentGame();
    }
}

/**
 * @brief Saves the current active game state to the repository.
 */
void GameStateManager::saveCurrentGame() {
    if (m_currentGameState && !m_currentGameState->isGameOver()) {
        m_repository->saveGameState(m_currentGameState);
    }
}

/**
 * @brief Loads the most recently saved game session from the repository.
 */
void GameStateManager::loadLastGame() {
    GameState* lastGame = m_repository->getLastGameState();
    if (lastGame) {
        m_currentGameState = lastGame;
    }
}

/**
 * @brief Retrieves the current active game state.
 * @return Pointer to the current GameState object.
 */
GameState* GameStateManager::getCurrentGameState() const {
    return m_currentGameState;
}
