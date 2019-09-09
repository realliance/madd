#pragma once
#include <glm/glm.hpp>
#include "components/cameracomponent.h"
#include "components/component.h"
#include "system.h"
#include <vector>

class CameraSystem : public System{
  public:
    void Init();
    void Deinit();
    bool Register(Component* component);
    bool Unregister(Component* component);
    void Update();

    std::string Name() { return "CameraSystem"; }
    std::vector<CameraComponent*>& GetCameras();
    static CameraComponent Construct();
    void Destruct(CameraComponent& c);
    void UpdateProjection(CameraComponent& c, int width, int height);
    static glm::vec3 PitchAndYawVector(CameraComponent& c, float pitch, float yaw);
  private:
    void updateComponent(CameraComponent& c);
    std::vector<CameraComponent*> cameras;
};
