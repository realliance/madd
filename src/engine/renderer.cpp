#include "renderer.h"
#include "madd.h"
#include "camera.h"
#include <iostream>
#include <GLFW/glfw3.h>
//see renderer.cpp::GetHeight(),GetWidth() for more details
int globalWidth;
int globalHeight;

#include "errors.h"
//Please rewrite if you know a better way
Renderer* rendererPointer=NULL;
void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
    //This is a bad workaround probably should fix eventually.
    globalWidth = width;
    globalHeight = height;
    rendererPointer->context->GetMainCamera()->UpdateProjection();
}

void ErrorCallback(int, const char* err_str)
{
    std::cout << "GLFW Error: " << err_str << std::endl;
}

Renderer::Renderer(Madd* context, int width, int height, const char *title):context(context),window(nullptr){
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

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    //delete me I dare you
    globalHeight=height;globalWidth=width;
    rendererPointer = this;
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
    //I don't know why this doesn't work
    //int height;
    //glfwGetFramebufferSize(window, NULL, &height);
    //return height;
    return globalHeight;
}

int Renderer::GetWidth(){
    //I don't know why this doesn't work
    //int width;
    //glfwGetFramebufferSize(window, &width, NULL);
    //return width;
    return globalWidth;
}