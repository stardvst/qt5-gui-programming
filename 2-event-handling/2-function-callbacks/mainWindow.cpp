#include "mainWindow.h"
#include <QtGui/QResizeEvent>
#include <QtGui/QKeyEvent>
#include <QtGui/QMouseEvent>
#include <QtGui/QWheelEvent>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
  setMouseTracking(true);
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
  qDebug() << "Old size: " << event->oldSize() << "New size: " << event->size();
  QMainWindow::resizeEvent(event);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
  qDebug() << "Key pressed: " << event->text();
  if (event->key() == Qt::Key_Escape)
    close();
  QMainWindow::keyPressEvent(event);
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
  qDebug() << "Key released: " << event->text();
  QMainWindow::keyReleaseEvent(event);
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
  qDebug() << "Mouse moved to: " << event->pos();
  QMainWindow::mouseMoveEvent(event);
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
  qDebug() << "Mouse button " << event->button() << " pressed";
  QMainWindow::mousePressEvent(event);
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
  qDebug() << "Mouse button " << event->button() << " released";
  QMainWindow::mouseReleaseEvent(event);
}

void MainWindow::wheelEvent(QWheelEvent *event)
{
  qDebug() << "Mouse wheel moved: " << event->angleDelta();
  QMainWindow::wheelEvent(event);
}
