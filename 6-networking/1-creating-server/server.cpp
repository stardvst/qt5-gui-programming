#include "server.h"

void Server::startServer() {
  m_server = new QTcpServer(this);
  m_server->setMaxPendingConnections(10);
  connect(m_server, &QTcpServer::newConnection, this, &Server::newClientConnected);

  if (m_server->listen(QHostAddress::Any, 8001))
    qDebug() << "Server started";
  else
    qDebug() << "Server failed to start: Error: " << m_server->errorString();
}

void Server::sendMessageToClients(const QString &message) {
  for (QTcpSocket *client : m_clients)
  {
    if (client->isOpen() && client->isWritable())
      client->write(message.toUtf8());
  }
}

void Server::newClientConnected() {
  QTcpSocket *client = m_server->nextPendingConnection();
  QString ipAddress = client->peerAddress().toString();
  quint16 port = client->peerPort();

  connect(client, &QTcpSocket::disconnected, this, &Server::socketDisconnected);
  connect(client, &QTcpSocket::readyRead, this, &Server::socketReadyRead);
  connect(client, &QAbstractSocket::stateChanged, this, &Server::socketStateChanged);

  m_clients.push_back(client);
  qDebug() << "New client connected" << ipAddress << ": " << port;
}

void Server::socketDisconnected() {
  QTcpSocket *client = qobject_cast<QTcpSocket *>(sender());
  QString ipAddress = client->peerAddress().toString();
  quint16 port = client->peerPort();

  qDebug() << "Client disconnected" << ipAddress << ": " << port;

  m_clients.removeAll(client);
  client->deleteLater();
}

void Server::socketReadyRead() {
  QTcpSocket *client = qobject_cast<QTcpSocket *>(sender());
  QString ipAddress = client->peerAddress().toString();
  quint16 port = client->peerPort();

  QString message = client->readAll();
  qDebug() << "Received message from" << ipAddress << ": " << port << " - " << message;
  sendMessageToClients(message);
}

void Server::socketStateChanged(QAbstractSocket::SocketState state) {
  QTcpSocket *client = qobject_cast<QTcpSocket *>(sender());
  QString ipAddress = client->peerAddress().toString();
  quint16 port = client->peerPort();

  QString desc;
  if (state == QAbstractSocket::UnconnectedState)
    desc = "The socket is not connected.";
  else if (state == QAbstractSocket::HostLookupState)
    desc = "The socket is performing a host name lookup.";
  else if (state == QAbstractSocket::ConnectingState)
    desc = "The socket has started establishing a connection.";
  else if (state == QAbstractSocket::ConnectedState)
    desc = "A connection is established.";
  else if (state == QAbstractSocket::BoundState)
    desc = "The socket is bound to an address and port.";
  else if (state == QAbstractSocket::ClosingState)
    desc = "The socket is about to close (data may still be waiting to be written).";
  else if (state == QAbstractSocket::ListeningState)
    desc = "For internal use only.";

  qDebug() << "State changed" << ipAddress << ": " << port << " - " << desc;
}
