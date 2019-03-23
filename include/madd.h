#ifndef MADD_H
#define MADD_H

#include <vector>
#include <chrono>
/** Type Definition for chrono clock shorthand */
typedef std::chrono::high_resolution_clock Clock;
/** Type Definition for chrono time_point shorthand */
typedef Clock::time_point Time;


class GameObject;
class Renderer;
class Camera;
class EventHandler;
struct GLFWwindow;
class Madd {
public:
    void Init(int width, int height, const char *title);
    static Madd& GetInstance();
    ~Madd();
    void Tick();
    void AddObject(GameObject* obj);
    bool StayOpen(){return !close;}
    void Close(){close = true;}
    void SetMainCamera(Camera* cameraObj);
    Camera* GetMainCamera();
    EventHandler* GetEventHandler();
    double GetTime();
    float GetDeltaTime();
    int GetWidth();
    int GetHeight();
    GLFWwindow* GetWindow();
    void ProcessInput(int key, int action);
    Madd(const Madd&) = delete;
    Madd& operator=(const Madd&) = delete;
private:
    Madd() = default;
    std::vector<GameObject*> objs;
    Camera* mainCamera = nullptr;
    void ReloadShader();
    void UpdateDeltaTime();
    std::chrono::duration<float> dTime;
    bool close = false;
    int width;
    int height;
    float timeScale = 1.0f;
    Time lastFrame = Clock::now();
};

#endif // MADD_H