#include <QtOpenGL/QOpenGLWindow>
#include <QtOpenGL/QOpenGLBuffer>
#include <QtOpenGL/QOpenGLVertexArrayObject>
#include <QtOpenGL/QOpenGLShader>
#include <QtOpenGL/QOpenGLShaderProgram>

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
};
