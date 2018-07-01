#include "madd.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "gameobject.h"
#include "renderer.h"
#include "camera.h"
#include "eventhandler.h"
Madd::Madd(int width, int height, const char *title):close(false),
                                                     width(width),
                                                     height(height),
                                                     timeScale(1.0f),
                                                     lastFrame(Clock::now()) {
    render = new Renderer(width, height, title);
    mainCamera = new Camera(this);
    event = new EventHandler(this);
    std::vector<unsigned int> keys = {KEY_ESCAPE,KEY_SPACE};
    event->RegisterMultipleKeyCB(BIND(Madd::ProcessInput),keys);
}

Madd::~Madd() { 
    for(GameObject* obj : objs){
        delete obj;
    }
    delete render;
    delete event;
    delete mainCamera;
}

void Madd::AddObject(GameObject* obj){
    objs.push_back(obj);
}

void Madd::Tick(){
    event->Update();
    render->Start();
    mainCamera->Update();
    for(GameObject* obj : objs){
        obj->Update();
        obj->Render();
    }
    render->Finish();
    UpdateDeltaTime();
}

void Madd::ReloadShader() {
    for(GameObject* obj : objs)
        if(!obj->ReloadShaders())
            return;
}
#include <iostream>
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

Camera* Madd::GetMainCamera(){
    return mainCamera;
}
EventHandler* Madd::GetEventHandler(){
    return event;
}
int Madd::GetWidth(){
    return render->GetWidth();
}
int Madd::GetHeight(){
    return render->GetHeight();
}
void* Madd::GetWindow(){
    return render->GetWindow();
}
float Madd::GetTime(){
    return glfwGetTime();
}
double Madd::GetDeltaTime(){
    return dTime.count() * timeScale;
}