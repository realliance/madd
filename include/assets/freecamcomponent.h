#pragma once

#include "components/component.h"
#include "components/cameracomponent.h"
#include "event/keycodes.h"
#include "components/keyboardeventcomponent.h"
#include <glm/glm.hpp>

struct FreecamComponent : public Component{
  CameraComponent camera;
  bool mouseLocked = false;
  bool firstCursor = true;
  glm::vec2 lastCursor;
  float movementSpeed = 2.0f;
  float lookSpeed = 0.05f;
  float pitch = 0.0f;
  float yaw = -90.0f;
  glm::vec3 movVector;
  glm::vec2 cursor;
};
