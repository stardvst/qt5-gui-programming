#include "renderWindow.h"

RenderWindow::RenderWindow()
{
  QSurfaceFormat format;
  format.setProfile(QSurfaceFormat::OpenGLContextProfile::CoreProfile);
  format.setVersion(3, 2);
  setFormat(format);

  m_context.setFormat(format);
  m_context.create();
  m_context.makeCurrent(this);
}

void RenderWindow::initializeGL()
{
  m_openGLFunctions = m_context.functions(); // Initialize OpenGL functions

  static const char *vertexShaderSource =
      "#version 330 core\n"
      "layout (location = 0) in vec2 aPos;\n"
      "void main()\n"
      "{\n"
      "    gl_Position = vec4(aPos, 0.0, 1.0);\n"
      "}\n";

  static const char *fragmentShaderSource =
      "#version 330 core\n"
      "out vec4 FragColor;\n"
      "void main()\n"
      "{\n"
      "    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
      "}\n";

  m_program.addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource);
  m_program.addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource);
  m_program.link();

  GLfloat vertices[] = {
      -0.5f, -0.5f,
      0.5f, -0.5f,
      0.5f, 0.5f,
      -0.5f, 0.5f};

  m_vao.create();
  m_vao.bind();

  m_vbo.create();
  m_vbo.setUsagePattern(QOpenGLBuffer::StaticDraw);
  m_vbo.bind();
  m_vbo.allocate(vertices, sizeof(vertices)); // Fixed: No need to multiply by sizeof(GLfloat)

  m_vao.release();
}

void RenderWindow::paintEvent(QPaintEvent *)
{
  glViewport(0, 0, width(), height());
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  m_vao.bind();

  m_program.bind();
  m_program.bindAttributeLocation("aPos", 0);
  m_program.enableAttributeArray(0);
  m_program.setAttributeBuffer(0, GL_FLOAT, 0, 2);
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
  m_program.release();

  m_vao.release();
}

void RenderWindow::resizeEvent(QResizeEvent *event)
{
  glViewport(0, 0, width(), height());
  update();
}
