#pragma once

#include "system.h"
#include "components/keyboardeventcomponent.h"
#include "components/component.h"
#include <vector>

class GLFWwindow;
class KeyboardEventSystem : public System{
  public:
    static KeyboardEventSystem& GetInstance();
    void Deinit();
    void Init();
    bool Register(Component* component);
    bool Unregister(Component* component);
    void Update();
    std::string Name(){ return "KeyboardEventSystem"; }
    KeyboardEventSystem(const KeyboardEventSystem&) = delete;
    KeyboardEventSystem& operator=(const KeyboardEventSystem&) = delete;
  private:
    KeyboardEventSystem() = default;
    static void KeyCallBack(GLFWwindow *window, int key, int scancode, int action, int mods);
    std::vector<KeyboardEventComponent*> subscribers;
}; 

