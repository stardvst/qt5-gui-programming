TEMPLATE = app
CONFIG += c++17
QT += core widgets
SOURCES += main.cpp
HEADERS +=
INCLUDEPATH += /opt/homebrew/opt/qt/include
LIBS += -F/opt/homebrew/opt/qt/lib -framework QtCore -framework QtWidgets

DESTDIR = build
TARGET = main
