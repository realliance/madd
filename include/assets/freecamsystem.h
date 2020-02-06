#pragma once
#include "camerasystem.h"
#include <glm/glm.hpp>
#include <unordered_map>
#include "components/cameracomponent.h"
#include "assets/freecamcomponent.h"
#include "components/windowcomponent.h"

class FreeCamSystem : public System {
  public:
    ~FreeCamSystem();
    void Init();
    bool Register(Component* component);
    bool Unregister(Component* component);
    void Update();
    std::string Name() { return "FreeCamSystem"; }
    std::vector<std::string> Requires() {return {"CameraSystem"};};

    CameraComponent* Camera(FreecamComponent* freecam);
  private:
    struct FreeCamData{
      FreeCamData(){}
      FreeCamData(FreecamComponent* freecam):
        freecam(freecam),
        camera(CameraComponent()),
        pitch(0.f),
        yaw(-90.f),
        movVector(glm::vec3(0.f,0.f,0.f)),
        lastCursor(glm::vec2(0.f,0.f)),
        cursor(glm::vec2(0.f,0.f)){}
      FreecamComponent* freecam;
      CameraComponent camera;
      float pitch = 0.0f;
      float yaw = -90.0f;
      glm::vec3 movVector;
      glm::vec2 lastCursor;
      glm::vec2 cursor;
    }; 
    std::unordered_map<ComponentID, FreeCamData> freecamdata;
    // static void toggleMouseLock(FreecamComponent& c, WindowComponent* window, int key=0, int action=1);
    void processMove(FreeCamData& c);        
    void processCursor(FreeCamData& c);
    glm::vec3 pitchAndYawVector(float pitch, float yaw);
};

