#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtCore/QPropertyAnimation>

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);

  QMainWindow window;
  window.resize(400, 300);
  QPushButton button("PushButton", &window);

  QPropertyAnimation animation(&button, "geometry");
  animation.setDuration(2000);
  animation.setStartValue(button.geometry());
  animation.setEndValue(QRect(/*pos*/200, 200, /*size*/100, 50));

  QEasingCurve curve;
  curve.setType(QEasingCurve::OutBounce);
  curve.setAmplitude(1.0);
  curve.setOvershoot(1.7);
  curve.setPeriod(0.3);

  animation.setEasingCurve(curve);
  animation.setLoopCount(2);
  animation.start();

  window.show();

  return app.exec();
}
