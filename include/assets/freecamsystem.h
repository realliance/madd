#pragma once
#include "camerasystem.h"
#include <glm/glm.hpp>
#include <vector>
#include "components/cameracomponent.h"
#include "assets/freecamcomponent.h"
class FreeCamSystem : public System {
  public:
    static FreecamComponent Construct();
    void Deinit();
    void Init();
    bool Register(Component* component);
    bool Unregister(Component* component);
    void Update();
    std::string Name() { return "FreeCamSystem"; }
    static void ToggleMouseLock(FreecamComponent& c, int key=0, int action=1);
  private:
    std::vector<FreecamComponent*> freecams;
    static void ProcessMove(FreecamComponent& c);        
    static void ProcessCursor(FreecamComponent& c);
};

