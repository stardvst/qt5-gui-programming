TEMPLATE = app
CONFIG += c++17
QT += core network gui widgets
SOURCES += main.cpp mainWindow.cpp
HEADERS += mainWindow.h
INCLUDEPATH += /opt/homebrew/opt/qt/include
LIBS += -F/opt/homebrew/opt/qt/lib -framework QtCore -framework QtNetwork -framework QtWidgets -framework QtGui

DESTDIR = build
TARGET = main
