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

#include "WordRepositoryFile.h"
#include "WordManager.h"
#include "GameStateManager.h"
#include "PlayerManager.h"
#include "CategoryEnum.h"
#include "MainFlower.h"   
#include "HighScoreManager.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void handleLogin();
    void startNewGame(QString category);
    void processLetter();
    void goToScores();
    void logout();
    void backToCategoryMenu();
    void toggleUserMode();

private:
    void setupUI();
    void loadPlayers();
    void loadCurrentPlayer(const QString& playerName);
    void updateGameUI();
    void updateScoreTable();
    void resetAlphabetButtons();
    void saveData();

    void updateCategoryProgress();                
    void startNextWordInCategory(CategoryEnum);    

    QStackedWidget *stackedWidget;

    QString currentWord;
    QString hiddenWord;
    QString currentCategory;
    int wrongAttempts = 0;

    QLineEdit *nameInput;
    QRadioButton *newUserRadio, *oldUserRadio;
    QWidget *avatarSection;
    QButtonGroup *avatarGroup;

    QLabel *wordDisplay, *statusLabel, *categoryLabel, *playerAvatarLabel;                   
    QLabel *userLevelLabel;
    QTableWidget *scoreTable;
    QList<QPushButton*> alphabetButtons;
    QList<QPushButton*> categoryButtons;      

    QString getCategoryName(CategoryEnum cat);

    QWidget *currentUserPanel;   
    QLabel *userAvatarLabel;    
    QLabel *userNameLabel;  
    QLabel *userScoreLabel; 

    // player and data management
    Player* currentPlayer = nullptr;

    PlayerRepository* playerRepo;
    PlayerManager* playerManager;
    IWordRepository* wordRepo;
    WordManager* wordManager;
    GameStateManager* gameManager;
    GameStateRepository* stateRepo;
    HighScoreManager* highScoreManager;
    MainFlower* mainFlower;                     
};

#endif
