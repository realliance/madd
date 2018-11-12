#ifndef PHYSICSOBJECT_H
#define PHYSICSOBJECT_H

#include <btBulletDynamicsCommon.h>
#include "renderedobject.h"
#include "collider.h"
class PhysicsObject{
    public:
        PhysicsObject(RenderedObject* position, Collider* collisionShape);
        ~PhysicsObject();
    private:
        btRigidBody* rigidBody;
        RenderedObject* position;

};

#endif //PHYSICSOBJECT_H