#include "keyboardeventsystem.h"
#include "madd.h"

void KeyboardEventSystem::Init(){
  
}

void KeyboardEventSystem::Deinit(){
  subscribers.clear();
}


void KeyboardEventSystem::KeyCallBack(WindowComponent *window, int key, int scancode, int action, int mods){
    for(auto const c : GetInstance().subscribers) {
        if((c->mods == mods || c->mods == 0) && c->code == key) {
            c->callback(c->c, window, key, action);
        }
    }
}

KeyboardEventSystem& KeyboardEventSystem::GetInstance() {
    static KeyboardEventSystem instance;
    return instance;
}

bool KeyboardEventSystem::Register(Component* component){
  component->cID = Madd::GetInstance().GetNewComponentID();
  subscribers.push_back(dynamic_cast<KeyboardEventComponent*>(component));
  return true;
}

bool KeyboardEventSystem::Unregister(Component* component){
  for(auto i = begin(subscribers); i != end(subscribers); i++){
    if((*i)->cID == component->cID){
      subscribers.erase(i);
      return true;
    }
  }
  return false;
}

void KeyboardEventSystem::Update(){
}
