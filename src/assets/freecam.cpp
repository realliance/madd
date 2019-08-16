#include "assets/freecam.h"
#include <vector>
#include "eventhandler.h"
#include "madd.h"

FreeCam::FreeCam(){
    firstCursor = true;
    mouseLocked = false;
    ToggleMouseLock();
    EventHandler::GetInstance().RegisterKeyCB(BIND(FreeCam::ToggleMouseLock), KEY_TAB);
    EventHandler::GetInstance().RegisterCursorPosCB(BIND(FreeCam::ProcessCursorPos));
    pitch = 0.0f;
    yaw = -90.0f;
}

FreeCam::~FreeCam(){

}

void FreeCam::Update(){
    ProcessInput();
}

void FreeCam::ProcessCursorPos(double xpos, double ypos){
    if(firstCursor){
        lastCursor = glm::vec2(xpos,ypos);
        firstCursor = false;
    }
    glm::vec2 offset = lastCursor - glm::vec2(xpos,ypos);
    lastCursor = glm::vec2(xpos,ypos);
    offset *= lookSpeed;
    yaw -= offset.x;
    pitch += offset.y;
    if(pitch > 89.0f)
        pitch = 89.0f;
    if(pitch < -89.0f)
        pitch = - 89.0f;
    SetPitchAndYaw(pitch,yaw);
}

void FreeCam::ProcessInput(){
    EventHandler* e = Madd::GetInstance().GetEventHandler();
    float speed = movementSpeed;
    glm::vec3 tempVec = glm::vec3(0.0f);
    if(e->GetKeyDown(KEY_W))
        tempVec += cameraFront;
    if(e->GetKeyDown(KEY_S))
        tempVec -= cameraFront;
    if(e->GetKeyDown(KEY_A))
        tempVec -= glm::cross(cameraFront, cameraUp);
    if(e->GetKeyDown(KEY_D))
        tempVec += glm::cross(cameraFront, cameraUp);
    if(e->GetKeyDown(KEY_LEFT_SHIFT))
        tempVec += cameraUp;
    if(e->GetKeyDown(KEY_LEFT_CONTROL))
        tempVec -= cameraUp;
    if(tempVec != glm::vec3(0.0f)){
        tempVec = glm::normalize(tempVec) * speed;
        Camera::MovePosition(tempVec*Madd::GetInstance().GetDeltaTime());
    }
}

void FreeCam::ToggleMouseLock(int key, int action){
    if(action == KEY_PRESS){
        firstCursor = true;
        if(mouseLocked)
            Madd::GetInstance().GetEventHandler()->UnLockCursor();
        else
            Madd::GetInstance().GetEventHandler()->LockCursor();
        mouseLocked = !mouseLocked;
    }
}
