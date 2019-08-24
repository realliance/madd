#ifndef CAMERACOMPONENT_H
#define CAMERACOMPONENT_H

#include "components/component.h"
#include <glm/glm.hpp>

struct CameraComponent : public Component{
  glm::vec3 pos;
  glm::vec3 front;
  glm::vec3 up;
  glm::mat4 view;
  glm::mat4 projection;
};

#endif // !CAMERACOMPONENT_H

