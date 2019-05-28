#ifndef BOXCOLLIDER_H
#include "collider.h"
#include <vector>
#include <glm/glm.hpp>

class BoxCollider: public Collider{
  public:
    BoxCollider(std::vector<float>& vertices, int stride);
    bool Collides();
  private:
    glm::vec3 minBox;
    glm::vec3 maxBox;
    glm::vec3 origin;
};

#endif // !BOXCOLLIDER_H
