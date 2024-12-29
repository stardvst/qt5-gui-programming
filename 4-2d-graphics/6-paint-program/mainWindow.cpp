#include "mainWindow.h"
#include <QtCore/QTime>
#include <QtGui/QPaintEvent>
#include <QtGui/QPainter>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), m_image(size(), QImage::Format_RGB32)
{
  m_image.fill(Qt::white);

  // create the menu bar and add actions
  QMenu *fileMenu = menuBar()->addMenu("File");
  QAction *saveAction = fileMenu->addAction("Save");
  connect(saveAction, &QAction::triggered, this, &MainWindow::on_actionSave_triggered);
  QAction *clearAction = fileMenu->addAction("Clear");
  connect(clearAction, &QAction::triggered, this, &MainWindow::on_actionClear_triggered);

  // create the line width menu and add actions
  QMenu *lineWidthMenu = menuBar()->addMenu("Line width");
  QAction *action2px = lineWidthMenu->addAction("2px");
  connect(action2px, &QAction::triggered, this, &MainWindow::on_action2px_triggered);
  QAction *action5px = lineWidthMenu->addAction("5px");
  connect(action5px, &QAction::triggered, this, &MainWindow::on_action5px_triggered);
  QAction *action10px = lineWidthMenu->addAction("10px");
  connect(action10px, &QAction::triggered, this, &MainWindow::on_action10px_triggered);

  // create the color menu and add actions
  QMenu *colorMenu = menuBar()->addMenu("Color");
  QAction *blackAction = colorMenu->addAction("Black");
  connect(blackAction, &QAction::triggered, this, &MainWindow::on_actionBlack_triggered);
  QAction *redAction = colorMenu->addAction("Red");
  connect(redAction, &QAction::triggered, this, &MainWindow::on_actionRed_triggered);
  QAction *greenAction = colorMenu->addAction("Green");
  connect(greenAction, &QAction::triggered, this, &MainWindow::on_actionGreen_triggered);
  QAction *blueAction = colorMenu->addAction("Blue");
  connect(blueAction, &QAction::triggered, this, &MainWindow::on_actionBlue_triggered);

  setMouseTracking(true);
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
  if (event->button() == Qt::LeftButton)
  {
    m_isDrawing = true;
    m_lastPoint = event->pos();
  }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
  if (event->buttons() & Qt::LeftButton && m_isDrawing)
  {
    QPainter painter(&m_image);
    painter.setPen(QPen(m_color, m_lineWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter.drawLine(m_lastPoint, event->pos());
    m_lastPoint = event->pos();
    update();
  }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
  if (event->button() == Qt::LeftButton && m_isDrawing)
    m_isDrawing = false;
}

void MainWindow::paintEvent(QPaintEvent *)
{
  QPainter painter(this);
  painter.drawImage(rect(), m_image, m_image.rect());
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
  QImage newImage(event->size(), QImage::Format_RGB32);
  newImage.fill(qRgb(255, 255, 255));

  QPainter painter(&newImage);
  painter.drawImage(QPoint(0, 0), m_image);
  m_image = newImage;

  QMainWindow::resizeEvent(event);
}

void MainWindow::on_actionSave_triggered()
{
  QString filePath = QFileDialog::getSaveFileName(this, "Save image", "", "PNG Image (*.png);;JPEG Image (*.jpeg *.jpg);;All Files (*.*)");
  if (!filePath.isEmpty())
    m_image.save(filePath);
}

void MainWindow::on_actionClear_triggered()
{
  m_image.fill(Qt::white);
  update();
}

void MainWindow::on_action2px_triggered()
{
  m_lineWidth = 2;
}

void MainWindow::on_action5px_triggered()
{
  m_lineWidth = 5;
}

void MainWindow::on_action10px_triggered()
{
  m_lineWidth = 10;
}

void MainWindow::on_actionBlack_triggered()
{
  m_color = Qt::black;
}

void MainWindow::on_actionRed_triggered()
{
  m_color = Qt::red;
}

void MainWindow::on_actionGreen_triggered()
{
  m_color = Qt::green;
}

void MainWindow::on_actionBlue_triggered()
{
  m_color = Qt::blue;
}
