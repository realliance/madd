#include "madd.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "gameobject.h"
#include "renderer.h"
#include "camera.h"
#include "eventhandler.h"

Madd::Madd(int width, int height, const char *title):close(false),width(width),height(height) {
    render = new Renderer(width, height, title);
    mainCamera = new Camera(this);
    event = new EventHandler(this);
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