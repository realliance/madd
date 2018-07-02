#ifndef CUBE_H
#define CUBE_H
#include "gameobject.h"
#include "renderedobject.h"
#include <vector>
#include <glm/glm.hpp>
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
        std::vector<glm::vec3> cubePositions;
        Madd* context;
};

#endif //CUBE_H