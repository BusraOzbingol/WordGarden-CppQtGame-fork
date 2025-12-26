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

#include "WordRepositoryFile.h"
#include "WordManager.h"
#include "GameStateManager.h"
#include "PlayerManager.h"
#include "CategoryEnum.h"

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
    QStackedWidget *stackedWidget;

    QString currentWord;
    QString hiddenWord;
    QString currentCategory;
    int wrongAttempts = 0;
    QLineEdit *nameInput;
    QRadioButton *newUserRadio, *oldUserRadio;
    QWidget *avatarSection;
    QButtonGroup *avatarGroup;
    QLabel *wordDisplay, *statusLabel, *categoryLabel;
    QTableWidget *scoreTable;
    QList<QPushButton*> alphabetButtons;
    QString getCategoryName(CategoryEnum cat);

    // Oyuncu ve Veri Yönetimi
    Player* currentPlayer = nullptr;


    PlayerRepository* playerRepo;
    PlayerManager* playerManager;
    IWordRepository* wordRepo;
    WordManager* wordManager;
    GameStateManager* gameManager;
    GameStateRepository* stateRepo;
};

#endif
