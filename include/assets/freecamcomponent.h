#ifndef FREECAMCOMPONENT_H
#define FREECAMCOMPONENT_H

#include "components/component.h"
#include "components/cameracomponent.h"
#include <glm/glm.hpp>

struct FreecamComponent : public Component{
  CameraComponent camera;
  bool mouseLocked;
  bool firstCursor;
  glm::vec2 lastCursor;
  float movementSpeed = 2.0f;
  float lookSpeed = 0.05f;
  float pitch;
  float yaw;
};

#endif // !FREECAMCOMPONENT_H
