#pragma once

#include <vector>
#include "components/component.h"
#include <glm/glm.hpp>
#include <sys/types.h>

struct MeshComponent : public Component{
  std::vector<glm::vec3> verts;
  std::vector<glm::vec2> texcoords;
};


