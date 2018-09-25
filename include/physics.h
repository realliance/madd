#ifndef PHYSICS_H
#define PHYSICS_H

#include <btBulletCollisionCommon.h>
class Physics{
    public:
        Physics();
        ~Physics();
        void Tick();
    private:
        btDefaultCollisionConfiguration* collisionConfig;
        btCollisionDispatcher* dispatcher;
        btBroadphaseInterface* overlappingPairCache;
        btSequentialImpulseConstraintSolver* solver;
        btDiscreteDynamicsWorld* dynamicsWorld;

        btAlignedObjectArray<btCollisionShape*> collisionShapes;

};

#endif //PHYSICS_H