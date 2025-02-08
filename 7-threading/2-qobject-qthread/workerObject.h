#pragma once

#include <QObject>
#include <QDebug>

class WorkerObject : public QObject
{
  Q_OBJECT

public:
  using QObject::QObject;

signals:
  void showResults(int res);
  void doneProcess();

public slots:
  void process();
};
