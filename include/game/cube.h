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
        void ProcessInput(int key, int action);
    private:
        RenderedObject* cubeMesh;
        Madd* context;
        float x,y,z;
};

#endif //CUBE_H