#include "server.h"

#include <QtCore/QCoreApplication>

int main(int argc, char *argv[])
{
  QCoreApplication app(argc, argv);

  Server server;
  server.startServer();

  return app.exec();
}
