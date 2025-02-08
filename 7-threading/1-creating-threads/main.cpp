#include <QtCore/QCoreApplication>
#include <QtCore/QFuture>
#include <QtCore/QFutureWatcher>
#include <QtCore/QThread>
#include <QtConcurrent/QtConcurrent>

void printText(const QString &message, int count)
{
  for (int i = 0; i < count; ++i)
    qDebug() << message << QThread::currentThreadId();
  qDebug() << message << "Done";
}

int main(int argc, char *argv[])
{
  QCoreApplication app(argc, argv);

  // printText("A", 5);
  // printText("B", 5);

  QFuture<void> f1 = QtConcurrent::run(printText, "A", 5);
  QFuture<void> f2 = QtConcurrent::run(printText, "B", 5);
  QFuture<void> f3 = QtConcurrent::run(printText, "C", 5);

  f1.waitForFinished();
  f2.waitForFinished();
  f3.waitForFinished();
}
