TEMPLATE = app
CONFIG += c++17
QT += core network
SOURCES += main.cpp server.cpp
HEADERS += server.h
INCLUDEPATH += /opt/homebrew/opt/qt/include
LIBS += -F/opt/homebrew/opt/qt/lib -framework QtCore -framework QtNetwork

DESTDIR = build
TARGET = main
