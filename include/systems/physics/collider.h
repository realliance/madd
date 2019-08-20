#ifndef COLLIDER_H
#define COLLIDER_H
#include <glm/glm.hpp>
#include <vector>

class Collider{
    public:
        Collider(std::vector<glm::vec3> collisionMesh);
        bool Collides(Collider& collider, int maxIteration = 5);
        const std::vector<glm::vec3>& getCollisionMesh();
        glm::vec3 getCenter();
        void updateModel(glm::mat4 newModel);
    private:
        glm::vec3 support(glm::vec3 dir);
        bool collides(Collider& p, Collider& q, int maxIteration);
        std::vector<glm::vec3> originalMesh;
        std::vector<glm::vec3> collisionMesh;
        glm::vec3 colliderCenter;
};

#endif //COLLIDER_H
