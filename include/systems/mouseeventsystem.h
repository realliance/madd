#pragma once

#include "system.h"
#include "components/mouseeventcomponent.h"
#include "components/component.h"
#include <vector>

class MouseEventSystem : public System{
  public:
    static MouseEventSystem& GetInstance();
    void Init();
    void Deinit();
    bool Register(Component* component);
    bool Unregister(Component* component);
    void LockCursor();
    void UnlockCursor();
    void Update();
    std::string Name(){ return "MouseEventSystem"; }
    std::vector<std::string> Requires() {return {"GlfwSystem"};};
    MouseEventSystem(const MouseEventSystem&) = delete;
    MouseEventSystem& operator=(const MouseEventSystem&) = delete;
    static void CursorCallBack(WindowComponent *window, double xpos, double ypos);
  private:
    MouseEventSystem() = default;
    std::vector<MouseEventComponent*> subscribers;
}; 

