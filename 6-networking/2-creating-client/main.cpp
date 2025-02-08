#include "mainWindow.h"

#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);

  MainWindow window;
  window.setWindowTitle("Client");
  window.resize(400, 300);
  window.show();

  return app.exec();
}
