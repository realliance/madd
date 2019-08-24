#include "keyboardeventsystem.h"
#include <GLFW/glfw3.h>
#include "madd.h"

bool KeyboardEventSystem::Init(){
  glfwSetKeyCallback(Madd::GetInstance().GetWindow(), KeyCallBack);
  return true;
}

bool KeyboardEventSystem::Deinit(){
  return true;
}

void KeyboardEventSystem::KeyCallBack(GLFWwindow *window, int key, int scancode, int action, int mods){
    for(auto const c : GetInstance().subscribers) {
        if((c->mods == mods || c->mods == 0) && c->code == key) {
            c->callback(c->c, key, action);
        }
    }
}

KeyboardEventSystem& KeyboardEventSystem::GetInstance() {
    static KeyboardEventSystem instance;
    return instance;
}

bool KeyboardEventSystem::Register(KeyboardEventComponent* component){
  component->cID = ++currID;
  subscribers.push_back(component);
  return true;
}

bool KeyboardEventSystem::Deregister(KeyboardEventComponent* component){
  for(auto i = begin(subscribers); i != end(subscribers); i++){
    if((*i)->cID == component->cID){
      subscribers.erase(i);
      return true;
    }
  }
  return false;
}

void KeyboardEventSystem::Update(){}
