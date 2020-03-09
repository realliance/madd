#pragma once

#include "system.h"
#include "components/keyboardeventcomponent.h"
#include "component.h"
#include <vector>

class KeyboardEventSystem : public System{
  public:
    void Deinit(){}
    void Init(){}
    bool Register(Component* component);
    bool Unregister(Component* component);
    void Update(){}
    std::vector<ComponentType> ComponentTypes() { return {KeyboardEventComponent{}.Type()};}
    std::string Name(){ return "KeyboardEventSystem"; }
    SystemType Type() { return sType; }
    std::vector<std::string> Requires() {return {"GlfwSystem"};};
    void KeyCallBack(WindowComponent *window, int key, int scancode, int action, int mods);
  private:
    std::vector<KeyboardEventComponent*> subscribers;
    static SystemType sType;
}; 

