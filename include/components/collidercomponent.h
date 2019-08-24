#ifndef COLLIDERCOMPONENT_H
#define COLLIDERCOMPONENT_H

#include "components/component.h"
#include <glm/glm.hpp>

class ColliderComponent : public Component{
  public:
    virtual glm::vec3 GetCenter() = 0;
    virtual glm::vec3 Support(glm::vec3 dir) = 0;
};

#endif // !COLLIDERCOMPONENT_H
