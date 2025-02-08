#include "mainWindow.h"

#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QGridLayout>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
  auto nameLabel = new QLabel("Name:");
  m_nameLineEdit = new QLineEdit;
  m_connectButton = new QPushButton("Connect");
  connect(m_connectButton, &QPushButton::clicked, this, &MainWindow::onConnect);

  m_textEdit = new QTextEdit;

  m_messageLineEdit = new QLineEdit;
  auto sendButton = new QPushButton("Send");
  connect(sendButton, &QPushButton::clicked, this, &MainWindow::onSend);

  auto connectLayout = new QHBoxLayout;
  connectLayout->addWidget(nameLabel);
  connectLayout->addWidget(m_nameLineEdit);
  connectLayout->addWidget(m_connectButton);

  auto sendLayout = new QHBoxLayout;
  sendLayout->addWidget(m_messageLineEdit);
  sendLayout->addWidget(sendButton);

  auto mainLayout = new QVBoxLayout;
  mainLayout->addLayout(connectLayout);
  mainLayout->addWidget(m_textEdit);
  mainLayout->addLayout(sendLayout);

  QWidget *centralWidget = new QWidget(this);
  centralWidget->setLayout(mainLayout);
  setCentralWidget(centralWidget);
}

void MainWindow::printMessage(QString message)
{
  m_textEdit->append(message);
}

void MainWindow::onConnect()
{
  if (!m_connectedToHost)
  {
    m_socket = new QTcpSocket();

    connect(m_socket, &QTcpSocket::connected, this, &MainWindow::socketConnected);
    connect(m_socket, &QTcpSocket::disconnected, this, &MainWindow::socketDisconnected);
    connect(m_socket, &QTcpSocket::readyRead, this, &MainWindow::socketReadyRead);

    m_socket->connectToHost("127.0.0.1", 8001);
  }
  else
  {
    QString name = m_nameLineEdit->text();
    m_socket->write("<font color=\"Orange\">" + name.toUtf8() + " has left the chat room.</font>");

    m_socket->disconnectFromHost();
  }
}

void MainWindow::onSend()
{
  QString name = m_nameLineEdit->text();
  QString message = m_messageLineEdit->text();
  m_socket->write("<font color=\"Blue\">" + name.toUtf8() + "</font>: " + message.toUtf8());

  m_messageLineEdit->clear();
}

void MainWindow::socketConnected()
{
  qDebug() << "Connected to server.";

  printMessage("<font color=\"Green\">Connected to server.</font>");

  QString name = m_nameLineEdit->text();
  m_socket->write("<font color=\"Purple\">" + name.toUtf8() + " has joined the chat room.</font>");

  m_connectButton->setText("Disconnect");
  m_connectedToHost = true;
}

void MainWindow::socketDisconnected()
{
  qDebug() << "Disconnected from server.";

  printMessage("<font color=\"Red\">Disconnected from server.</font>");

  m_connectButton->setText("Connect");
  m_connectedToHost = false;
}

void MainWindow::socketReadyRead()
{
  printMessage(m_socket->readAll());
}
