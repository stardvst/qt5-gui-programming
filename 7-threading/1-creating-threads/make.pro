TEMPLATE = app
CONFIG += c++17
QT += core
SOURCES += main.cpp
INCLUDEPATH += /opt/homebrew/opt/qt/include
LIBS += -F/opt/homebrew/opt/qt/lib -framework QtCore

DESTDIR = build
TARGET = main
