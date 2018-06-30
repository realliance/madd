#ifndef MADD_H
#define MADD_H

#include <vector>

class GameObject;
class Renderer;
class Camera;
class EventHandler;
class Madd {
public:
    Madd(int width, int height, const char *title);
    ~Madd();
    void Tick();
    void AddObject(GameObject* obj);
    bool StayOpen(){return !close;}
    void Close(){close = true;}
    Camera* GetMainCamera();
    float GetTime();
    int GetWidth();
    int GetHeight();
    void* GetWindow();
    void SetHeightWidth(int _height, int _width);
    void ProcessInput(int key, int action);
private:
    Renderer* render;
    std::vector<GameObject*> objs;
    Camera* mainCamera;
    EventHandler* event;
    void ReloadShader();
    bool close;
    int width;
    int height;
};

#endif // MADD_H