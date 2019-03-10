#include "renderer.h"
#include "madd.h"
#include "camera.h"
#include <iostream>
#include <GLFW/glfw3.h>
#include "errors.h"

void Renderer::FramebufferSizeCallback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
    Madd::getInstance().GetMainCamera()->UpdateProjection();
}

void Renderer::ErrorCallback(int, const char* err_str) {
    std::cout << "GLFW Error: " << err_str << std::endl;
}

void Renderer::Init(int width, int height, const char * title) {
    glfwSetErrorCallback(ErrorCallback);
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(width, height, title, NULL, NULL);
    glfwMakeContextCurrent(window);

    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    glViewport(0, 0, width, height);

    glEnable(GL_DEPTH_TEST);

    glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);
}

Renderer& Renderer::getInstance() {

    static Renderer r;
    return r;
}

Renderer::~Renderer(){
    glfwTerminate();
}

void Renderer::Start(){
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::Finish(){
    glfwSwapBuffers(window);
}

int Renderer::GetHeight(){
    int height;
    glfwGetWindowSize(window, NULL, &height);
    return height;
}

int Renderer::GetWidth(){
    int width;
    glfwGetWindowSize(window, &width, NULL);
    return width;
}