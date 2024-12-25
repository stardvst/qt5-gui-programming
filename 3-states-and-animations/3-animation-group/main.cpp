#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtCore/QPropertyAnimation>
#include <QtCore/QParallelAnimationGroup>
// #include <QtCore/QSequentialAnimationGroup>

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);

  QMainWindow window;
  window.resize(400, 300);

  QPushButton button1("PushButton", &window);
  QPropertyAnimation animation1(&button1, "geometry");
  animation1.setDuration(3000);
  animation1.setStartValue(button1.geometry());
  animation1.setEndValue(QRect(/*pos*/50, 50, /*size*/100, 50));

  QPushButton button2("PushButton", &window);
  QPropertyAnimation animation2(&button2, "geometry");
  animation2.setDuration(3000);
  animation2.setStartValue(button2.geometry());
  animation2.setEndValue(QRect(/*pos*/150, 50, /*size*/ 100, 50));

  QPushButton button3("PushButton", &window);
  QPropertyAnimation animation3(&button3, "geometry");
  animation3.setDuration(3000);
  animation3.setStartValue(button3.geometry());
  animation3.setEndValue(QRect(/*pos*/250, 50, /*size*/ 100, 50));

  QEasingCurve curve;
  curve.setType(QEasingCurve::OutBounce);
  curve.setAmplitude(1.0);
  curve.setOvershoot(1.7);
  curve.setPeriod(0.3);

  animation1.setEasingCurve(curve);
  animation2.setEasingCurve(curve);
  animation3.setEasingCurve(curve);

  QParallelAnimationGroup group;
  // QSequentialAnimationGroup group;
  group.addAnimation(&animation1);
  group.addAnimation(&animation2);
  group.addAnimation(&animation3);
  group.start();

  window.show();

  return app.exec();
}
