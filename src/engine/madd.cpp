#include "madd.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "keycodes.h"
#include "gameobject.h"
#include "renderer.h"
#include "camera.h"
#include "eventhandler.h"

Madd::Madd(int width, int height, const char *title):close(false),width(width),height(height) {
    render = new Renderer(width, height, title);
    mainCamera = new Camera(this);
    event = new EventHandler(this);
    std::vector<unsigned int> keys = {KEY_ESCAPE,KEY_SPACE};
    keyCB callback = std::bind(&ProcessInput, this, std::placeholders::_1, std::placeholders::_2);
    event->RegisterMultipleKeyCB(callback,keys);
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

Camera* Madd::GetMainCamera(){
    return mainCamera;
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