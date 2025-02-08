TEMPLATE = app
CONFIG += c++17
QT += core widgets
SOURCES += main.cpp mainWindow.cpp workerObject.cpp
HEADERS += mainWindow.h workerObject.h
INCLUDEPATH += /opt/homebrew/opt/qt/include
LIBS += -F/opt/homebrew/opt/qt/lib -framework QtCore -framework QtWidgets

DESTDIR = build
TARGET = main
