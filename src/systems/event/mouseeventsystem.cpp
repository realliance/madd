#include "mouseeventsystem.h"
#include <GLFW/glfw3.h>
#include "madd.h"

bool MouseEventSystem::Init(){
  glfwSetCursorPosCallback(Madd::GetInstance().GetWindow(), CursorCallBack);
  return true;
}

bool MouseEventSystem::Deinit(){
  return true;
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

bool MouseEventSystem::Register(MouseEventComponent* component){
  component->cID = ++currID;
  subscribers.push_back(component);
  return true;
}

bool MouseEventSystem::Deregister(MouseEventComponent* component){
  for(auto i = begin(subscribers); i != end(subscribers); i++){
    if((*i)->cID == component->cID){
      subscribers.erase(i);
      return true;
    }
  }
  return false;
}

void MouseEventSystem::Update(){}
