#include "renderWindow.h"

#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);

  RenderWindow window;
  window.setTitle("Hello OpenGL!");
  window.resize(640, 480);

  window.show();

  return app.exec();
}
