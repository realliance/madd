#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "components/cameracomponent.h"
#include "components/component.h"
#include "system.h"
#include <unordered_map>

class CameraSystem : public System{
  public:
    void Init();
    ~CameraSystem();
    bool Register(Component* component);
    bool Unregister(Component* component);
    void Update();
    std::string Name() { return "CameraSystem"; }
    std::vector<std::string> Requires() {return {};};

    glm::mat4* View(CameraComponent* c);
    glm::mat4* Projection(CameraComponent* c);
    
  private:
    struct CameraData{
      CameraData(){}
      CameraData(CameraComponent* cam): 
        cam(cam),
        front(glm::vec3(0.0f, 0.0f, 1.0f)), 
        up(glm::vec3(0.0f, 1.0f, 0.0f)),
        projection(glm::mat4(1.0f)){
          view = glm::lookAt(cam->pos, cam->pos + front, up);
        }
      CameraComponent* cam;
      glm::vec3 front;
      glm::vec3 up;
      glm::mat4 view;
      glm::mat4 projection;
    };
    std::unordered_map<ComponentID,CameraData> cameradata;
    void destruct(CameraComponent& c);
    void updateComponent(CameraData& c);
};
