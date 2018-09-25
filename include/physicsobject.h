#ifndef PHYSICSOBJECT_H
#define PHYSICSOBJECT_H

#include "gameobject.h"
class PhysicsObject : public GameObject{
    public:
        PhysicsObject();
        ~PhysicsObject();
        virtual Madd* GetContext()=0;
        virtual bool ReloadShaders()=0;
        virtual bool Render()=0;
        virtual bool Update()=0;
}

#endif //PHYSICSOBJECT_H