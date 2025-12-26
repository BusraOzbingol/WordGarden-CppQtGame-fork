QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    main.cpp \
    mainwindow.cpp\
    GameState.cpp\
    GameStateManager.cpp\
    GameStateRepository.cpp\
    Word.cpp\
    WordManager.cpp\
    WordRepository.cpp\
    WordRepositoryFile.cpp\
    WordRepositoryMemory.cpp\
    Player.cpp\
    PlayerManager.cpp\
    PlayerRepository.cpp\
    Score.cpp

HEADERS += \
    mainwindow.h\
    GameState.h\
    GameStateManager.h\
    GameStateRepository.h\
    Word.h\
    WordManager.h\
    WordRepository.h\
    WordRepositoryFile.h\
    WordRepositoryMemory.h\
    Player.h\
    PlayerLevel.h\
    PlayerManager.h\
    PlayerRepository.h\
    Score.h\
    CategoryEnum.h

FORMS += \
    mainwindow.ui

DISTFILES += \
        words.txt

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
