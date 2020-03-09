#pragma once

#include "system.h"
#include "components/mouseeventcomponent.h"
#include "component.h"
#include <vector>

class MouseEventSystem : public System{
  public:
    void Init(){}
    void Deinit(){}
    bool Register(Component* component);
    bool Unregister(Component* component);
    void LockCursor();
    void UnlockCursor();
    void Update(){}
    std::vector<ComponentType> ComponentTypes() { return {MouseEventComponent{}.Type()};}
    std::string Name(){ return "MouseEventSystem"; }
    SystemType Type() { return sType; }
    std::vector<std::string> Requires() {return {"GlfwSystem"};};
    void CursorCallBack(WindowComponent *window, double xpos, double ypos);
  private:
    std::vector<MouseEventComponent*> subscribers;
    static SystemType sType;
}; 

