TEMPLATE = app
CONFIG += c++17
QT += core widgets gui
SOURCES += main.cpp mainWindow.cpp
HEADERS += mainwindow.h
INCLUDEPATH += /opt/homebrew/opt/qt/include
LIBS += -F/opt/homebrew/opt/qt/lib -framework QtCore -framework QtWidgets -framework QtGui

DESTDIR = build
TARGET = main
