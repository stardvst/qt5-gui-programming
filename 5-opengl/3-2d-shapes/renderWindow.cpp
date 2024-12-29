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
  m_openGLFunctions = m_context.functions();

  static const char *vertexShaderSource =
      "#version 330 core\n"
      "layout (location = 0) in vec2 aPos;\n"
      "layout (location = 1) in vec3 aCol;\n"
      "out vec3 fragCol;\n"
      "void main()\n"
      "{\n"
      "    fragCol = aCol;\n"
      "    gl_Position = vec4(aPos, 1.0, 1.0);\n"
      "}\n";

  static const char *fragmentShaderSource =
      "#version 330 core\n"
      "in vec3 fragCol;\n"
      "out vec4 col;\n"
      "void main()\n"
      "{\n"
      "    col = vec4(fragCol, 1.0f);\n"
      "}\n";

  m_program.addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource);
  m_program.addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource);
  m_program.link();

  // Define vertex data and colors in one buffer to reduce binding overhead
  GLfloat vertices[] = {
      -0.3f, -0.5f, 1.0f, 0.0f, 0.0f, // Vertex 1 (Position + Color)
      0.8f, -0.4f, 0.0f, 1.0f, 0.0f,  // Vertex 2 (Position + Color)
      0.2f, 0.6f, 0.0f, 0.0f, 1.0f,   // Vertex 3 (Position + Color)

      0.5f, 0.3f, 1.0f, 0.0f, 0.0f,  // Vertex 4 (Position + Color)
      0.4f, -0.8f, 0.0f, 1.0f, 0.0f, // Vertex 5 (Position + Color)
      -0.6f, -0.2f, 0.0f, 0.0f, 1.0f // Vertex 6 (Position + Color)
  };

  m_vao.create();
  m_vao.bind();

  // Create and bind VBO with both position and color data
  m_vbo.create();
  m_vbo.setUsagePattern(QOpenGLBuffer::StaticDraw);
  m_vbo.bind();
  m_vbo.allocate(vertices, sizeof(vertices));

  // Set up attribute for position
  m_program.bindAttributeLocation("aPos", 0);
  m_program.enableAttributeArray(0);
  m_program.setAttributeBuffer(0, GL_FLOAT, 0, 2, 5 * sizeof(GLfloat)); // Each vertex has 5 components (Position + Color)

  // Set up attribute for color
  m_program.bindAttributeLocation("aColor", 1);
  m_program.enableAttributeArray(1);
  m_program.setAttributeBuffer(1, GL_FLOAT, 2 * sizeof(GLfloat), 3, 5 * sizeof(GLfloat)); // Color data starts from 2nd component

  m_vao.release();
}

void RenderWindow::paintEvent(QPaintEvent *)
{
  glViewport(0, 0, width(), height());
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  m_vao.bind();
  m_program.bind();

  glDrawArrays(GL_TRIANGLES, 0, 6); // Draw 2 triangles (6 vertices)

  m_program.release();
  m_vao.release();
}

void RenderWindow::resizeEvent(QResizeEvent *event)
{
  glViewport(0, 0, width(), height());
  update();
}
