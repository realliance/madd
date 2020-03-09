#pragma once
#include <glm/glm.hpp>
#include "components/cameracomponent.h"
#include "component.h"
#include "system.h"
#include <vector>

class CameraSystem : public System{
  public:
    void Init(){}
    void Deinit(){}
    bool Register(Component* component);
    bool Unregister(Component* component);
    void Update();

    std::vector<ComponentType> ComponentTypes() { return {CameraComponent{}.Type()};}
    std::string Name() { return "CameraSystem"; }
    SystemType Type() { return sType; }
    std::vector<std::string> Requires() {return {};};
    static CameraComponent Construct();
    void Destruct(CameraComponent& c);
    static void UpdateProjection(CameraComponent& c, int width, int height);
    static glm::vec3 PitchAndYawVector(CameraComponent& c, float pitch, float yaw);
  private:
    void updateComponent(CameraComponent& c);
    std::vector<CameraComponent*> cameras;
    static SystemType sType;
};
