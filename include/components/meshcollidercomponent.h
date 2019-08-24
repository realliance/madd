#ifndef MESHCOLLIDERCOMPONENT_H
#define MESHCOLLIDERCOMPONENT_H

#include <vector>
#include <glm/glm.hpp>
#include "components/collidercomponent.h"

class MeshColliderComponent : public ColliderComponent{
  public:
    glm::mat4 model;
    std::vector<glm::vec3> mesh;
    glm::vec3 GetCenter();
    glm::vec3 Support(glm::vec3 dir);
};

#endif // !MESHCOLLIDERCOMPONENT_H

