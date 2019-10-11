#pragma once

#include "system.h"
#include "components/keyboardeventcomponent.h"
#include "components/component.h"
#include <vector>

class KeyboardEventSystem : public System{
  public:
    static KeyboardEventSystem& GetInstance();
    void Deinit();
    void Init();
    bool Register(Component* component);
    bool Unregister(Component* component);
    void Update();
    std::string Name(){ return "KeyboardEventSystem"; }
    std::vector<std::string> Requires() {return {"GlfwSystem"};};
    KeyboardEventSystem(const KeyboardEventSystem&) = delete;
    KeyboardEventSystem& operator=(const KeyboardEventSystem&) = delete;
    static void KeyCallBack(WindowComponent *window, int key, int scancode, int action, int mods);
  private:
    KeyboardEventSystem() = default;
    std::vector<KeyboardEventComponent*> subscribers;
}; 

