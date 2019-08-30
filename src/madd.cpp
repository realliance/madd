#include "madd.h"
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "renderer.h"
#include "camerasystem.h"
#include "event/keyboardeventsystem.h"
#include "event/mouseeventsystem.h"
#include "keycodes.h"

void Madd::Init(int width, int height, const char *title) {
    this->currID = 0;
    this->width = width;
    this->height = height;
    this->height = height;
    this->mainCamera = nullptr;
    Renderer::GetInstance().Init(width, height, title);

    reloadShaderEvent = KeyboardEventComponent{};
    reloadShaderEvent.callback = Madd::ProcessInput;
    exitEvent = reloadShaderEvent;
    exitEvent.code = KEY_ESCAPE;
    reloadShaderEvent.code = KEY_SPACE;

    MouseEventSystem::GetInstance().Init();
    KeyboardEventSystem::GetInstance().Init();
    KeyboardEventSystem::GetInstance().Register(&reloadShaderEvent);
    KeyboardEventSystem::GetInstance().Register(&exitEvent);
}

Madd::~Madd() {
    for(auto const& [name, sys] : systems){
        sys->Deinit();
    }
    Renderer::GetInstance().DeInit();
}

Madd& Madd::GetInstance() {
    static Madd instance;
    return instance;
}

void Madd::Register(System* s){
    if(systems.contains(s->Name())){
        return;
    }
    s->Init();
    systems[s->Name()] = s;
}

System* Madd::GetSystem(std::string s){
    if(systems.contains(s)){
        return systems[s];
    }
    return nullptr;
}

size_t Madd::GetNewComponentID(){
    return ++currID;
}

void Madd::Tick(){
    for(auto const& [name, sys] : systems){
        sys->Update();
    }
    UpdateDeltaTime();
}

void Madd::ReloadShader() {
    // for(GameObject* obj : objs)
    //     if(!obj->ReloadShaders())
    //         return;
}

void Madd::ProcessInput(Component* c, int key, int action){
    if (key == KEY_ESCAPE)
        GetInstance().Close();
    if (key == KEY_SPACE && action == KEY_PRESS)
        GetInstance().ReloadShader();
}

void Madd::UpdateDeltaTime(){
    dTime = Clock::now() - lastFrame;
    lastFrame = Clock::now();
}

CameraComponent* Madd::GetMainCamera(){
    return mainCamera;
}


void Madd::SetMainCamera(CameraComponent* cameraObj){mainCamera=cameraObj;}
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
