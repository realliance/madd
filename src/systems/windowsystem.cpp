#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "windowsystem.h"
#include "madd.h"
#include "camerasystem.h"
#include "keyboardeventsystem.h"
#include "mouseeventsystem.h"


void WindowSystem::errorCallback(int, const char* err_str) {
    std::cout << "GLFW Error: " << err_str << std::endl;
}

void WindowSystem::framebufferSizeCallback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
    WindowComponent* windowcomp = static_cast<WindowComponent*>(glfwGetWindowUserPointer(window));
    for(CameraComponent* c : windowcomp->cameras){
      c->aspectratio = (float) width/height;
      CameraSystem::UpdateProjection(*c, width, height);
    }
}

void WindowSystem::keyCallBack(GLFWwindow *window, int key, int scancode, int action, int mods){
  KeyboardEventSystem::KeyCallBack(static_cast<WindowComponent*>(glfwGetWindowUserPointer(window)), key, scancode, action, mods);
}

void WindowSystem::cursorCallBack(GLFWwindow *window, double xpos, double ypos){
  MouseEventSystem::CursorCallBack(static_cast<WindowComponent*>(glfwGetWindowUserPointer(window)), xpos, ypos);
}

void WindowSystem::windowFocusCallback(GLFWwindow* window, int focused){
  WindowComponent* windowcomp = static_cast<WindowComponent*>(glfwGetWindowUserPointer(window));
  if(windowcomp->mouselocked){
    if(focused){
      LockCursor(*windowcomp);
    }else{
      UnlockCursor(*windowcomp);
    }
  }
}

void WindowSystem::Init() {
  glfwSetErrorCallback(errorCallback);
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
  const char* title = "mainContext";
  mainContext = glfwCreateWindow(1,1,title,NULL,NULL);
  glfwMakeContextCurrent(mainContext);
  glfwWindowHint(GLFW_VISIBLE, GLFW_TRUE);

  gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
}

void WindowSystem::Deinit(){
  for (WindowComponent *w : windows){
    destruct(*w);
  }
  glfwSetErrorCallback(nullptr);
  glfwTerminate();
}

bool WindowSystem::Register(Component* component){
  component->cID = Madd::GetInstance().GetNewComponentID();
  initialize(*dynamic_cast<WindowComponent*>(component));
  windows.push_back(dynamic_cast<WindowComponent*>(component));
  return true;
}

bool WindowSystem::Unregister(Component* component){
  for(auto i = begin(windows); i != end(windows); i++){
    if((*i)->cID == component->cID){
      destruct(**i);
      windows.erase(i);
      return true;
    }
  }
  return false;
}

void WindowSystem::Update(){
  glfwPollEvents();
  for (WindowComponent *w : windows) {
    if(w->update){
      glfwSetWindowTitle(w->window, w->title.c_str());
      glfwSetWindowSize(w->window, w->width, w->height);
      framebufferSizeCallback(w->window, w->width, w->height);
      w->update = false;
    }
  }
}

void WindowSystem::initialize(WindowComponent& w){
  w.window = glfwCreateWindow(w.width, w.height, w.title.c_str(), NULL, mainContext);
  if(w.window == NULL){
    throw w;
  }
  glfwMakeContextCurrent(w.window);
  glfwSetWindowUserPointer(w.window, &w);
  glfwSetKeyCallback(w.window, keyCallBack);
  glfwSetCursorPosCallback(w.window, cursorCallBack);
  glEnable(GL_DEPTH_TEST);

  glfwSetFramebufferSizeCallback(w.window, framebufferSizeCallback);
  framebufferSizeCallback(w.window, w.width, w.height);
}

void WindowSystem::destruct(WindowComponent& w){
    glfwSetFramebufferSizeCallback(w.window, nullptr);
    glfwSetCursorPosCallback(w.window, NULL);
    glfwSetKeyCallback(w.window, NULL);
    glfwDestroyWindow(w.window);
}

std::vector<WindowComponent*>& WindowSystem::GetWindows(){
  return windows;
}

void WindowSystem::Enable(WindowComponent& w){
  glfwMakeContextCurrent(w.window);
}

void WindowSystem::Finish(WindowComponent& w){
  glfwSwapBuffers(w.window);
}

void WindowSystem::LockCursor(WindowComponent& w){
    glfwSetInputMode(w.window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void WindowSystem::UnlockCursor(WindowComponent& w){
    glfwSetInputMode(w.window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);   
}