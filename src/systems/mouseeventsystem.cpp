#include "mouseeventsystem.h"
#include <GLFW/glfw3.h>
#include "madd.h"

void MouseEventSystem::Init(){
  glfwSetCursorPosCallback(Madd::GetInstance().GetWindow(), CursorCallBack);
}

void MouseEventSystem::Deinit(){
  subscribers.clear();
  glfwSetCursorPosCallback(Madd::GetInstance().GetWindow(), NULL);
}


void MouseEventSystem::CursorCallBack(GLFWwindow *window, double xpos, double ypos){
    for(auto const c : GetInstance().subscribers) {
      c->callback(c->c, xpos, ypos);
    }
}

MouseEventSystem& MouseEventSystem::GetInstance() {
    static MouseEventSystem instance;
    return instance;
}

bool MouseEventSystem::Register(Component* component){
  component->cID = Madd::GetInstance().GetNewComponentID();
  subscribers.push_back(dynamic_cast<MouseEventComponent*>(component));
  return true;
}

bool MouseEventSystem::Unregister(Component* component){
  for(auto i = begin(subscribers); i != end(subscribers); i++){
    if((*i)->cID == component->cID){
      subscribers.erase(i);
      return true;
    }
  }
  return false;
}

void MouseEventSystem::Update(){
  glfwPollEvents();
}

void MouseEventSystem::LockCursor(){
    glfwSetInputMode(Madd::GetInstance().GetWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void MouseEventSystem::UnlockCursor(){
    glfwSetInputMode(Madd::GetInstance().GetWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);   
}
