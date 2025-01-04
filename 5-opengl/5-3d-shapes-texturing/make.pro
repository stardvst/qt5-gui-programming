TEMPLATE = app
CONFIG += c++17
QT += core widgets gui opengl
SOURCES += main.cpp renderWindow.cpp
HEADERS += renderWindow.h
INCLUDEPATH += /opt/homebrew/opt/qt/include
LIBS += -F/opt/homebrew/opt/qt/lib -framework QtCore -framework QtWidgets -framework QtGui -framework OpenGL

DESTDIR = build
TARGET = main
