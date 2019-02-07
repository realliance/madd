#include "eventhandler.h"
#include "madd.h"
#include <GLFW/glfw3.h>

struct keyCallback {
    keyCB cb;
    int mods;
};
#include<iostream>
#include "errors.h"
//Please rewrite if you know a better way

void EventHandler::KeyCallBack(GLFWwindow *window, int key, int scancode, int action, int mods){
    for(auto const i : getInstance().keyboardCallbacks[key]) {
        if(i.mods == mods || i.mods == 0) {
            i.cb(key, action);
        }
    }
}

void EventHandler::CursorPosCallback(GLFWwindow *window, double xpos, double ypos){
    for(auto const i : getInstance().cursorCallbacks)
        i(xpos,ypos);
}

EventHandler::EventHandler() : context{ nullptr } {
    glfwSetKeyCallback(context->GetWindow(), KeyCallBack);
    glfwSetCursorPosCallback(context->GetWindow(), CursorPosCallback);
}

void EventHandler::Init(Madd* context) {
    if (context != nullptr) {
        throw EVENTHANDLER_ALREADY_SETUP;
    }
    this->context = context;
}

EventHandler & EventHandler::getInstance() {
    static EventHandler instance;
    return instance;
}

void EventHandler::Update(){
    glfwPollEvents();
    if(glfwWindowShouldClose(context->GetWindow()))
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

void EventHandler::RegisterCursorPosCB(cursorPosCB cursorPosfunc){
    cursorCallbacks.push_back(cursorPosfunc);
}

bool EventHandler::GetKeyDown(unsigned int key){
    if(glfwGetKey(context->GetWindow(), key) == KEY_PRESS)
        return true;
    return false;
}

glm::vec2 EventHandler::GetCursorPos(){
    double xpos,ypos;
    glfwGetCursorPos(context->GetWindow(), &xpos, &ypos);
    return glm::vec2(xpos,ypos);
}

void EventHandler::LockCursor(){
    glfwSetInputMode(context->GetWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void EventHandler::UnLockCursor(){
    glfwSetInputMode(context->GetWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);   
}