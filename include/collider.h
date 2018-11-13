#ifndef COLLIDER_H
#define COLLIDER_H
#include <btBulletCollisionCommon.h>
#include <glm/glm.hpp>
#include <vector>

enum EColliderShape {
    box,
    sphere
};

class Collider{
    public:
        Collider(EColliderShape shape, std::vector<float>& vertices, int stride);
        ~Collider();

    private:
        void CreateBoxCollisionShape(std::vector<float>& vertices, int stride);
        void CreateSphereCollisionShape(std::vector<float>& vertices, int stride);
        btCollisionShape* shape;
};

#endif //COLLIDER_H