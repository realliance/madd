#include "madd.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

Madd::Madd(int width, int height, const char *title):close(false) {
    render = new Renderer(width, height, title);
}

Madd::~Madd() { 
    for(GameObject* obj : objs){
        delete obj;
    }
}

void Madd::addObject(GameObject* obj){
    objs.push_back(obj);
}

void Madd::Tick(){
    ProcessInput();
    render->Start();

    for(GameObject* obj : objs){
        obj->Update();
        obj->Render();
    }

    render->Finish();
    glfwPollEvents();
}

void Madd::ProcessInput() {
    if(glfwWindowShouldClose(render->GetWindow()))
        close = true;
    if (glfwGetKey(render->GetWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
        close = true;
    if (glfwGetKey(render->GetWindow(), GLFW_KEY_SPACE) == GLFW_PRESS)
        ReloadShader();
}

bool Madd::ReloadShader() {
    for(GameObject* obj : objs){
          if(!obj->ReloadShaders()){
            return false;
          }
    }
    return true;
}
