#include <QtOpenGL/QOpenGLWindow>
#include <QtOpenGL/QOpenGLBuffer>
#include <QtOpenGL/QOpenGLVertexArrayObject>
#include <QtOpenGL/QOpenGLShader>
#include <QtOpenGL/QOpenGLShaderProgram>

#include <QtCore/QElapsedTimer>

class RenderWindow : public QOpenGLWindow
{
public:
  RenderWindow();

protected:
  void initializeGL() override;

  void paintEvent(QPaintEvent *event) override;
  void resizeEvent(QResizeEvent *event) override;

private:
  QOpenGLContext m_context;
  QOpenGLFunctions *m_openGLFunctions{nullptr};
  QOpenGLShaderProgram m_program;
  QOpenGLVertexArrayObject m_vao;
  QOpenGLBuffer m_vbo;

  QElapsedTimer m_time;
  int m_currentTime = 0;
  int m_oldTime = 0;
  float m_deltaTime = 0;
  float m_rotation = 0;
};
