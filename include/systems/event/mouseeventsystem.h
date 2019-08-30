#pragma once

#include "system.h"
#include "components/mouseeventcomponent.h"
#include "components/component.h"
#include <vector>

class GLFWwindow;
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
    MouseEventSystem(const MouseEventSystem&) = delete;
    MouseEventSystem& operator=(const MouseEventSystem&) = delete;
  private:
    MouseEventSystem() = default;
    static void CursorCallBack(GLFWwindow *window, double xpos, double ypos);
    std::vector<MouseEventComponent*> subscribers;
}; 

