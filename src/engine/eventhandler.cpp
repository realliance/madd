#include "eventhandler.h"
#include "madd.h"
#include <GLFW/glfw3.h>

struct keyCallback {
    keyCB cb;
    int mods;
};
#define EVENTHANDLER_ALREADY_EXISTS 70;
//Please rewrite if you know a better way
EventHandler* eventPointer=NULL;
void EventHandler::KeyCallBack(GLFWwindow *window, int key, int scancode, int action, int mods){
    for(auto const i : keyboardCallbacks[key]) {
        if(i.mods == mods) {
            i.cb(key, action);
        }
    }
}

void GlfwKeyCallBack(GLFWwindow *window, int key, int scancode, int action, int mods){
    eventPointer->KeyCallBack(window, key, scancode, action, mods);
}


EventHandler::EventHandler(Madd* context):context(context){
    if(eventPointer)
        throw EVENTHANDLER_ALREADY_EXISTS;
    eventPointer = this;
    glfwSetKeyCallback((GLFWwindow*)context->GetWindow(),GlfwKeyCallBack);
}

EventHandler::~EventHandler(){
    eventPointer = NULL;
}

void EventHandler::Update(){
    glfwPollEvents();
    if(glfwWindowShouldClose((GLFWwindow*)context->GetWindow()))
        context->Close();
}

void EventHandler::RegisterMultipleKeyCB(keyCB keyCBfunc, std::vector<unsigned int> keyCode, unsigned int keyMods){
    for(unsigned int i : keyCode)
        RegisterKeyCB(keyCBfunc, i, keyMods);
}

void EventHandler::RegisterKeyCB(keyCB keyCBfunc, unsigned int keyCode, unsigned int keyMods){
    keyCallback callback;
    callback.cb = keyCBfunc;
    callback.mods = keyMods;
    keyboardCallbacks[keyCode].push_back(callback);
}

unsigned int EventHandler::GetKey(unsigned int key){
    return glfwGetKey((GLFWwindow*)context->GetWindow(), key);
}

void EventHandler::GetMousePos(double* xpos, double* ypos){
    glfwGetCursorPos((GLFWwindow*)context->GetWindow(), xpos, ypos);
}