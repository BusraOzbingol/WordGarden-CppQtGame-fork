/**
 * @file mainwindow.h
 * @brief Header file for the primary application window.
 * * This file defines the MainWindow class, which manages the application's UI states,
 * user authentication, gameplay logic coordination, and data persistence.
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QLineEdit>
#include <QLabel>
#include <QTableWidget>
#include <QPushButton>
#include <QRadioButton>
#include <QButtonGroup>
#include <QGridLayout>
#include <QSettings>
#include <QHeaderView>
#include <QTimer>
#include <QList>
#include <QTableWidgetItem>
#include <QVBoxLayout>

#include "2_Repository/WordRepositoryFile.h"
#include "3_Manager/WordManager.h"
#include "3_Manager/GameStateManager.h"
#include "3_Manager/PlayerManager.h"
#include "0_Enums/CategoryEnum.h"
#include "4_Ui/mainFlower.h"
#include "3_Manager/HighScoreManager.h"

/**
 * @class MainWindow
 * @brief The central controller and UI manager for the application.
 * * MainWindow handles the QStackedWidget to switch between Login, Category Selection,
 * Gameplay, and High Score screens. It coordinates between various Manager classes
 * to handle game logic and player data.
 */
class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    /**
     * @brief Constructs the MainWindow and initializes managers and UI.
     * @param parent Pointer to the parent widget (default is nullptr).
     */
    MainWindow(QWidget *parent = nullptr);

    /**
     * @brief Destructor that ensures data is saved before closing.
     */
    ~MainWindow();

private slots:
    /** @brief Validates user input and logs the player into the system. */
    void handleLogin();

    /** * @brief Initializes a new game session for a specific category.
     * @param category The string representation of the selected category.
     */
    void startNewGame(QString category);

    /** @brief Processes the letter from the clicked alphabet button. */
    void processLetter();

    /** @brief Switches the view to the High Scores table. */
    void goToScores();

    /** @brief Logs out the current player and returns to the login screen. */
    void logout();

    /** @brief Navigates back to the category selection menu. */
    void backToCategoryMenu();

    /** @brief Toggles UI elements based on New User or Returning User selection. */
    void toggleUserMode();

private:
    /** @brief Initializes all UI components and the QStackedWidget. */
    void setupUI();

    /** @brief Loads the list of registered players from the repository. */
    void loadPlayers();

    /** @brief Loads data for a specific player by name. */
    void loadCurrentPlayer(const QString& playerName);

    /** @brief Refreshes the gameplay UI (word display, attempts, flower stage). */
    void updateGameUI();

    /** @brief Updates the high score table with the latest data. */
    void updateScoreTable();

    /** @brief Resets all alphabet buttons to their enabled/initial state. */
    void resetAlphabetButtons();

    /** @brief Persists player and game progress to storage. */
    void saveData();

    /** @brief Updates progress tracking for the active category. */
    void updateCategoryProgress();

    /** @brief Fetches and starts the next available word in a category. */
    void startNextWordInCategory(CategoryEnum);

    // UI Layout Management
    QStackedWidget *stackedWidget; ///< Container for switching between different screens.

    // Game Logic State
    QString currentWord;     ///< The target word the player is trying to guess.
    QString hiddenWord;      ///< The masked version of the word (e.g., "_ _ A _").
    QString currentCategory; ///< The name of the currently active category.
    int wrongAttempts = 0;   ///< Counter for incorrect letter guesses.

    // Login Screen Components
    QLineEdit *nameInput;
    QRadioButton *newUserRadio, *oldUserRadio;
    QWidget *avatarSection;
    QButtonGroup *avatarGroup;

    // Gameplay UI Components
    QLabel *wordDisplay, *statusLabel, *categoryLabel, *playerAvatarLabel;
    QLabel *userLevelLabel; ///< Displays the player's current level/rank.

    // Collection Components
    QTableWidget *scoreTable;
    QList<QPushButton*> alphabetButtons;
    QList<QPushButton*> categoryButtons;

    /** * @brief Helper to convert CategoryEnum to a displayable string.
     * @param cat The category enumeration value.
     * @return QString The string name of the category.
     */
    QString getCategoryName(CategoryEnum cat);

    // Current User Info Panel
    QWidget *currentUserPanel;
    QLabel *userAvatarLabel;
    QLabel *userNameLabel;
    QLabel *userScoreLabel;

    // Player and Data Management
    Player* currentPlayer = nullptr;   ///< Pointer to the currently logged-in player.

    // Manager and Repository Pointers
    PlayerRepository* playerRepo;      ///< Repository for player persistence.
    PlayerManager* playerManager;      ///< Logic for player-related operations.
    IWordRepository* wordRepo;         ///< Repository for word data.
    WordManager* wordManager;          ///< Logic for word selection and validation.
    GameStateManager* gameManager;     ///< Logic for managing active game sessions.
    GameStateRepository* stateRepo;    ///< Repository for saving/loading game states.
    HighScoreManager* highScoreManager;///< Logic for ranking and scores.
    MainFlower* mainFlower;            ///< Custom widget for visual growth feedback.
};

#endif // MAINWINDOW_H
