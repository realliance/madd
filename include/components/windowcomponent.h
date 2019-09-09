#pragma once

#include <sys/types.h>
#include <string>
#include <vector>

#include "components/component.h"
#include "components/cameracomponent.h"


class GLFWwindow;
class WindowSystem;
class WindowComponent : public Component{
  public:
    std::string title;
    uint width;
    uint height;
    std::vector<CameraComponent*> cameras;
    bool mouselocked;
  friend class WindowSystem;
  private:
    GLFWwindow* window;
};

