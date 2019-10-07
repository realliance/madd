#pragma once

#include <vector>
#include <glm/glm.hpp>
#include "components/collidercomponent.h"
#include "components/meshcomponent.h"

class MeshColliderComponent : public ColliderComponent{
  public:
    glm::mat4 model;
    MeshComponent* mesh;
    glm::vec3 GetCenter();
    glm::vec3 Support(glm::vec3 dir);
};


