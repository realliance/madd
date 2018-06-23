#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

class Madd;
class GameObject{
    public:
        GameObject(){};
        virtual ~GameObject(){};
        virtual Madd* GetContext()=0;
        virtual bool ReloadShaders()=0;
        virtual bool Render()=0;
        virtual bool Update()=0;
};

#endif //GAMEOBJECT_H