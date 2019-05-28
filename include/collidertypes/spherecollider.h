#ifndef SPHERECOLLIDER_H
#include "collider.h"
#include <vector>
#include <glm/glm.hpp>

class SphereCollider: public Collider{
  public:
    SphereCollider(std::vector<float>& vertices, int stride);
    bool Collides();
  private:
    glm::vec3 origin;
    float radius;
};

#endif // !SPHERECOLLIDER_H
