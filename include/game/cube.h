#ifndef CUBE_H
#define CUBE_H
#include "gameobject.h"
#include "renderedobject.h"
class Madd;
class Cube : public GameObject{
    public:
        Cube(Madd* context);
        ~Cube();
        Madd* GetContext(){return context;};
        bool Render();
        bool Update();
        bool ReloadShaders();
    private:
        RenderedObject* cubeMesh;
        Madd* context;
};

#endif //CUBE_H