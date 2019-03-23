#include "madd.h"
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "gameobject.h"
#include "renderer.h"
#include "camera.h"
#include "eventhandler.h"

void Madd::Init(int width, int height, const char *title) {
    this->width = width;
    this->height = height;
    this->height = height;
    Renderer::GetInstance().Init(width, height, title);
    std::vector<unsigned int> keys = {KEY_ESCAPE,KEY_SPACE};
    EventHandler::GetInstance().RegisterMultipleKeyCB(BIND(Madd::ProcessInput), keys);
}

Madd& Madd::GetInstance() {
    static Madd instance;
    return instance;
}

Madd::~Madd() {
    for(GameObject* obj : objs){
        delete obj;
    }
    Renderer::GetInstance().DeInit();
}

void Madd::AddObject(GameObject* obj){
    objs.push_back(obj);
}

void Madd::Tick(){
    EventHandler::GetInstance().Update();
    Renderer::GetInstance().Start();
    for(GameObject* obj : objs){
        obj->Update();
        obj->Render();
    }
    Renderer::GetInstance().Finish();
    UpdateDeltaTime();
}

void Madd::ReloadShader() {
    for(GameObject* obj : objs)
        if(!obj->ReloadShaders())
            return;
}

void Madd::ProcessInput(int key, int action){
    if (key == KEY_ESCAPE)
        Close();
    if (key == KEY_SPACE && action == KEY_PRESS)
        ReloadShader();
}

void Madd::UpdateDeltaTime(){
    dTime = Clock::now() - lastFrame;
    lastFrame = Clock::now();
}

Camera* Madd::GetMainCamera(){return mainCamera;}
EventHandler* Madd::GetEventHandler() {
    return &EventHandler::GetInstance();
}
void Madd::SetMainCamera(Camera* cameraObj){mainCamera=cameraObj;}
double Madd::GetTime(){return glfwGetTime();}
float Madd::GetDeltaTime(){return dTime.count() * timeScale;}

int Madd::GetWidth() {
    return Renderer::GetInstance().GetWidth();
}

int Madd::GetHeight() {
    return Renderer::GetInstance().GetHeight();
}

GLFWwindow* Madd::GetWindow() {
    return Renderer::GetInstance().GetWindow();
}
