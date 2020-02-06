#pragma once

#include "components/component.h"
#include "components/cameracomponent.h"
#include "keycodes.h"
#include "components/keyboardeventcomponent.h"
#include <glm/glm.hpp>

struct FreecamComponent : public Component{
  FreecamComponent():
    mouseLocked(true),
    movementSpeed(2.0f),
    lookSpeed(0.05f){}

  bool mouseLocked;
  float movementSpeed;
  float lookSpeed;
};
