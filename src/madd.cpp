#include "madd.h"

#include <iostream>
#include <vector>

#include "shader.h"
#include "vertexarray.h"

void Clear(GLFWwindow *window) {
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  glfwSwapBuffers(window);

  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
  Clear(window);
}

Madd::Madd(int width, int height, const char *title) {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  window = glfwCreateWindow(width, height, title, NULL, NULL);
  glfwMakeContextCurrent(window);

  gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
  glViewport(0, 0, width, height);

  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
}

Madd::~Madd() { glfwTerminate(); }

void Madd::Start() {

  if (!ReloadShader()) {
    std::cout << "Shader Loading Failed" << std::endl;
    return;
  }

  std::vector<float> vertices = {
      0.5f,  0.5f,  0.0f, // top right
      0.5f,  -0.5f, 0.0f, // bottom right
      -0.5f, -0.5f, 0.0f, // bottom left
      -0.5f, 0.5f,  0.0f  // top left
  };
  std::vector<unsigned int> indices = {
      // note that we start from 0!
      0, 1, 3, // first triangle
      1, 2, 3  // second triangle
  };

  VertexArray *rect = new VertexArray(vertices, indices);

  int shaderTimeLocation = glGetUniformLocation(program->GetID(), "time");

  Clear(window);
  while (!glfwWindowShouldClose(window)) {
    ProcessInput();

    // glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    // glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(program->GetID());
    glUniform1f(shaderTimeLocation, glfwGetTime());

    rect->Bind();

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    VertexArray::UnBind();

    glfwSwapBuffers(window);
    glfwPollEvents();
  }
}

void Madd::ProcessInput() {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
  else if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    ReloadShader();
}

// This function is temporary for shader testing.
bool Madd::ReloadShader() {
  Clear(window);
  Shader *vertexShader;
  Shader *fragmentShader;
  ShaderProgram *_program;
  try {
    vertexShader = new Shader("default.vs");
    fragmentShader = new Shader("default.fs");
    _program = new ShaderProgram(vertexShader, fragmentShader);
  } catch (int e) {
    return false;
  }

  delete vertexShader;
  delete fragmentShader;
  if (program)
    delete program;
  program = _program;
  return true;
}
