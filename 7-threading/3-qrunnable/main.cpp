#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtCore/QThread>
#include <QtCore/QThreadPool>
#include <QtCore/QRunnable>
#include <QtCore/QDebug>
#include <QtCore/QTimer>

class CustomProcess : public QRunnable
{
public:
  void run() override
  {
    int number = 0;
    for (int i = 0; i < 2000000000; ++i)
    {
      number += 1;
    }
    qDebug() << "Task completed in thread:" << QThread::currentThread() << "Result:" << number;
  }
};

class MainWindow : public QMainWindow
{
public:
  MainWindow(QWidget *parent = nullptr) : QMainWindow(parent)
  {
    CustomProcess *p1 = new CustomProcess();
    CustomProcess *p2 = new CustomProcess();
    CustomProcess *p3 = new CustomProcess();
    CustomProcess *p4 = new CustomProcess();

    QThreadPool::globalInstance()->start(p1);
    QThreadPool::globalInstance()->start(p2);
    QThreadPool::globalInstance()->start(p3);
    QThreadPool::globalInstance()->start(p4);

    qDebug() << "Active threads:" << QThreadPool::globalInstance()->activeThreadCount();
  }
};

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);

  MainWindow window;
  window.show();

  return a.exec();
}
