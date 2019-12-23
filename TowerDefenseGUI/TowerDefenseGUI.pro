QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11 \
    warn_off

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Lib/Building.cpp \
    Lib/Castle.cpp \
    Lib/Cell.cpp \
    Lib/Effect.cpp \
    Lib/Enemy.cpp \
    Lib/Feature.cpp \
    Lib/FileStructs.cpp \
    Lib/GameManager.cpp \
    Lib/Landscape.cpp \
    Lib/Lire.cpp \
    Lib/MagicEntity.cpp \
    Lib/MagicTower.cpp \
    Lib/Strategy.cpp \
    Lib/Tower.cpp \
    Lib/TowerDefenseStaticLib.cpp \
    Lib/Trap.cpp \
    Lib/pch.cpp \
    about.cpp \
    gamewindow.cpp \
    levelchoicewindow.cpp \
    main.cpp \
    mainwindow.cpp \
    startoptionswindow.cpp

HEADERS += \
    Lib/Building.h \
    Lib/Castle.h \
    Lib/Cell.h \
    Lib/Effect.h \
    Lib/Enemy.h \
    Lib/Entity.h \
    Lib/Enums.h \
    Lib/Feature.h \
    Lib/FileStructs.h \
    Lib/GameManager.h \
    Lib/Landscape.h \
    Lib/Lire.h \
    Lib/MagicEntity.h \
    Lib/MagicTower.h \
    Lib/Strategy.h \
    Lib/Table.h \
    Lib/Tower.h \
    Lib/TowerDefenseLib.h \
    Lib/Trap.h \
    Lib/framework.h \
    Lib/pch.h \
    about.h \
    gamewindow.h \
    levelchoicewindow.h \
    mainwindow.h \
    startoptionswindow.h

FORMS += \
    about.ui \
    gamewindow.ui \
    levelchoicewindow.ui \
    mainwindow.ui \
    startoptionswindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    GameField.qml \
    GameFieldForm.ui.qml
