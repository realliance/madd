#ifndef COLLIDER_H
#define COLLIDER_H
#include <glm/glm.hpp>
#include <vector>

class Collider{
    public:
        Collider(std::vector<glm::vec3> collisionMesh);
        bool Collides(std::vector<glm::vec3>& collider, glm::vec3 pos, glm::mat4 model, glm::vec3 center, int maxIteration = 16);
    private:
        static glm::vec3 support(std::vector<glm::vec3> points, glm::vec3 dir);
        bool collides(std::vector<glm::vec3>& p, std::vector<glm::vec3>& q, glm::vec3 pcenter, int maxIteration);
        std::vector<glm::vec3> collisionMesh;
        glm::vec3 colliderCenter;
};

#endif //COLLIDER_H
