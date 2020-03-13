#include "mouseeventsystem.h"
#include "madd.h"

SystemType MouseEventSystem::sType = Madd::GetNewSystemType();

void MouseEventSystem::CursorCallBack(WindowComponent *window, double xpos, double ypos){
    for(auto const c : subscribers) {
      c->callback(c->c, window, xpos, ypos);
    }
}

bool MouseEventSystem::Register(Component* component){
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
