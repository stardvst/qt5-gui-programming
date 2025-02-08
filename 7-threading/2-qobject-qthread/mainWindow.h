#include <QtWidgets/QMainWindow>


class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = nullptr);

public slots:
  void handleResults(int res);
};
