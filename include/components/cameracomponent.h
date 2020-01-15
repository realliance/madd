#pragma once

#include "components/component.h"
#include <glm/glm.hpp>

class CameraSystem;
struct CameraComponent : public Component{
  glm::vec3 pos;
  glm::vec3 lookAt;
  float fov;
  float aspectratio;
  float near;
  float far;

  glm::vec3 front;
  glm::vec3 up;
  glm::mat4 view;
  glm::mat4 projection;
};


