#ifndef MOUSEEVENTSYSTEM_H
#define MOUSEEVENTSYSTEM_H

#include "system.h"
#include "components/mouseeventcomponent.h"
#include "components/component.h"
#include <vector>

class GLFWwindow;
class MouseEventSystem : public System<MouseEventComponent>{
  public:
    static MouseEventSystem& GetInstance();
    bool Init();
    bool Deinit();
    bool Register(MouseEventComponent* component);
    bool Deregister(MouseEventComponent* component);
    void Update();
    MouseEventSystem(const MouseEventSystem&) = delete;
    MouseEventSystem& operator=(const MouseEventSystem&) = delete;
  private:
    MouseEventSystem() = default;
    static void CursorCallBack(GLFWwindow *window, double xpos, double ypos);
    std::vector<MouseEventComponent*> subscribers;
    //TODO: Replace with component manager id
    ComponentID currID;
}; 

#endif // !MOUSEEVENTSYSTEM_H
