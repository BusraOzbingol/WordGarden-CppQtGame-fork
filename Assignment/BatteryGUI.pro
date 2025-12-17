QT          += core gui
QT          += widgets printsupport

INCLUDEPATH += $$PWD/Battery

CONFIG      += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

# --- Kaynak Dosyalar ---
SOURCES += \
    Battery.cpp \
    BatteryPack.cpp \
    batteryview.cpp \
    main.cpp \
    mainwindow.cpp

# --- Başlık Dosyaları ---
HEADERS += \
    Battery.h \
    Battery/Battery.h \
    Battery/BatteryPack.h \
    BatteryPack.h \
    batteryview.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
