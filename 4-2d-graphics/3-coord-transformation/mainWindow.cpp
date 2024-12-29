#include "mainWindow.h"
#include <QtGui/QPaintEvent>
#include <QtGui/QPainter>
#include <QtCore/QTime>

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
{
  m_timer.start(1000);
  connect(&m_timer, &QTimer::timeout, this, qOverload<>(&MainWindow::update));
}

void MainWindow::paintEvent(QPaintEvent *)
{
  static const QPoint hourHand[3] = {
    QPoint(4, 4),
    QPoint(-4, 4),
    QPoint(0, -40)
  };
  static const QPoint minuteHand[3] = {
    QPoint(4, 4),
    QPoint(-4, 4),
    QPoint(0, -70)
  };
  static const QPoint secondHand[3] = {
    QPoint(4, 4),
    QPoint(-4, 4),
    QPoint(0, -90)
  };

  int side = qMin(width(), height());
  QPainter painter(this);
  painter.setRenderHint(QPainter::Antialiasing);
  painter.translate(width() / 2, height() / 2);
  painter.scale(side / 250.0, side / 250.0);

  for (int i = 0; i < 60; ++i) {
    if ((i % 5) == 0) {
      painter.drawLine(92, 0, 96, 0);
    } else {
      painter.drawLine(86, 0, 96, 0);
    }
    painter.rotate(6.0);
  }

  QTime time = QTime::currentTime();

  painter.save();
  painter.rotate(time.hour() * 360 / 12.0);
  painter.setPen(Qt::NoPen);
  painter.setBrush(Qt::black);
  painter.drawConvexPolygon(hourHand, 3);
  painter.restore();

  painter.save();
  painter.rotate(time.minute() * 360 / 60.0);
  painter.setPen(Qt::NoPen);
  painter.setBrush(Qt::black);
  painter.drawConvexPolygon(minuteHand, 3);
  painter.restore();

  painter.save();
  painter.rotate(time.second() * 360 / 60.0);
  painter.setPen(Qt::NoPen);
  painter.setBrush(Qt::red);
  painter.drawConvexPolygon(secondHand, 3);
  painter.restore();
}
