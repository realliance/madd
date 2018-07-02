#ifndef RENDERER_H
#define RENDERER_H
#include <glad/glad.h>

class Madd;
struct GLFWwindow;
class Renderer{
    public:
        Renderer(Madd* context, int width, int height, const char *title);
        ~Renderer();
        GLFWwindow* GetWindow(){return window;}
        void Start();
        void Finish();
        int GetHeight();
        int GetWidth();
        Madd* context;
    private:
        GLFWwindow *window;
};

#endif //RENDERER_H