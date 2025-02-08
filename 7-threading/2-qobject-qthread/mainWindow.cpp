#include "mainWindow.h"
#include "workerObject.h"

// #include <QtCore/QThread>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
  // QThread* workerThread = new QThread;
  WorkerObject *workerObject = new WorkerObject;

  // workerObject->moveToThread(workerThread);
  // connect(workerThread, &QThread::started, workerObject, &WorkerObject::process);
  // connect(workerObject, &WorkerObject::doneProcess, workerThread, &QThread::quit);
  connect(workerObject, &WorkerObject::doneProcess, workerObject, &WorkerObject::deleteLater);
  connect(workerObject, &WorkerObject::showResults, this, &MainWindow::handleResults);
  // connect(workerThread, &QThread::finished, workerObject, &WorkerObject::deleteLater);
  // workerThread->start();

  workerObject->process();
}

void MainWindow::handleResults(int res)
{
  qDebug() << "Final result:" << res;
}
