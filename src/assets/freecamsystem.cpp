#include <assets/freecamsystem.h>
#include <vector>
#include "madd.h"
#include <mouseeventsystem.h>
#include <keycodes.h>
#include <components/component.h>


void FreeCamSystem::Init(){
}

void FreeCamSystem::Deinit(){
  delete this;
  freecams.clear();
}

bool FreeCamSystem::Register(Component* component){
  component->cID = Madd::GetInstance().GetNewComponentID();
  freecams.push_back(dynamic_cast<FreecamComponent*>(component));
  Madd::GetInstance().GetSystem("CameraSystem")->Register(&dynamic_cast<FreecamComponent*>(component)->camera);
  return true;
}

bool FreeCamSystem::Unregister(Component* component){
  for(auto i = begin(freecams); i != end(freecams); i++){
    if((*i)->cID == component->cID){
      freecams.erase(i);
      return true;
    }
  }
  return false;
}

void FreeCamSystem::Update(){
  for(auto const c : freecams){
    ProcessCursor(*c);
    ProcessMove(*c);
  }
}

FreecamComponent FreeCamSystem::Construct(){
    FreecamComponent c = FreecamComponent{};
    c.camera = CameraSystem::Construct();
    ToggleMouseLock(c);
    return c;
}

void FreeCamSystem::ProcessCursor(FreecamComponent& c){
    if(!c.mouseLocked){
        return;
    }
    if(c.lastCursor == glm::vec2{}){
        c.lastCursor = c.cursor;
    }
    glm::vec2 offset = c.lastCursor - c.cursor;
    c.lastCursor = c.cursor;
    offset *= c.lookSpeed;
    c.yaw -= offset.x;
    c.pitch += offset.y;
    if(c.pitch > 89.0f)
        c.pitch = 89.0f;
    if(c.pitch < -89.0f)
        c.pitch = - 89.0f;
    c.camera.lookAt = CameraSystem::PitchAndYawVector(c.camera,c.pitch,c.yaw);
    
}

void FreeCamSystem::ProcessMove(FreecamComponent& c){
  if(c.movVector == glm::vec3(0)){
    return;
  }
  glm::vec3 tempVec{};

  if(c.movVector.z > 0)
      tempVec += c.camera.front * glm::vec3(1.f,0.f,1.f);
  if(c.movVector.z < 0)
      tempVec -= c.camera.front * glm::vec3(1.f,0.f,1.f);
  if(c.movVector.x < 0)
      tempVec -= glm::cross(c.camera.front, c.camera.up);
  if(c.movVector.x > 0)
      tempVec += glm::cross(c.camera.front, c.camera.up);
  if(c.movVector.y > 0)
      tempVec += c.camera.up;
  if(c.movVector.y < 0)
      tempVec -= c.camera.up;

  tempVec = glm::normalize(tempVec) * c.movementSpeed;
  c.camera.pos += tempVec*Madd::GetInstance().GetDeltaTime();
}

void FreeCamSystem::ToggleMouseLock(FreecamComponent& c, int key, int action){
    if(action == KEY_PRESS){
        c.lastCursor = glm::vec2{};
        if(c.mouseLocked)
            MouseEventSystem::GetInstance().UnlockCursor();
        else
            MouseEventSystem::GetInstance().LockCursor();
        c.mouseLocked = !c.mouseLocked;
    }
}
