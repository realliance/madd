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
EventHandler* eventPointer=NULL;

void EventHandler::KeyCallBack(GLFWwindow *window, int key, int scancode, int action, int mods){
    for(auto const i : keyboardCallbacks[key]) {
        if(i.mods == mods || i.mods == 0) {
            i.cb(key, action);
        }
    }
}

void GlfwKeyCallBack(GLFWwindow *window, int key, int scancode, int action, int mods){
    eventPointer->KeyCallBack(window, key, scancode, action, mods);
}

void EventHandler::CursorPosCallback(GLFWwindow *window, double xpos, double ypos){
    for(auto const i : cursorCallbacks)
        i(xpos,ypos);
}

void GlfwCursorPosCallback(GLFWwindow *window, double xpos, double ypos){
    eventPointer->CursorPosCallback(window, xpos, ypos);
}

EventHandler::EventHandler(Madd* context):context(context){
    if(eventPointer)
        throw EVENTHANDLER_ALREADY_EXISTS;
    eventPointer = this;
    glfwSetKeyCallback(context->GetWindow(),GlfwKeyCallBack);
    glfwSetCursorPosCallback(context->GetWindow(),GlfwCursorPosCallback);
}

EventHandler::~EventHandler(){
    eventPointer = NULL;
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

unsigned int EventHandler::GetKey(unsigned int key){
    return glfwGetKey(context->GetWindow(), key);
}

void EventHandler::GetCursorPos(double* xpos, double* ypos){
    glfwGetCursorPos(context->GetWindow(), xpos, ypos);
}

void EventHandler::LockCursor(){
    glfwSetInputMode(context->GetWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void EventHandler::UnLockCursor(){
    glfwSetInputMode(context->GetWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);   
}