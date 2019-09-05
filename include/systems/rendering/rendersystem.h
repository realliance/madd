#pragma once

#include "system.h"
#include "components/renderedcomponent.h"
#include "components/cameracomponent.h"

class Madd;
struct GLFWwindow;
class RenderSystem : public System{
    public:
        static RenderSystem& GetInstance();
        void Deinit();
        void Init();
        bool Register(Component* component);
        bool Unregister(Component* component);
        void Update();

        std::string Name(){ return "RenderSystem"; }
        static void FramebufferSizeCallback(GLFWwindow * window, int width, int height);
        static void ErrorCallback(int, const char * err_str);
        GLFWwindow* GetWindow(){return window;}
        void Start();
        void Finish();
        int GetHeight();
        int GetWidth();
        
        RenderSystem(const RenderSystem&) = delete;
        RenderSystem& operator=(const RenderSystem&) = delete;
    private:
        void updateComponent(RenderedComponent& r, CameraComponent& c);
        RenderSystem() = default;
        GLFWwindow* window;
        std::vector<RenderedComponent*> objects;
};

