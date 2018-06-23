#ifndef RENDERER_H
#define RENDERER_H
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Renderer{
    public:
        Renderer(int width, int height, const char *title);
        ~Renderer();
        GLFWwindow* GetWindow(){return window;}
        void Start();
        void Finish();
    private:
        GLFWwindow *window = nullptr;
};

#endif //RENDERER_H