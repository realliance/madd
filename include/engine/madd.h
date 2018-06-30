#ifndef MADD_H
#define MADD_H

#include <vector>
#include "gameobject.h"
#include "renderer.h"
#include "camera.h"

class Madd {
public:
    Madd(int width, int height, const char *title);
    virtual ~Madd();
    void Tick();
    void addObject(GameObject* obj);
    bool stayOpen(){return !close;}
    Camera* GetMainCamera();
    virtual float GetTime(){return glfwGetTime();}
    int GetWidth();
    int GetHeight();
    void SetHeightWidth(int _height, int _width);
private:
    Renderer* render;
    std::vector<GameObject*> objs;
    Camera* mainCamera;
    void ProcessInput();
    bool ReloadShader();
    bool close;
    int width;
    int height;
};

#endif // MADD_H