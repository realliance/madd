#include "madd.h"

#include <iostream>
#include <vector>

#include "shader.h"
#include "vertexarray.h"

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}

Madd::Madd(int width, int height, const char *title):program(nullptr),close(false) {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  window = glfwCreateWindow(width, height, title, NULL, NULL);
  glfwMakeContextCurrent(window);

  gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
  glViewport(0, 0, width, height);

  glEnable(GL_DEPTH_TEST);

  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
}

Madd::~Madd() { glfwTerminate(); }


void Madd::addObject(GameObject* obj){
    objs.push_back(obj);
}

void Madd::Tick(){
  if (!glfwWindowShouldClose(window)) {
    ProcessInput();

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    

    for(GameObject* obj : objs){
        obj->Update();
        obj->Render();
    }

    glfwSwapBuffers(window);
    glfwPollEvents();
  }else{
      close =true;
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
  for(GameObject* obj : objs){
        if(!obj->ReloadShaders()){
          return false;
        }
  }
  return true;
}
