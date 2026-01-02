QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    1_Entities/GameState.cpp \
    3_Manager/GameStateManager.cpp \
    2_Repository/GameStateRepository.cpp \
    3_Manager/HighScoreManager.cpp \
    1_Entities/Player.cpp \
    3_Manager/PlayerManager.cpp \
    2_Repository/PlayerRepository.cpp \
    1_Entities/Score.cpp \
    1_Entities/Word.cpp \
    3_Manager/WordManager.cpp \
    2_Repository/WordRepositoryFile.cpp \
    2_Repository/WordRepositoryMemory.cpp \
    4_Ui/main.cpp \
    4_Ui/mainFlower.cpp \
    4_Ui/mainwindow.cpp

HEADERS += \
    0_Enums/CategoryEnum.h \
    1_Entities/GameState.h \
    3_Manager/GameStateManager.h \
    2_Repository/GameStateRepository.h \
    3_Manager/HighScoreManager.h \
    2_Repository/IWordRepository.h \
    1_Entities/Player.h \
    0_Enums/PlayerLevel.h \
    3_Manager/PlayerManager.h \
    2_Repository/PlayerRepository.h \
    1_Entities/Score.h \
    1_Entities/Word.h \
    3_Manager/WordManager.h \
    2_Repository/WordRepositoryFile.h \
    2_Repository/WordRepositoryMemory.h \
    4_Ui/mainFlower.h \
    4_Ui/mainwindow.h

FORMS += \
    4_Ui/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

DISTFILES += \
    5_File/words.txt
