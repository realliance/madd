#pragma once

#include "components/component.h"
#include <glm/glm.hpp>

class CameraSystem;
struct CameraComponent : public Component{
  CameraComponent(): 
    pos(glm::vec3(0.f,0.f,0.f)), 
    lookAt(glm::vec3(0.f, 0.f, 1.f)),
    fov(45.f), 
    aspectratio(16.f/9.f), 
    near(0.1f), 
    far(100.f) {}
    
  glm::vec3 pos;
  glm::vec3 lookAt;
  float fov;
  float aspectratio;
  float near;
  float far;
};


