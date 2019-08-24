#include "eventhandler.h"
#include "madd.h"
#include <GLFW/glfw3.h>
#include<iostream>
#include "errors.h"


void EventHandler::Init() {
}

EventHandler& EventHandler::GetInstance() {
    static EventHandler instance;
    return instance;
}

void EventHandler::Update(){
    glfwPollEvents();
    if(glfwWindowShouldClose(Madd::GetInstance().GetWindow()))
        Madd::GetInstance().Close();
}


bool EventHandler::GetKeyDown(unsigned int key){
    if(glfwGetKey(Madd::GetInstance().GetWindow(), key) == KEY_PRESS)
        return true;
    return false;
}

glm::vec2 EventHandler::GetCursorPos(){
    double xpos,ypos;
    glfwGetCursorPos(Madd::GetInstance().GetWindow(), &xpos, &ypos);
    return glm::vec2(xpos,ypos);
}

void EventHandler::LockCursor(){
    glfwSetInputMode(Madd::GetInstance().GetWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void EventHandler::UnLockCursor(){
    glfwSetInputMode(Madd::GetInstance().GetWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);   
}
