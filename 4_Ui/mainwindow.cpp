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
    highScoreManager = new HighScoreManager(playerRepo);
    
    setWindowTitle("WORDGARDEN");
    resize(1536, 1024);
    this->setStyleSheet(
        "QMainWindow { background-color: #ffffff; }"
        "QWidget { background-color: #ffffff; color: #2c3e50; font-family: 'Segoe UI', Arial; }"
        "QPushButton { background-color: #f8f9fa; border: 1px solid #dee2e6; border-radius: 10px; }"
        "QPushButton:hover { background-color: #e9ecef; border: 1px solid #3498db; }"
        "QLineEdit { border: 2px solid #dee2e6; padding: 10px; border-radius: 8px; font-size: 16px; }");
    setupUI();
    playerRepo->clear();
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

    // Top Bar
    QHBoxLayout *catTopBar = new QHBoxLayout();
    QPushButton *loBtn = new QPushButton("Logout");
    QPushButton *lbBtn = new QPushButton("Leaderboard");
    loBtn->setFixedSize(150, 50);
    lbBtn->setFixedSize(160, 50);

    QString topBtnStyle = "QPushButton { font-size: 14px; font-weight: bold; border-radius: 12px; background-color: rgba(236, 240, 241, 200); color: #2c3e50; border: 1px solid #bdc3c7; }"
                          "QPushButton:hover { background-color: #bdc3c7; }";
    loBtn->setStyleSheet(topBtnStyle);
    lbBtn->setStyleSheet(topBtnStyle);

    playerAvatarLabel = new QLabel(catPage);
    playerAvatarLabel->setAlignment(Qt::AlignCenter);
    playerAvatarLabel->setFixedSize(120, 120);
    playerAvatarLabel->setStyleSheet("border-radius: 60px; background: transparent;");

    catTopBar->addWidget(playerAvatarLabel);
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
        categoryButtons.append(b);

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
    gameTop->addWidget(gameBackBtn);
    connect(gameBackBtn, &QPushButton::clicked, this, &MainWindow::backToCategoryMenu);
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

    QLabel *scoreBg = new QLabel(scorePage);
    scoreBg->setPixmap(QPixmap(":/category_bg.png"));
    scoreBg->setScaledContents(true);
    scoreBg->setGeometry(0, 0, 1536, 1024);
    scoreBg->lower();

    QVBoxLayout *scoreLayout = new QVBoxLayout(scorePage);
    scoreLayout->setContentsMargins(50, 20, 50, 20);
    scoreLayout->setSpacing(15);

    // Top bar
    QHBoxLayout *scoreTop = new QHBoxLayout();
    scoreTop->setContentsMargins(0, 10, 0, 10);

    QPushButton *scoreBackBtn = new QPushButton("Back to Menu");
    scoreBackBtn->setFixedSize(160, 45);
    scoreBackBtn->setStyleSheet("background-color: #e74c3c; color: white; font-weight: bold; border-radius: 10px;");
    scoreTop->addWidget(scoreBackBtn);
    connect(scoreBackBtn, &QPushButton::clicked, this, &MainWindow::backToCategoryMenu);

    scoreTop->addStretch();
    QLabel *hallOfFameLabel = new QLabel("HALL OF FAME");
    hallOfFameLabel->setAlignment(Qt::AlignCenter);
    hallOfFameLabel->setStyleSheet("font-size: 24px; font-weight: bold; color: #2c3e50; background: rgba(255, 255, 255, 120); padding: 8px 30px; border-radius: 12px;");
    scoreTop->addWidget(hallOfFameLabel);
    scoreTop->addStretch();
    scoreTop->addSpacing(160);
    scoreLayout->addLayout(scoreTop);

    // user panel
    currentUserPanel = new QWidget();
    currentUserPanel->setFixedHeight(110);
    currentUserPanel->setStyleSheet(
        "QWidget {"
        "  background-color: rgba(255, 255, 255, 230);"
        "  border: 3px solid #3498db;"
        "  border-radius: 20px;"
        "}"
        );
    QHBoxLayout *userPanelLayout = new QHBoxLayout(currentUserPanel);
    userPanelLayout->setContentsMargins(30, 0, 30, 0);

    userAvatarLabel = new QLabel();
    userAvatarLabel->setFixedSize(75, 75);

    userAvatarLabel->setStyleSheet("border-radius: 37px; border: 3px solid #3498db; background: white;");
    userAvatarLabel->setScaledContents(true);
    userPanelLayout->addWidget(userAvatarLabel);

    userPanelLayout->addStretch();

    // the current username in bold
    userNameLabel = new QLabel();
    userNameLabel->setStyleSheet("font-size: 28px; font-weight: 900; color: #2c3e50; border: none; background: transparent;");
    userPanelLayout->addWidget(userNameLabel);

    userPanelLayout->addStretch();

    // the current score in bold
    userScoreLabel = new QLabel();
    userScoreLabel->setStyleSheet("font-size: 24px; font-weight: 900; color: #3498db; border: none; background: transparent;");
    userPanelLayout->addWidget(userScoreLabel);

    scoreLayout->addWidget(currentUserPanel);

    // no changes can be made to the table
    scoreTable = new QTableWidget(0, 3, this);
    scoreTable->setHorizontalHeaderLabels({"Avatar", "Name", "Score"});
    scoreTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    scoreTable->setIconSize(QSize(100, 100));
    scoreTable->verticalHeader()->setDefaultSectionSize(135);
    scoreTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // headlines are not clickable
    scoreTable->horizontalHeader()->setSectionsClickable(false);

    scoreTable->setSelectionMode(QAbstractItemView::NoSelection);
    scoreTable->setFocusPolicy(Qt::NoFocus);

    // score table
    scoreTable->setStyleSheet(
        "QTableWidget {"
        "   background-color: rgba(255, 255, 255, 200);"
        "   color: #2c3e50;"
        "   border: 3px solid #3498db;"
        "   border-radius: 20px;"
        "   font-size: 18px;"
        "   font-weight: bold;"
        "}"
        "QHeaderView::section {"
        "   background-color: #3498db;"
        "   color: white;"
        "   font-weight: bold;"
        "   font-size: 18px;"
        "   border: none;"
        "   height: 45px;"
        "}"
        );
    scoreTable->viewport()->setAttribute(Qt::WA_TranslucentBackground);
    scoreTable->viewport()->setStyleSheet("background: transparent;");

    scoreLayout->addWidget(scoreTable);
    stackedWidget->addWidget(scorePage);
    
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
        if (playerManager->getPlayer(name)) {
            QMessageBox::warning(this, "Error", "This player name is already taken!");
            return;
        }
        currentPlayer = playerManager->createPlayer(name, PlayerLevel::Beginner);
        currentPlayer->setAvatarId(avatarGroup->checkedId());

    } else {
        currentPlayer = playerManager->getPlayer(name);
        if(!currentPlayer) { QMessageBox::warning(this, "Error", "Player not found!"); return; }
        loadCurrentPlayer(name);
    }
    int avatarId = currentPlayer->getAvatarId();

    QString avatarPath = QString(":/avatar%1.png").arg(avatarId + 1);
    playerAvatarLabel->setPixmap(QPixmap(avatarPath).scaled(120, 120, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    stackedWidget->setCurrentIndex(1);
    updateCategoryProgress();
}

// new update from berrak
// updated
void MainWindow::processLetter() {
    QPushButton *btn = qobject_cast<QPushButton*>(sender());
    if(!btn) return;

    QChar L = btn->text()[0];
    btn->setEnabled(false);
    Word* currentWord = wordManager->getCurrentWord();
    if(!currentWord) return;

    // estimation process
    bool correct = wordManager->makeGuess(L.toLatin1());

    if(correct) {
        btn->setStyleSheet("background-color: #2ecc71; color: white; font-size: 20px; font-weight: bold;");
        currentPlayer->increaseScoreForCorrectGuess();
    } else {
        btn->setStyleSheet("background-color: #e74c3c; color: white; font-size: 20px; font-weight: bold;");
        currentPlayer->decreaseScoreForIncorrectGuess();

        GameState* gs = gameManager->getCurrentGameState();
        if(gs) {
            gs->decreaseRemainingGuesses();
        }
    }

    updateGameUI();
    GameState* gs = gameManager->getCurrentGameState();

    if(gs && gs->isGameOver()) {
        // the current category name has been moved to a secure location
        CategoryEnum currentCatEnum = currentWord->getCategory();
        QString currentCatName = getCategoryName(currentCatEnum);

        if(currentWord->isGuessed()) {
            // when word known
            QString wordStr = QString::fromStdString(currentWord->getWord());
            currentPlayer->addCompletedWord(currentCatEnum, wordStr);
            wordManager->onGameWon();
        }

        updateCategoryProgress();

        // wait 2 second
        // startNewGame function directly with currenCatName
        QTimer::singleShot(2000, this, [this, currentCatEnum, currentCatName]() {
            int completed = currentPlayer->getCompletedWords(currentCatEnum).size();
            int totalWords = 10; // Senin limitin

            if(completed >= totalWords) {
                // if all words in the category are exhausted
                backToCategoryMenu();
                QMessageBox::information(this, "Category Complete", currentCatName + " category finished!");
            } else {
                // if the words have not run out
                this->startNewGame(currentCatName);
            }
        });
    }

    if(mainFlower && gs) {
        mainFlower->setLeafCount(gs->getRemainingGuesses());
    }
}

void MainWindow::updateGameUI() {
    GameState* gs = gameManager->getCurrentGameState();
    if(!gs) return;

    QString masked = QString::fromStdString(wordManager->getMaskedWord());
    wordDisplay->setText(masked.split("").join(" "));
    statusLabel->setText(QString("SCORE: %1 | MISSES: %2")
                             .arg(currentPlayer->getScore())
                             .arg(gs->getRemainingGuesses()));
}

// updated from Berrak
void MainWindow::updateScoreTable() {
    if (!currentPlayer) return;

    // update avatar and information at the top
    int avId = currentPlayer->getAvatarId();
    userAvatarLabel->setPixmap(QPixmap(QString(":/avatar%1.png").arg(avId + 1)));
    userNameLabel->setText(currentPlayer->getName());
    userScoreLabel->setText("SCORE: " + QString::number(currentPlayer->getScore()));

    // all players are listed
    int totalPlayerCount = playerRepo->getAllPlayers().size();
    QList<Player*> players = highScoreManager->getHighScores(totalPlayerCount);

    scoreTable->setRowCount(0);
    scoreTable->setSortingEnabled(false);

    for(Player* p : players) {
        int r = scoreTable->rowCount();
        scoreTable->insertRow(r);

        // avatar  and level Container
        QWidget* avatarContainer = new QWidget();
        avatarContainer->setStyleSheet("background: transparent; border: none;");
        QVBoxLayout* vLayout = new QVBoxLayout(avatarContainer);

        QLabel *img = new QLabel();
        img->setPixmap(QIcon(QString(":/avatar%1.png").arg(p->getAvatarId() + 1)).pixmap(65, 65));
        img->setAlignment(Qt::AlignCenter);
        vLayout->addWidget(img);

        QLabel* levelLabel = new QLabel(p->getLevel());
        levelLabel->setStyleSheet("font-size: 11pt; color: #7f8c8d; font-weight: bold; border: none;");
        levelLabel->setAlignment(Qt::AlignCenter);
        vLayout->addWidget(levelLabel);
        scoreTable->setCellWidget(r, 0, avatarContainer);

        // Name
        QTableWidgetItem* nameItem = new QTableWidgetItem(p->getName());
        nameItem->setTextAlignment(Qt::AlignCenter);
        if(p->getName() == currentPlayer->getName()) {
            nameItem->setForeground(QBrush(QColor("#3498db")));
        }
        scoreTable->setItem(r, 1, nameItem);

        // Score
        QTableWidgetItem* scoreItem = new QTableWidgetItem();
        scoreItem->setData(Qt::EditRole, p->getScore());
        scoreItem->setTextAlignment(Qt::AlignCenter);
        if(p->getName() == currentPlayer->getName()) {
            scoreItem->setForeground(QBrush(QColor("#3498db")));
        }
        scoreTable->setItem(r, 2, scoreItem);
    }

    scoreTable->setSortingEnabled(true);
    scoreTable->sortItems(2, Qt::DescendingOrder);
}

void MainWindow::updateCategoryProgress() {

     for (int i = 0; i < 6; ++i) {
        CategoryEnum cat = static_cast<CategoryEnum>(i);
        QPushButton* b = categoryButtons[i]; 
        int completed = currentPlayer ? currentPlayer->getCompletedWords(cat).size() : 0;
        int totalWords = 10;
        QString name = getCategoryName(cat);
        b->setText(QString("%1\n%2/%3 COMPLETED").arg(name).arg(completed).arg(totalWords));
        if (completed >= totalWords) {
            b->setEnabled(false);  // cannot click
            b->setStyleSheet(
                "QPushButton {"
                "  background-color: #bdc3c7;"
                "  border: 3px solid #7f8c8d;"
                "  border-radius: 20px;"
                "  font-size: 20px;"
                "  font-weight: bold;"
                "  color: #7f8c8d;"
                "  text-align: center;"
                "  padding: 10px;"
                "}"
                ); // gray out 
        } else {
            b->setEnabled(true);
            //normal clickable style
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
        }
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
        }
    }
    settings.endGroup(); // CompletedWords
    settings.endGroup(); // playerName
    settings.endGroup(); // Players
    updateCategoryProgress();

}

void MainWindow::saveData() {
    QSettings settings("MyCompany", "WordGarden");
    settings.beginGroup("Players");
    QList<Player*> players = playerRepo->getAllPlayers();
    for (Player* p : players) {
        settings.beginGroup(p->getName());
        settings.setValue("level", p->getLevel());
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

    GameState* gs = gameManager->getCurrentGameState();
    if (mainFlower && gs) {
        mainFlower->setLeafCount(gs->getRemainingGuesses()); 
    }

    stackedWidget->setCurrentIndex(2);
}

//new from Berrak
void MainWindow::startNextWordInCategory(CategoryEnum category) {
    int completed = currentPlayer->getCompletedWords(category).size();
    int totalWords = 10; 

    if(completed >= totalWords) {
        // category ended
        backToCategoryMenu();
    } else {
        //  new word in the same category
        startNewGame(getCategoryName(category));
    }
}

void MainWindow::resetAlphabetButtons() {
    for(QPushButton* b : alphabetButtons) {
        b->setEnabled(true);
        b->setStyleSheet("font-size: 20px; font-weight: bold; color: #2c3e50; background-color: #fdfdfd; border: 1px solid #ccc;");
    }
}
void MainWindow::goToScores() { updateScoreTable(); stackedWidget->setCurrentIndex(3); }

// new
void MainWindow::backToCategoryMenu() {
    updateCategoryProgress();   // in same category
    stackedWidget->setCurrentIndex(1);
}

// NEW from Berrak
void MainWindow::toggleUserMode()
{
    bool isNewUser = newUserRadio->isChecked();
    avatarSection->setVisible(isNewUser);
}

// logout NEW
void MainWindow::logout() {
    nameInput->clear();
    if(currentPlayer) saveData();
    stackedWidget->setCurrentIndex(0);
}

// destructor NEW
MainWindow::~MainWindow() {}












