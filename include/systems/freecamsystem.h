#pragma once
#include "camerasystem.h"
#include <glm/glm.hpp>
#include <vector>
#include "components/cameracomponent.h"
#include "components/freecamcomponent.h"
#include "components/windowcomponent.h"
class FreeCamSystem : public System {
  public:
    static FreecamComponent Construct();
    void Deinit(){}
    void Init(){}
    bool Register(Component* component);
    bool Unregister(Component* component);
    void Update();
    std::vector<ComponentType> ComponentTypes() { return {FreecamComponent{}.Type()};}
    std::string Name() { return "FreeCamSystem"; }
    SystemType Type() { return sType; }
    std::vector<std::string> Requires() {return {"CameraSystem"};};
    static void ToggleMouseLock(FreecamComponent& c, WindowComponent* window, int key=0, int action=1);
  private:
    std::vector<FreecamComponent*> freecams;
    static void ProcessMove(FreecamComponent& c);        
    static void ProcessCursor(FreecamComponent& c);
    static SystemType sType;
};

