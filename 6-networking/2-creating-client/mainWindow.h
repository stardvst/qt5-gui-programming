#pragma once

#include <QtWidgets/QMainWindow>

#include <QDebug>
#include <QTcpSocket>

class QLineEdit;
class QPushButton;
class QTextEdit;

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  void printMessage(QString message);

private slots:
  void onConnect();
  void onSend();

  void socketConnected();
  void socketDisconnected();
  void socketReadyRead();

private:
  QLineEdit *m_nameLineEdit{nullptr};
  QPushButton *m_connectButton{nullptr};
  QTextEdit *m_textEdit{nullptr};

  QLineEdit *m_messageLineEdit{nullptr};
  QPushButton *m_sendButton{nullptr};

  bool m_connectedToHost = false;
  QTcpSocket *m_socket{nullptr};
};
