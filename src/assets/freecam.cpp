#include "assets/freecam.h"
#include <vector>
#include "eventhandler.h"
#include "madd.h"

FreecamComponent FreeCam::Construct(){
    FreecamComponent c = FreecamComponent{};
    c.camera = Camera::Construct();
    c.firstCursor = true;
    c.mouseLocked = false;
    ToggleMouseLock(c);
    c.pitch = 0.0f;
    c.yaw = -90.0f;
    return c;
}

void FreeCam::Destruct(FreecamComponent& c){

}

void FreeCam::Update(FreecamComponent& c){
    ProcessInput(c);
}

void FreeCam::ProcessCursorPos(FreecamComponent& c, double xpos, double ypos){
    if(!c.mouseLocked){
        return;
    }
    if(c.firstCursor){
        c.lastCursor = glm::vec2(xpos,ypos);
        c.firstCursor = false;
    }
    glm::vec2 offset = c.lastCursor - glm::vec2(xpos,ypos);
    c.lastCursor = glm::vec2(xpos,ypos);
    offset *= c.lookSpeed;
    c.yaw -= offset.x;
    c.pitch += offset.y;
    if(c.pitch > 89.0f)
        c.pitch = 89.0f;
    if(c.pitch < -89.0f)
        c.pitch = - 89.0f;
    Camera::SetPitchAndYaw(c.camera,c.pitch,c.yaw);
}

void FreeCam::ProcessInput(FreecamComponent& c){
    EventHandler* e = Madd::GetInstance().GetEventHandler();
    float speed = c.movementSpeed;
    glm::vec3 tempVec = glm::vec3(0.0f);
    if(e->GetKeyDown(KEY_W))
        tempVec += c.camera.front * glm::vec3(1.f,0.f,1.f);
    if(e->GetKeyDown(KEY_S))
        tempVec -= c.camera.front * glm::vec3(1.f,0.f,1.f);
    if(e->GetKeyDown(KEY_A))
        tempVec -= glm::cross(c.camera.front, c.camera.up);
    if(e->GetKeyDown(KEY_D))
        tempVec += glm::cross(c.camera.front, c.camera.up);
    if(e->GetKeyDown(KEY_LEFT_SHIFT))
        tempVec += c.camera.up;
    if(e->GetKeyDown(KEY_LEFT_CONTROL))
        tempVec -= c.camera.up;
    if(tempVec != glm::vec3(0.0f)){
        tempVec = glm::normalize(tempVec) * speed;
        Camera::MovePosition(c.camera, tempVec*Madd::GetInstance().GetDeltaTime());
    }
}

void FreeCam::ToggleMouseLock(FreecamComponent& c, int key, int action){
    if(action == KEY_PRESS){
        c.firstCursor = true;
        if(c.mouseLocked)
            Madd::GetInstance().GetEventHandler()->UnLockCursor();
        else
            Madd::GetInstance().GetEventHandler()->LockCursor();
        c.mouseLocked = !c.mouseLocked;
    }
}
