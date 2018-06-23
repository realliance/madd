#ifndef MADD_H
#define MADD_H

#include <vector>
#include "gameobject.h"
#include "renderer.h"

class Madd {
public:
    Madd(int width, int height, const char *title);
    virtual ~Madd();
    void Tick();
    void addObject(GameObject* obj);
    bool stayOpen(){return !close;}
    virtual float GetTime(){return glfwGetTime();}
private:
    Renderer* render;
    std::vector<GameObject*> objs;
    void ProcessInput();
    bool ReloadShader();
    bool close;
};

#endif // MADD_H