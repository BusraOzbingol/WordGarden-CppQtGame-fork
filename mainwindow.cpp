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

    // --- PAGE 1: LOGIN ---
    QWidget *loginPage = new QWidget();

    // add login background
    QLabel *loginBg = new QLabel(loginPage);
    loginBg->setPixmap(QPixmap(":/login_bg.png"));
    loginBg->setScaledContents(true);
    loginBg->setGeometry(0, 0, 1536, 1024);
    loginBg->lower();

    QVBoxLayout *loginLayout = new QVBoxLayout(loginPage);
    loginLayout->setAlignment(Qt::AlignTop | Qt::AlignHCenter);
    loginLayout->setContentsMargins(0, 0, 0, 0);

    // top space fixing
    loginLayout->addSpacing(400);

    nameInput = new QLineEdit();
    nameInput->setPlaceholderText("Enter player name...");
    nameInput->setFixedSize(400, 50);
    nameInput->setStyleSheet("background-color: white; color: black; font-size: 18px; "
                             "border: 2px solid #3498db; border-radius: 8px; padding: 5px;");
    loginLayout->addWidget(nameInput, 0, Qt::AlignCenter);

    loginLayout->addSpacing(20);

    // radio button
    QHBoxLayout *radioLayout = new QHBoxLayout();
    radioLayout->setAlignment(Qt::AlignCenter);
    newUserRadio = new QRadioButton("New Player");
    oldUserRadio = new QRadioButton("Old Player");
    newUserRadio->setChecked(true);

    QString rStyle = "QRadioButton { font-size: 20px; font-weight: bold; color: black; background: transparent; spacing: 10px; }"
                     "QRadioButton::indicator { width: 22px; height: 22px; border: 2px solid black; border-radius: 12px; background: white; }"
                     "QRadioButton::indicator:checked { background: #3498db; border: 2px solid #3498db; }"
                     "QRadioButton:checked { color: #3498db; text-decoration: underline; }";

    newUserRadio->setStyleSheet(rStyle);
    oldUserRadio->setStyleSheet(rStyle);
    radioLayout->addWidget(newUserRadio);
    radioLayout->addSpacing(40);
    radioLayout->addWidget(oldUserRadio);
    loginLayout->addLayout(radioLayout);

    connect(newUserRadio, &QRadioButton::toggled, this, &MainWindow::toggleUserMode);

    loginLayout->addSpacing(20);

    // select the avatar
    avatarSection = new QWidget();
    avatarSection->setStyleSheet("background: transparent; border: none;"); 
    QVBoxLayout *avatarLayout = new QVBoxLayout(avatarSection);

    QLabel* avatarLabel = new QLabel("Select Avatar:");
    avatarLabel->setStyleSheet("color: black; font-weight: bold; font-size: 25px; background: transparent;");
    avatarLayout->addWidget(avatarLabel, 0, Qt::AlignCenter);

    QHBoxLayout *avatarRow = new QHBoxLayout();
    avatarGroup = new QButtonGroup(this);
    for(int i=0; i<4; ++i) {
        QToolButton *tb = new QToolButton();
        tb->setCheckable(true);
        tb->setFixedSize(110, 110);
        tb->setIcon(QIcon(QString(":/avatar%1.png").arg(i+1)));
        tb->setIconSize(QSize(110, 110));
        tb->setStyleSheet("QToolButton { border: 2px solid transparent; border-radius: 55px; background: transparent; }"
                          "QToolButton:checked { border: 5px solid #3498db; background: rgba(52, 152, 219, 25); }");
        avatarGroup->addButton(tb, i);
        avatarRow->addWidget(tb);
    }
    avatarLayout->addLayout(avatarRow);
    loginLayout->addWidget(avatarSection, 0, Qt::AlignCenter);

    // login button
    QPushButton *loginBtn = new QPushButton("LOGIN");
    loginBtn->setFixedSize(380, 55);
    loginBtn->setStyleSheet("background-color: #3498db; color: white; font-weight: bold; font-size: 20px; border-radius: 10px;");
    connect(loginBtn, &QPushButton::clicked, this, &MainWindow::handleLogin);
    loginLayout->addWidget(loginBtn, 0, Qt::AlignCenter);

    // flexibility
    loginLayout->addStretch(1);
    
    stackedWidget->addWidget(loginPage);

     // --- PAGE 2: CATEGORIES ---
    QWidget *catPage = new QWidget();

    // add category background
    QLabel *catBg = new QLabel(catPage);
    catBg->setPixmap(QPixmap(":/category_bg.png"));
    catBg->setScaledContents(true);
    catBg->setGeometry(0, 0, 1536, 1024); 
    catBg->lower(); 

    QVBoxLayout *catLayout = new QVBoxLayout(catPage);
    catLayout->setContentsMargins(30, 20, 30, 20);

    // Üst Bar
    QHBoxLayout *catTopBar = new QHBoxLayout();
    QPushButton *loBtn = new QPushButton("Logout");
    QPushButton *lbBtn = new QPushButton("Leaderboard");
    loBtn->setFixedSize(150, 50);
    lbBtn->setFixedSize(160, 50);

    QString topBtnStyle = "QPushButton { font-size: 14px; font-weight: bold; border-radius: 12px; background-color: rgba(236, 240, 241, 200); color: #2c3e50; border: 1px solid #bdc3c7; }"
                          "QPushButton:hover { background-color: #bdc3c7; }";
    loBtn->setStyleSheet(topBtnStyle);
    lbBtn->setStyleSheet(topBtnStyle);

    catTopBar->addWidget(loBtn);
    catTopBar->addStretch();
    catTopBar->addWidget(lbBtn);
    catLayout->addLayout(catTopBar);
    catLayout->addStretch();

    // text select category
    QLabel *catHeader = new QLabel("SELECT CATEGORY");
    catHeader->setStyleSheet("font-size: 45px; font-weight: bold; color: #2c3e50; background: transparent; margin-bottom: 30px;");
    catLayout->addWidget(catHeader, 0, Qt::AlignCenter);

    // category grid
    QWidget* gridContainer = new QWidget();
    gridContainer->setStyleSheet("background: transparent;"); 
    gridContainer->setMaximumWidth(1100);

    QGridLayout* categoryGrid = new QGridLayout(gridContainer);
    categoryGrid->setSpacing(30);

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

        b->setIcon(QIcon(QString(":/icon%1.png").arg(i + 1)));
        b->setIconSize(QSize(85, 85));

        b->setFixedSize(400, 150);

        b->setStyleSheet(
            "QPushButton {"
            "  background-color: rgba(255, 255, 255, 230);" 
            "  border: 3px solid #3498db;"
            "  border-radius: 20px;"
            "  font-size: 20px;"
            "  font-weight: bold;"
            "  color: #2c3e50;"
            "  text-align: center;"
            "  padding: 10px;"
            "}"
            "QPushButton:hover {"
            "  background-color: #d6eaf8;"
            "  border-color: #2980b9;"
            "  border-width: 3px;"
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


    // --- PAGE 3: GAME PAGE---
    QWidget *gamePage = new QWidget();
    mainFlower = new MainFlower(gamePage);
    mainFlower->setGeometry(0, 0, 1536, 1024);
    mainFlower->lower();

    QVBoxLayout *gameLayout = new QVBoxLayout(gamePage);
    gameLayout->setContentsMargins(50, 20, 50, 20);
    gameLayout->setSpacing(5);

    // top bar
    QHBoxLayout *gameTop = new QHBoxLayout();
    gameTop->setContentsMargins(0, 10, 0, 0);

    QPushButton *gameBackBtn = new QPushButton("Back to Menu");
    gameBackBtn->setFixedSize(160, 45);
    gameBackBtn->setStyleSheet("background-color: #e74c3c; color: white; font-weight: bold; border-radius: 10px;");
    connect(gameBackBtn, &QPushButton::clicked, this, &MainWindow::backToCategoryMenu);
    gameTop->addWidget(gameBackBtn);

    gameTop->addStretch();

    categoryLabel = new QLabel("");
    categoryLabel->setAlignment(Qt::AlignCenter);
    categoryLabel->setStyleSheet(
        "font-size: 24px; font-weight: bold; color: #2c3e50; "
        "background: rgba(255, 255, 255, 120); padding: 8px 30px; border-radius: 12px;"
        );
    gameTop->addWidget(categoryLabel);

    gameTop->addStretch();
    gameTop->addSpacing(160);

    gameLayout->addLayout(gameTop);
    gameLayout->addStretch(10);

    wordDisplay = new QLabel("");
    wordDisplay->setAlignment(Qt::AlignCenter);
    wordDisplay->setStyleSheet(
        "font-size: 75px; font-weight: bold; letter-spacing: 20px; "
        "background-color: transparent; color: #2c3e50;"
        );
    gameLayout->addWidget(wordDisplay);

    gameLayout->addSpacing(10);

    statusLabel = new QLabel("");
    statusLabel->setAlignment(Qt::AlignCenter);
    statusLabel->setFixedSize(600, 65);
    statusLabel->setStyleSheet(
        "font-size: 20px; font-weight: bold; color: #34495e; "
        "background-color: rgba(255, 255, 255, 150); border-radius: 15px;"
        );
    gameLayout->addWidget(statusLabel, 0, Qt::AlignCenter);

    gameLayout->addSpacing(20);

    // keyboard
    QWidget *keyboardContainer = new QWidget();
    keyboardContainer->setStyleSheet("background: transparent;");
    QGridLayout *keyGrid = new QGridLayout(keyboardContainer);
    keyGrid->setSpacing(10);
    keyGrid->setContentsMargins(100, 0, 100, 0);

    QString letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for(int i = 0; i < letters.length(); i++) {
        QPushButton *b = new QPushButton(QString(letters[i]));
        b->setFixedSize(60, 60);
        b->setStyleSheet(
            "QPushButton { background-color: rgba(255, 255, 255, 200); border: 1px solid #2c3e50; "
            "border-radius: 10px; font-size: 18px; font-weight: bold; } "
            "QPushButton:hover { background-color: white; }"
            );
        alphabetButtons.append(b);
        keyGrid->addWidget(b, i / 13, i % 13);
        connect(b, &QPushButton::clicked, this, &MainWindow::processLetter);
    }

    gameLayout->addWidget(keyboardContainer, 0, Qt::AlignCenter);
    gameLayout->addStretch(1);

    stackedWidget->addWidget(gamePage);

    
    // --- PAGE 4: LEADERBOARD ---
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
     updateCategoryProgress();
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
             updateCategoryProgress();
        }
        QTimer::singleShot(2000, this, &MainWindow::backToCategoryMenu);
    }
    // The error count goes to mainFlower
    if(mainFlower) {
        int remaining = wordManager->getRemainingGuesses();
        mainFlower->setLeafCount(remaining);
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

void MainWindow::updateCategoryProgress() {

    for (int i = 0; i < 6; ++i) {
        CategoryEnum cat = static_cast<CategoryEnum>(i);
        QPushButton* b = categoryButtons[i]; // store your buttons in a QList<QPushButton*> when creating them
        int completed = currentPlayer ? currentPlayer->getCompletedWords(cat).size() : 0;
        int totalWords = 10;
        QString name = getCategoryName(cat);
        b->setText(QString("%1\n%2/%3 COMPLETED").arg(name).arg(completed).arg(totalWords));
    }
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
            updateCategoryProgress();
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













