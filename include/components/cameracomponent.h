#pragma once

#include "components/component.h"
#include <glm/glm.hpp>

class CameraSystem;
struct CameraComponent : public Component{
  glm::vec3 pos;
  glm::vec3 lookAt;
  bool active;
  float fov;

  glm::vec3 front;
  glm::vec3 up;
  glm::mat4 view;
  glm::mat4 projection;
  friend class CameraSystem;
private:
  glm::vec3 _pos;
  glm::vec3 _lookAt;
  float _fov;
};


