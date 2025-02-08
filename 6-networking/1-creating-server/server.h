#pragma once

#include <QObject>

#include <QTcpServer>
#include <QTcpSocket>
#include <QVector>
#include <QDebug>

class Server : public QObject
{
  Q_OBJECT

public:
  using QObject::QObject;

  void startServer();
  void sendMessageToClients(const QString &message);

public slots:
  void newClientConnected();
  void socketDisconnected();
  void socketReadyRead();
  void socketStateChanged(QAbstractSocket::SocketState state);

private:
  QTcpServer *m_server;
  QVector<QTcpSocket *> m_clients;
};
