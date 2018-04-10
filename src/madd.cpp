#include "madd.h"

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
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

  ReloadShader();

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

  while (!glfwWindowShouldClose(window)) {
    ProcessInput();

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(program->GetID());
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
  else if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    ReloadShader();
}

//This function is temporary for shader testing.
void Madd::ReloadShader(){
    Shader *vertexShader = new Shader("default.vs");
    Shader *fragmentShader = new Shader("default.fs");
    ShaderProgram *_program = new ShaderProgram(vertexShader, fragmentShader);

    delete vertexShader;
    delete fragmentShader;
    if(program)
      delete program;
    program = _program;
}