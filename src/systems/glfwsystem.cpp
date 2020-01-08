#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "glfwsystem.h"
#include "madd.h"
#include "camerasystem.h"
#include "keyboardeventsystem.h"
#include "mouseeventsystem.h"
#include "meshsystem.h"


void GlfwSystem::errorCallback(int, const char* err_str) {
    std::cout << "GLFW Error: " << err_str << std::endl;
}

void APIENTRY GlfwSystem::glDebugOutput(uint source, uint type, uint id, uint severity, 
                            int length, const char *message, const void *userParam){
  printf( "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
          ( type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "" ),
          type, severity, message );
  
}

void GlfwSystem::framebufferSizeCallback(GLFWwindow *window, int width, int height) {
    WindowComponent* windowcomp = static_cast<WindowComponent*>(glfwGetWindowUserPointer(window));
    glfwMakeContextCurrent(window);
    glViewport(0, 0, width, height);
    for(CameraComponent* c : windowcomp->cameras){
      c->aspectratio = (float) width/height;
      CameraSystem::UpdateProjection(*c, width, height);
    }
}

void GlfwSystem::EnableDebuggingContext(){
  debugcontext = true;
}

void GlfwSystem::keyCallBack(GLFWwindow *window, int key, int scancode, int action, int mods){
  dynamic_cast<KeyboardEventSystem*>(Madd::GetInstance().GetSystem("KeyboardEventSystem"))->KeyCallBack(static_cast<WindowComponent*>(glfwGetWindowUserPointer(window)), key, scancode, action, mods);
}

void GlfwSystem::cursorCallBack(GLFWwindow *window, double xpos, double ypos){
  dynamic_cast<MouseEventSystem*>(Madd::GetInstance().GetSystem("MouseEventSystem"))->CursorCallBack(static_cast<WindowComponent*>(glfwGetWindowUserPointer(window)), xpos, ypos);
}

void GlfwSystem::windowFocusCallback(GLFWwindow* window, int focused){
  WindowComponent* windowcomp = static_cast<WindowComponent*>(glfwGetWindowUserPointer(window));
   GlfwSystem* glfwsys= dynamic_cast<GlfwSystem*>(Madd::GetInstance().GetSystem("GlfwSystem"));
  if(windowcomp->mouselocked){
    if(focused){
      glfwsys->LockCursor(*windowcomp);
    }else{
      glfwsys->UnlockCursor(*windowcomp);
    }
  }
}

bool GlfwSystem::debugcontext = false;

void GlfwSystem::Init() {
  glfwSetErrorCallback(errorCallback);
  if(!glfwInit()){
    std::cout << "GLFW failed to init" << std::endl;
  }
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  if(debugcontext == true){
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE); 
  }
  glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
  const char* title = "mainContext";
  mainContext = glfwCreateWindow(1,1,title,NULL,NULL);
  glfwMakeContextCurrent(mainContext);
  glfwWindowHint(GLFW_VISIBLE, GLFW_TRUE);

  gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

  GLint flags; 
  glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
  if (flags & GL_CONTEXT_FLAG_DEBUG_BIT){
     glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS); 
    glDebugMessageCallback(glDebugOutput, nullptr);
    glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
    std::cout << "GL Debug Output Enabled" << std::endl;
  }

  meshsystem = dynamic_cast<MeshSystem*>(Madd::GetInstance().GetSystem("MeshSystem"));
}



GlfwSystem::~GlfwSystem(){
  for (WindowComponent *w : windows){
    destruct(*w);
  }
  glfwSetErrorCallback(nullptr);
  glfwTerminate();
}

bool GlfwSystem::Register(Component* component){
  component->cID = Madd::GetInstance().GetNewComponentID();
  initialize(*dynamic_cast<WindowComponent*>(component));
  windows.push_back(dynamic_cast<WindowComponent*>(component));
  return true;
}

bool GlfwSystem::Unregister(Component* component){
  for(auto i = begin(windows); i != end(windows); i++){
    if((*i)->cID == component->cID){
      destruct(**i);
      windows.erase(i);
      return true;
    }
  }
  return false;
}

void GlfwSystem::Update(){
  glfwPollEvents();
  for (WindowComponent *w : windows) {
    if(w->update){
      glfwSetWindowTitle(glfwWindows[w->cID], w->title.c_str());
      glfwSetWindowSize(glfwWindows[w->cID], w->width, w->height);
      framebufferSizeCallback(glfwWindows[w->cID], w->width, w->height);
      w->update = false;
    }
  }
}

void GlfwSystem::initialize(WindowComponent& w){
  glfwWindows[w.cID] = glfwCreateWindow(w.width, w.height, w.title.c_str(), NULL, mainContext);
  if(glfwWindows[w.cID] == NULL){
    throw w;
  }
  glfwMakeContextCurrent(glfwWindows[w.cID]);
  glfwSetWindowUserPointer(glfwWindows[w.cID], &w);
  glfwSetKeyCallback(glfwWindows[w.cID], keyCallBack);
  glfwSetCursorPosCallback(glfwWindows[w.cID], cursorCallBack);
  glEnable(GL_DEPTH_TEST);

  glfwSetFramebufferSizeCallback(glfwWindows[w.cID], framebufferSizeCallback);
  framebufferSizeCallback(glfwWindows[w.cID], w.width, w.height);
  glfwMakeContextCurrent(mainContext);
}

void GlfwSystem::destruct(WindowComponent& w){
    glfwSetFramebufferSizeCallback(glfwWindows[w.cID], nullptr);
    glfwSetCursorPosCallback(glfwWindows[w.cID], NULL);
    glfwSetKeyCallback(glfwWindows[w.cID], NULL);
    glfwDestroyWindow(glfwWindows[w.cID]);
}

std::vector<WindowComponent*>& GlfwSystem::GetWindows(){
  return windows;
}

void GlfwSystem::Enable(WindowComponent& w){
  glfwMakeContextCurrent(glfwWindows[w.cID]);
}

void GlfwSystem::Finish(WindowComponent& w){
  glfwSwapBuffers(glfwWindows[w.cID]);
}

void GlfwSystem::LockCursor(WindowComponent& w){
    glfwSetInputMode(glfwWindows[w.cID], GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void GlfwSystem::UnlockCursor(WindowComponent& w){
    glfwSetInputMode(glfwWindows[w.cID], GLFW_CURSOR, GLFW_CURSOR_NORMAL);   
}

WindowComponent* GlfwSystem::GetCurrentWindow(){
  if(glfwGetCurrentContext() != NULL){
    return static_cast<WindowComponent*>(glfwGetWindowUserPointer(glfwGetCurrentContext()));
  }
  return NULL;
}

uint GlfwSystem::GetCurrentContextVAO(Component* c, std::function<uint(Component*)> CreateVAO){
  if(!VAOs.contains({c->cID,GetCurrentWindow()->cID})){
    VAOs[{c->cID,GetCurrentWindow()->cID}] = CreateVAO(c);
  }
  return VAOs[{c->cID,GetCurrentWindow()->cID}];
}

void GlfwSystem::DeleteComponentVAO(Component* c){
  for(WindowComponent* w : windows){
    if(VAOs.contains({c->cID,GetCurrentWindow()->cID})){
      glDeleteVertexArrays(1, &VAOs[{c->cID,GetCurrentWindow()->cID}]);
      VAOs.erase({c->cID,GetCurrentWindow()->cID});
    }
  }
}
