#pragma once

#include "system.h"
#include "components/mouseeventcomponent.h"
#include "components/component.h"
#include <vector>

class MouseEventSystem : public System{
  public:
    void Init();
    ~MouseEventSystem();
    bool Register(Component* component);
    bool Unregister(Component* component);
    void LockCursor();
    void UnlockCursor();
    void Update();
    std::vector<ComponentType> Types() { return {MouseEventComponent{}.Type()};}
    std::string Name(){ return "MouseEventSystem"; }
    std::vector<std::string> Requires() {return {"GlfwSystem"};};
    void CursorCallBack(WindowComponent *window, double xpos, double ypos);
  private:
    std::vector<MouseEventComponent*> subscribers;
}; 

