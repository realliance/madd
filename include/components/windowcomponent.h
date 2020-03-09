#pragma once

#include <sys/types.h>
#include <string>
#include <vector>

#include "component.h"
#include "components/cameracomponent.h"

class WindowComponent : public Component{
  public:
    std::string title;
    uint width;
    uint height;
    std::vector<CameraComponent*> cameras;
    bool mouselocked;
    static ComponentType cType;
    ComponentType Type();
};

