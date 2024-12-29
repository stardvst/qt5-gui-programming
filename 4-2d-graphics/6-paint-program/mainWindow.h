#pragma once

#include <QtWidgets/QMainWindow>
#include <QtGui/QImage>

class MainWindow : public QMainWindow
{
public:
  explicit MainWindow(QWidget *parent = nullptr);

  void mousePressEvent(QMouseEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override;
  void mouseReleaseEvent(QMouseEvent *event) override;
  void paintEvent(QPaintEvent *event) override;
  void resizeEvent(QResizeEvent *event) override;

protected slots:
  void on_actionSave_triggered();
  void on_actionClear_triggered();

  void on_action2px_triggered();
  void on_action5px_triggered();
  void on_action10px_triggered();

  void on_actionBlack_triggered();
  void on_actionRed_triggered();
  void on_actionGreen_triggered();
  void on_actionBlue_triggered();

private:
  QImage m_image{};
  bool m_isDrawing{false};
  QPoint m_lastPoint{};
  QColor m_color{Qt::black};
  int m_lineWidth{2};
};
