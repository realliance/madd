#ifndef COLLIDER_H
#define COLLIDER_H
#include <glm/glm.hpp>
#include <vector>
#include "components/collidercomponent.h"
#include "components/meshcollidercomponent.h"

class Collider{
  public:
    static bool Collides(ColliderComponent& q, ColliderComponent& p, int maxIteration = 15);
};

#endif //COLLIDER_H
