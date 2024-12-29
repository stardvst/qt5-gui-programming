#pragma once

#include <QtWidgets/QMainWindow>
#include <QtCore/QTimer>

class MainWindow : public QMainWindow
{
public:
  explicit MainWindow(QWidget *parent = nullptr);
  void paintEvent(QPaintEvent *event) override;

private:
  QTimer m_timer;
};
