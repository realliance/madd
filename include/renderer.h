#ifndef RENDERER_H
#define RENDERER_H
#include <glad/glad.h>

class Madd;
struct GLFWwindow;
class Renderer{
    public:
        static void FramebufferSizeCallback(GLFWwindow * window, int width, int height);
        static void ErrorCallback(int, const char * err_str);
        void Init(int width, int height, const char *title);
        void DeInit();
        static Renderer& GetInstance();
        GLFWwindow* GetWindow(){return window;}
        void Start();
        void Finish();
        int GetHeight();
        int GetWidth();
        
        Renderer(const Renderer&) = delete;
        Renderer& operator=(const Renderer&) = delete;
    private:
        Renderer() = default;
        GLFWwindow* window;
};

#endif //RENDERER_H