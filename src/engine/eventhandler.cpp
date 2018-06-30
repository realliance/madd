#include "eventhandler.h"
#include "madd.h"
#include <GLFW/glfw3.h>
#include "keycodes.h"
struct keyCallback {
    keyCB callback;
    unsigned int keyFlags;
};

void GlfwKeyCallBack(GLFWwindow *window, int key, int scancode, int action, int mods){
    
}

EventHandler::EventHandler(Madd* context):context(context){

}

EventHandler::~EventHandler(){

}

void EventHandler::Update(){
    glfwPollEvents();
    if(glfwWindowShouldClose((GLFWwindow*)context->GetWindow()))
        context->Close();
}

void EventHandler::RegisterKeyCB(keyCB* keyCBfunc, unsigned int keyCode, unsigned keyFlags){

}