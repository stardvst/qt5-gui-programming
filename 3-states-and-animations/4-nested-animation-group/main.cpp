#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtCore/QPropertyAnimation>
#include <QtCore/QParallelAnimationGroup>
#include <QtCore/QSequentialAnimationGroup>

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);

  QMainWindow window;
  window.resize(400, 300);

  QPushButton button1("PushButton", &window);
  QPropertyAnimation animation1(&button1, "geometry");
  animation1.setDuration(3000);
  animation1.setStartValue(button1.geometry());
  animation1.setEndValue(QRect(/*pos*/ 50, 50, /*size*/ 100, 50));

  QPushButton button2("PushButton", &window);
  QPropertyAnimation animation2(&button2, "geometry");
  animation2.setDuration(3000);
  animation2.setStartValue(button2.geometry());
  animation2.setEndValue(QRect(/*pos*/ 150, 50, /*size*/ 100, 50));

  QPushButton button3("PushButton", &window);
  QPropertyAnimation animation3(&button3, "geometry");
  animation3.setDuration(3000);
  animation3.setStartValue(button3.geometry());
  animation3.setEndValue(QRect(/*pos*/ 250, 50, /*size*/ 100, 50));

  QPushButton button4("PushButton", &window);
  QPropertyAnimation animation4(&button4, "geometry");
  animation4.setDuration(3000);
  animation4.setStartValue(button4.geometry());
  animation4.setEndValue(QRect(/*pos*/ 50, 200, /*size*/ 100, 50));

  QPushButton button5("PushButton", &window);
  QPropertyAnimation animation5(&button5, "geometry");
  animation5.setDuration(3000);
  animation5.setStartValue(button5.geometry());
  animation5.setEndValue(QRect(/*pos*/ 150, 200, /*size*/ 100, 50));

  QPushButton button6("PushButton", &window);
  QPropertyAnimation animation6(&button6, "geometry");
  animation6.setDuration(3000);
  animation6.setStartValue(button6.geometry());
  animation6.setEndValue(QRect(/*pos*/ 250, 200, /*size*/ 100, 50));

  QEasingCurve curve;
  curve.setType(QEasingCurve::OutBounce);
  curve.setAmplitude(1.0);
  curve.setOvershoot(1.7);
  curve.setPeriod(0.3);

  animation1.setEasingCurve(curve);
  animation2.setEasingCurve(curve);
  animation3.setEasingCurve(curve);
  animation4.setEasingCurve(curve);
  animation5.setEasingCurve(curve);
  animation6.setEasingCurve(curve);

  QParallelAnimationGroup group1;
  group1.addAnimation(&animation1);
  group1.addAnimation(&animation2);
  group1.addAnimation(&animation3);

  QParallelAnimationGroup group2;
  group2.addAnimation(&animation4);
  group2.addAnimation(&animation5);
  group2.addAnimation(&animation6);

  QSequentialAnimationGroup groupAll;
  groupAll.addAnimation(&group1);
  groupAll.addAnimation(&group2);
  groupAll.start();

  window.show();

  return app.exec();
}
