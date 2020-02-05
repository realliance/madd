#pragma once

#include <vector>
#include "components/component.h"
#include <glm/glm.hpp>
#include <sys/types.h>
#include <string>

struct MeshComponent : public Component{
  std::string modelPath;
};


