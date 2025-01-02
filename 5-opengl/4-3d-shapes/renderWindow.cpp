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

  m_time.start();
  m_oldTime = 0;
}

void RenderWindow::initializeGL()
{
  m_openGLFunctions = m_context.functions();
  glEnable(GL_DEPTH_TEST);

  static const char *vertexShaderSource =
      "#version 330 core\n"
      "layout(location = 0) in vec3 posAttr;\n"
      "uniform mat4 matrix;\n"
      "out vec3 fragPos;\n"
      "void main() {\n"
      "fragPos = posAttr;\n"
      "gl_Position = matrix * vec4(posAttr, 1.0); }";

  static const char *fragmentShaderSource =
      "#version 330 core\n"
      "in vec3 fragPos;\n"
      "out vec4 col;\n"
      "void main() {\n"
      "col = vec4(fragPos, 1.0); }";

  m_program.addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource);
  m_program.addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource);
  m_program.link();

  // Define vertex data and colors in one buffer to reduce binding overhead
  GLfloat vertices[] =
      {
          -1.0f, -1.0f, -1.0f,
          1.0f, -1.0f, -1.0f,
          -1.0f, -1.0f, 1.0f,
          1.0f, -1.0f, -1.0f,
          1.0f, -1.0f, 1.0f,
          -1.0f, -1.0f, 1.0f,
          -1.0f, 1.0f, -1.0f,
          -1.0f, 1.0f, 1.0f,
          1.0f, 1.0f, -1.0f,
          1.0f, 1.0f, -1.0f,
          -1.0f, 1.0f, 1.0f,
          1.0f, 1.0f, 1.0f,
          -1.0f, -1.0f, 1.0f,
          1.0f, -1.0f, 1.0f,
          -1.0f, 1.0f, 1.0f,
          1.0f, -1.0f, 1.0f,
          1.0f, 1.0f, 1.0f,
          -1.0f, 1.0f, 1.0f,
          -1.0f, -1.0f, -1.0f,
          -1.0f, 1.0f, -1.0f,
          1.0f, -1.0f, -1.0f,
          1.0f, -1.0f, -1.0f,
          -1.0f, 1.0f, -1.0f,
          1.0f, 1.0f, -1.0f,
          -1.0f, -1.0f, 1.0f,
          -1.0f, 1.0f, -1.0f,
          -1.0f, -1.0f, -1.0f,
          -1.0f, -1.0f, 1.0f,
          -1.0f, 1.0f, 1.0f,
          -1.0f, 1.0f, -1.0f,
          1.0f, -1.0f, 1.0f,
          1.0f, -1.0f, -1.0f,
          1.0f, 1.0f, -1.0f,
          1.0f, -1.0f, 1.0f,
          1.0f, 1.0f, -1.0f,
          1.0f, 1.0f, 1.0f};

  m_vao.create();
  m_vao.bind();

  // Create and bind VBO with both position and color data
  m_vbo.create();
  m_vbo.setUsagePattern(QOpenGLBuffer::StaticDraw);
  m_vbo.bind();
  m_vbo.allocate(vertices, sizeof(vertices));

  m_vao.release();
}

void RenderWindow::paintEvent(QPaintEvent *)
{
  // Delta time for each frame
  m_currentTime = m_time.elapsed();
  m_deltaTime = (float)(m_currentTime - m_oldTime) / 1000.0f;
  m_oldTime = m_currentTime;

  glViewport(0, 0, width(), height());
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  m_vao.bind();
  m_program.bind();

  m_rotation += m_deltaTime * 50;

  QMatrix4x4 matrixMVP;
  QMatrix4x4 model, view, projection;
  model.translate(0, 1, 0);
  model.rotate(m_rotation, 0, 1, 0);
  view.lookAt(QVector3D(5, 5, 5), QVector3D(0, 0, 0), QVector3D(0, 1, 0));
  projection.perspective(60.0f, ((float)this->width() / (float)this->height()), 0.1f, 100.0f);
  matrixMVP = projection * view * model;
  m_program.setUniformValue("matrix", matrixMVP);

  m_vbo.bind();
  m_program.bindAttributeLocation("posAttr", 0);
  m_program.enableAttributeArray(0);
  m_program.setAttributeBuffer(0, GL_FLOAT, 0, 3);

  glDrawArrays(GL_TRIANGLES, 0, 36); // Draw 2 triangles (6 vertices)

  m_program.release();
  m_vao.release();

  update();
}

void RenderWindow::resizeEvent(QResizeEvent *event)
{
  glViewport(0, 0, width(), height());
  update();
}
