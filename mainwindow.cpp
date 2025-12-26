#include "mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QToolButton>
#include <QMessageBox>
#include <QHeaderView>
#include <QTimer>
#include <QCoreApplication>
#include <QFont>
#include <QGridLayout>
#include <QString>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    playerRepo = new PlayerRepository();
    playerManager = new PlayerManager(playerRepo);
    stateRepo = new GameStateRepository();
    wordRepo = new WordRepositoryFile("words.txt");
    wordManager = new WordManager(wordRepo);
    gameManager = new GameStateManager(stateRepo, wordManager);
    
    setWindowTitle("A Word Game of Hangman");
    resize(1536, 1024);
    this->setStyleSheet(
        "QMainWindow { background-color: #ffffff; }"
        "QWidget { background-color: #ffffff; color: #2c3e50; font-family: 'Segoe UI', Arial; }"
        "QPushButton { background-color: #f8f9fa; border: 1px solid #dee2e6; border-radius: 10px; }"
        "QPushButton:hover { background-color: #e9ecef; border: 1px solid #3498db; }"
        "QLineEdit { border: 2px solid #dee2e6; padding: 10px; border-radius: 8px; font-size: 16px; }");
    setupUI();
    loadPlayers();
    connect(qApp, &QCoreApplication::aboutToQuit,
            this, &MainWindow::saveData);
}



void MainWindow::setupUI() {
    stackedWidget = new QStackedWidget(this);
    setCentralWidget(stackedWidget);

    // --- SAYFA 1: GİRİŞ (LOGIN) ---
    QWidget *loginPage = new QWidget();
    QVBoxLayout *loginLayout = new QVBoxLayout(loginPage);
    loginLayout->setAlignment(Qt::AlignCenter);

    QLabel* title = new QLabel("WORDGARDEN");
    title->setStyleSheet("font-size: 55px; font-weight: bold; color: #2980b9; margin-bottom: 20px;");

    QHBoxLayout *radioLayout = new QHBoxLayout();
     radioLayout->setAlignment(Qt::AlignCenter);
    newUserRadio = new QRadioButton("New Player");
    oldUserRadio = new QRadioButton("Old Player");
    newUserRadio->setChecked(true);
    QString rStyle = "QRadioButton { font-size: 18px; font-weight: bold; color: #34495e; }"
                     "QRadioButton::indicator { width: 0px; } "
                     "QRadioButton:checked { color: #2980b9; }";
    newUserRadio->setStyleSheet(rStyle);
    oldUserRadio->setStyleSheet(rStyle);

    radioLayout->addWidget(newUserRadio);
    radioLayout->addSpacing(40);
    radioLayout->addWidget(oldUserRadio);
    connect(newUserRadio, &QRadioButton::toggled, this, &MainWindow::toggleUserMode);

    nameInput = new QLineEdit();
    nameInput->setPlaceholderText("Enter player name...");
    nameInput->setFixedWidth(400);
    nameInput->setFixedHeight(50);

    nameInput->setStyleSheet("background-color: white; color: black; font-size: 18px; border: 2px solid #3498db; border-radius: 8px; padding: 5px;");

    avatarSection = new QWidget();
    QVBoxLayout *avatarLayout = new QVBoxLayout(avatarSection);
    avatarLayout->addWidget(new QLabel("Select Avatar:"), 0, Qt::AlignCenter);

    QHBoxLayout *avatarRow = new QHBoxLayout();
    avatarGroup = new QButtonGroup(this);
    for(int i=0; i<4; ++i) {
        QToolButton *tb = new QToolButton();
        tb->setCheckable(true);
        tb->setFixedSize(110, 110);
        tb->setIcon(QIcon(QString(":/avatar%1.png").arg(i+1)));
        tb->setIconSize(QSize(95, 95));
        tb->setStyleSheet("QToolButton { border: 2px solid transparent; border-radius: 10px; }"
                          "QToolButton:checked { border: 4px solid #3498db; background-color: #ebf5fb; }");
        avatarGroup->addButton(tb, i);
        avatarRow->addWidget(tb);
    }
     avatarLayout->addLayout(avatarRow);

    QPushButton *loginBtn = new QPushButton("LOGIN");
    loginBtn->setFixedSize(380, 55);
    loginBtn->setStyleSheet("background-color: #3498db; color: white; font-weight: bold; font-size: 20px; border-radius: 10px;");
    connect(loginBtn, &QPushButton::clicked, this, &MainWindow::handleLogin);

    loginLayout->addStretch();
    loginLayout->addWidget(title, 0, Qt::AlignCenter);
    loginLayout->addWidget(nameInput, 0, Qt::AlignCenter);
    loginLayout->addLayout(radioLayout);
    loginLayout->addWidget(avatarSection, 0, Qt::AlignCenter);
    loginLayout->addWidget(loginBtn, 0, Qt::AlignCenter);
    loginLayout->addStretch();
    stackedWidget->addWidget(loginPage);

    //Page 2 Categories
    QWidget *catPage = new QWidget();
    QVBoxLayout *catLayout = new QVBoxLayout(catPage);
      catLayout->setContentsMargins(30, 20, 30, 20);
    QHBoxLayout *catTopBar = new QHBoxLayout();
    QPushButton *loBtn = new QPushButton("Logout");
    QPushButton *lbBtn = new QPushButton("Leaderboard");
    loBtn->setFixedSize(150, 50);
    lbBtn->setFixedSize(160, 50);
    QString topBtnStyle = "QPushButton { font-size: 14px; font-weight: bold; border-radius: 12px; }";
    loBtn->setStyleSheet(topBtnStyle);
    lbBtn->setStyleSheet(topBtnStyle);
    catTopBar->addWidget(loBtn); catTopBar->addStretch(); catTopBar->addWidget(lbBtn);
    catLayout->addLayout(catTopBar);
    catLayout->addStretch();

    QLabel *catHeader = new QLabel("SELECT CATEGORY");
    catHeader->setStyleSheet("font-size: 45px; font-weight: bold; color: #2c3e50; margin-bottom: 30px;");
    catLayout->addWidget(catHeader, 0, Qt::AlignCenter);
    QWidget* gridContainer = new QWidget();
    QGridLayout* categoryGrid = new QGridLayout(gridContainer);
    categoryGrid->setObjectName("categoryGrid");
    for (int i = 0; i < 6; ++i) {
        CategoryEnum currentCat = static_cast<CategoryEnum>(i);
        QString name = getCategoryName(currentCat);
        int guessedCount = 0;
        if (currentPlayer) {
            guessedCount = currentPlayer->getCompletedWords(currentCat).size();
        }
        int totalWords = 10;

         QString btnText = QString("%1\n%2/%3 COMPLETED").arg(name).arg(guessedCount).arg(totalWords);
         QPushButton *b = new QPushButton(btnText);

        b->setFixedSize(250, 180);
        b->setStyleSheet(
            "QPushButton {"
            "  background-color: #ffffff;"
            "  border: 2px solid #3498db;"
            "  border-radius: 20px;"
            "  font-size: 20px;"
            "  font-weight: bold;"
            "  color: #2c3e50;"
            "  text-align: bottom center;"
            "  padding-bottom: 10px;"
            "}"
            "QPushButton:hover {"
            "  background-color: #ebf5fb;"
            "  border-color: #2980b9;"
            "}"
            );

        connect(b, &QPushButton::clicked, [this, name](){
            this->startNewGame(name);
        });

        categoryGrid->addWidget(b, i / 2, i % 2);
    }
    catLayout->addWidget(gridContainer, 0, Qt::AlignCenter);
    catLayout->addStretch();


    stackedWidget->addWidget(catPage);

    connect(lbBtn, &QPushButton::clicked, this, &MainWindow::goToScores);
    connect(loBtn, &QPushButton::clicked, this, &MainWindow::logout);






    // 3: Game page
    QWidget *gamePage = new QWidget();
    QVBoxLayout *gameLayout = new QVBoxLayout(gamePage);

    QHBoxLayout *gameTop = new QHBoxLayout();
    QPushButton *gameBackBtn = new QPushButton("Back to Menu");
    gameBackBtn->setFixedSize(150,45);
    gameBackBtn->setStyleSheet("background-color: #e74c3c; color: white;");
    gameTop->addWidget(gameBackBtn); gameTop->addStretch();
    gameLayout->addLayout(gameTop);
    connect(gameBackBtn, &QPushButton::clicked, this, &MainWindow::backToCategoryMenu);

    categoryLabel = new QLabel("");
    categoryLabel->setAlignment(Qt::AlignCenter);
    categoryLabel->setStyleSheet("font-size: 16px; color: #7f8c8d;");
    wordDisplay = new QLabel("");
    wordDisplay->setAlignment(Qt::AlignCenter);
    wordDisplay->setStyleSheet("font-size: 80px; font-weight: bold; letter-spacing: 20px;");
    statusLabel = new QLabel("");
    statusLabel->setAlignment(Qt::AlignCenter);
    statusLabel->setMinimumWidth(650);
    statusLabel->setStyleSheet("font-size: 22px; font-weight: bold; background-color: #f8f9fa; border-radius: 15px; padding: 20px;");

    gameLayout->addWidget(categoryLabel);
    gameLayout->addStretch(1);

    gameLayout->addWidget(wordDisplay);
    gameLayout->addStretch(1);

    gameLayout->addWidget(statusLabel, 0, Qt::AlignCenter);
    gameLayout->addStretch(2);

   QGridLayout *keyGrid = new QGridLayout();
    QString letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for(int i=0; i<letters.length(); i++) {
        QPushButton *b = new QPushButton(QString(letters[i]));
        b->setFixedSize(60, 60);
        b->setStyleSheet("font-size: 20px; font-weight: bold;");
        alphabetButtons.append(b);
        keyGrid->addWidget(b, i/9, i%9);
        connect(b, &QPushButton::clicked, this, &MainWindow::processLetter);
    }
   gameLayout->addLayout(keyGrid);
    gameLayout->addSpacing(20);
    stackedWidget->addWidget(gamePage);

    // --- SAYFA 4: LEADERBOARD ---
    QWidget *scorePage = new QWidget();
    QVBoxLayout *scoreLayout = new QVBoxLayout(scorePage);
    scoreTable = new QTableWidget(0, 3, this);
    scoreTable->setHorizontalHeaderLabels({"Avatar", "Name", "Score"});
    scoreTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    scoreTable->setIconSize(QSize(120, 120));
    scoreTable->verticalHeader()->setDefaultSectionSize(140);
    scoreTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    QPushButton *scoreBack = new QPushButton("BACK TO MENU");
    scoreBack->setFixedSize(300, 60);
    scoreBack->setStyleSheet("background-color: #2c3e50; color: white; font-weight: bold; font-size: 18px; border-radius: 10px;");

    scoreLayout->addWidget(new QLabel("HALL OF FAME"), 0, Qt::AlignCenter);
    scoreLayout->addWidget(scoreTable);
    scoreLayout->addWidget(scoreBack, 0, Qt::AlignCenter);
    stackedWidget->addWidget(scorePage);
    connect(scoreBack, &QPushButton::clicked, this, &MainWindow::backToCategoryMenu);

}

QString MainWindow::getCategoryName(CategoryEnum cat) {
    switch(cat) {
    case CategoryEnum::Animals: return "Animals";
    case CategoryEnum::Plants:  return "Plants";
    case CategoryEnum::Technology: return "Technology";
    case CategoryEnum::Cities:  return "Cities";
    case CategoryEnum::Jobs:    return "Jobs";
    case CategoryEnum::Movies:    return "Movies";
    default: return "Unspecified";
    }
}

void MainWindow::handleLogin() {
    QString name = nameInput->text().trimmed().toUpper();
    if(name.isEmpty()) return;

    if(newUserRadio->isChecked()) {
        currentPlayer = playerManager->createPlayer(name, PlayerLevel::Beginner);
       currentPlayer->setAvatarId(avatarGroup->checkedId());

    } else {
        currentPlayer = playerManager->getPlayer(name);
        loadCurrentPlayer(name);
        if(!currentPlayer) { QMessageBox::warning(this, "Error", "Player not found!"); return; }
    }
    stackedWidget->setCurrentIndex(1);

}

void MainWindow::processLetter() {
    QPushButton *btn = qobject_cast<QPushButton*>(sender());
    if(!btn) return;
    QChar L = btn->text()[0];
    btn->setEnabled(false);
    gameManager->makeGuess(L);


    if(wordManager->getCurrentWord()->guessLetter(L.toLatin1())) {
        btn->setStyleSheet("background-color: #2ecc71; color: white; font-size: 20px; font-weight: bold;");
        currentPlayer->increaseScoreForCorrectGuess(); // +5 puan

    } else {
        btn->setStyleSheet("background-color: #e74c3c; color: white; font-size: 20px; font-weight: bold;");
        currentPlayer->decreaseScoreForIncorrectGuess(); // -2 puan
    }

    updateGameUI();

    if(gameManager->getCurrentGameState()->isGameOver()) {
        Word* currentWord = wordManager->getCurrentWord();
        if (currentWord && currentWord->isGuessed()) {
            QString wordStr = QString::fromStdString(currentWord->getWord());
            currentPlayer->addCompletedWord(currentWord->getCategory(), wordStr);



        }
        QTimer::singleShot(2000, this, &MainWindow::backToCategoryMenu);
    }
}

void MainWindow::updateGameUI() {
    if(!gameManager->getCurrentGameState()) return;
    QString masked = QString::fromStdString(wordManager->getMaskedWord());
    wordDisplay->setText(masked.split("").join(" "));
    statusLabel->setText(QString("SCORE: %1 | MISSES: %2")
                             .arg(currentPlayer->getScore())
                             .arg(gameManager->getCurrentGameState()->getRemainingGuesses()));
}

void MainWindow::updateScoreTable() {
    scoreTable->setRowCount(0);
    QList<Player*> players = playerRepo->getAllPlayers();
    for(Player* p : players) {
        int r = scoreTable->rowCount();
        scoreTable->insertRow(r);
        QLabel *img = new QLabel();
        int avId = p->getAvatarId();
        img->setPixmap(QIcon(QString(":/avatar%1.png").arg(avId + 1)).pixmap(50, 50));
        img->setAlignment(Qt::AlignCenter);
        scoreTable->setCellWidget(r, 0, img);
        scoreTable->setItem(r, 1, new QTableWidgetItem(p->getName()));
        scoreTable->setItem(r, 2, new QTableWidgetItem(QString::number(p->getScore())));
    }
    scoreTable->sortItems(2, Qt::DescendingOrder);
}
// LOAD AND SAVE
void MainWindow::loadPlayers() {
    QSettings settings("MyCompany", "WordGarden");
    settings.beginGroup("Players");

    QStringList playerNames = settings.childGroups();
    for (const QString &name : playerNames) {
        Player* p = new Player(name, PlayerLevel::Beginner);
        p->setScore(settings.value(name + "/score", 0).toInt());
        p->setAvatarId(settings.value(name + "/avatar", 0).toInt());
        playerRepo->addPlayer(p); // repo now holds all players
    }

    settings.endGroup();
}
void MainWindow::loadCurrentPlayer(const QString& playerName) {
    Player* p = playerRepo->getPlayerByName(playerName);
    if (!p) return; // safety check

    currentPlayer = p;

    QSettings settings("MyCompany", "WordGarden");
    settings.beginGroup("Players");
    settings.beginGroup(playerName);

    // Basic info
    currentPlayer->setScore(settings.value("score", 0).toInt());
    currentPlayer->setLevel(static_cast<PlayerLevel>(settings.value("level", 0).toInt()));
    currentPlayer->setAvatarId(settings.value("avatar", 0).toInt());
    currentPlayer->setLastGameTime(settings.value("lastTime", 0).toInt());

    // Completed words per category
    settings.beginGroup("CompletedWords");
    for (int i = 0; i < 6; ++i) {
        CategoryEnum cat = static_cast<CategoryEnum>(i);
        QStringList words = settings.value(QString::number(i), QStringList()).toStringList();
        for (const QString& w : words) {
            currentPlayer->addCompletedWord(cat, w);
        }
    }
    settings.endGroup(); // CompletedWords
    settings.endGroup(); // playerName
    settings.endGroup(); // Players
}

void MainWindow::saveData() {
    QSettings settings("MyCompany", "WordGarden");
    settings.beginGroup("Players");
    QList<Player*> players = playerRepo->getAllPlayers();
    for (Player* p : players) {
        settings.beginGroup(p->getName());
        settings.setValue("level", static_cast<int>(p->getLevel()));
        settings.setValue("score", p->getScore());
        settings.setValue("avatar", p->getAvatarId());
        settings.setValue("lastTime", p->getLastGameTime());
        settings.beginGroup("CompletedWords");
        for (int i = 0; i < 6; ++i) {
            CategoryEnum cat = static_cast<CategoryEnum>(i);
            QStringList words = p->getCompletedWords(cat);
            settings.setValue(QString::number(i), words);
        }
        settings.endGroup(); //keep track of progress

        settings.endGroup(); //keep track of player infos
    }

    settings.endGroup();

}


// YARDIMCI FONKSİYONLAR
void MainWindow::startNewGame(QString category) {
    gameManager->startNewGame(category);
    categoryLabel->setText("CATEGORY: " + category.toUpper());
    resetAlphabetButtons();
    updateGameUI();
    stackedWidget->setCurrentIndex(2);
}
void MainWindow::resetAlphabetButtons() {
    for(QPushButton* b : alphabetButtons) {
        b->setEnabled(true);
        b->setStyleSheet("font-size: 20px; font-weight: bold; color: #2c3e50; background-color: #fdfdfd; border: 1px solid #ccc;");
    }
}
void MainWindow::goToScores() { updateScoreTable(); stackedWidget->setCurrentIndex(3); }
void MainWindow::backToCategoryMenu() { stackedWidget->setCurrentIndex(1); }
void MainWindow::logout() { nameInput->clear(); stackedWidget->setCurrentIndex(0); }
void MainWindow::toggleUserMode() { avatarSection->setVisible(newUserRadio->isChecked()); }
MainWindow::~MainWindow() {}

