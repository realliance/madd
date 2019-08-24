#ifndef KEYBOARDEVENTSYSTEM_H
#define KEYBOARDEVENTSYSTEM_H

#include "system.h"
#include "components/keyboardeventcomponent.h"
#include "components/component.h"
#include <vector>

class GLFWwindow;
class KeyboardEventSystem : public System<KeyboardEventComponent>{
  public:
    static KeyboardEventSystem& GetInstance();
    bool Init();
    bool Deinit();
    bool Register(KeyboardEventComponent* component);
    bool Deregister(KeyboardEventComponent* component);
    void Update();
    KeyboardEventSystem(const KeyboardEventSystem&) = delete;
    KeyboardEventSystem& operator=(const KeyboardEventSystem&) = delete;
  private:
    KeyboardEventSystem() = default;
    static void KeyCallBack(GLFWwindow *window, int key, int scancode, int action, int mods);
    std::vector<KeyboardEventComponent*> subscribers;
    //TODO: Replace with component manager id
    ComponentID currID;
}; 

#endif // !KEYBOARDEVENTSYSTEM_H
