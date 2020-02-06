#include <assets/freecamsystem.h>
#include <vector>
#include "madd.h"
#include <glfwsystem.h>
#include <keycodes.h>
#include <components/component.h>

void FreeCamSystem::Init(){
}

FreeCamSystem::~FreeCamSystem(){
}

bool FreeCamSystem::Register(Component* component){
  component->cID = Madd::GetInstance().GetNewComponentID();
  freecamdata[component->cID] = FreeCamData(dynamic_cast<FreecamComponent*>(component));
  Madd::GetInstance().GetSystem("CameraSystem")->Register(&freecamdata[component->cID].camera);
  return true;
}

bool FreeCamSystem::Unregister(Component* component){
  if(freecamdata.contains(component->cID)){
    freecamdata.erase(component->cID);
    return true;
  }
  return false;
}

void FreeCamSystem::Update(){
  for(auto & [cid, fcdata] : freecamdata){
    processCursor(fcdata);
    processMove(fcdata);
  }
}

void FreeCamSystem::processCursor(FreeCamData& c){
    if(!c.freecam->mouseLocked){
        return;
    }
    if(c.lastCursor == glm::vec2{}){
        c.lastCursor = c.cursor;
    }
    glm::vec2 offset = c.lastCursor - c.cursor;
    c.lastCursor = c.cursor;
    offset *= c.freecam->lookSpeed;
    c.yaw -= offset.x;
    c.pitch += offset.y;
    if(c.pitch > 89.0f)
        c.pitch = 89.0f;
    if(c.pitch < -89.0f)
        c.pitch = - 89.0f;
    c.camera.lookAt = pitchAndYawVector(c.pitch,c.yaw);
}

void FreeCamSystem::processMove(FreeCamData& c){
  if(c.movVector == glm::vec3(0)){
    return;
  }
  glm::vec3 tempVec{};
  glm::vec3 front = glm::normalize(c.camera.lookAt);
  glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
  if(c.movVector.z > 0)
      tempVec += front * glm::vec3(1.f,0.f,1.f);
  if(c.movVector.z < 0)
      tempVec -= front * glm::vec3(1.f,0.f,1.f);
  if(c.movVector.x < 0)
      tempVec -= glm::cross(front, up);
  if(c.movVector.x > 0)
      tempVec += glm::cross(front, up);
  if(c.movVector.y > 0)
      tempVec += up;
  if(c.movVector.y < 0)
      tempVec -= up;
  tempVec = glm::normalize(tempVec) * c.freecam->movementSpeed;
  c.camera.pos += tempVec*Madd::GetInstance().GetDeltaTime();
}

// void FreeCamSystem::ToggleMouseLock(FreecamComponent& c, WindowComponent* window, int key, int action){
//   GlfwSystem* glfwsys= dynamic_cast<GlfwSystem*>(Madd::GetInstance().GetSystem("GlfwSystem"));
//   if(action == KEY_PRESS){
//       c.lastCursor = glm::vec2{};
//       if(c.mouseLocked)
//           glfwsys->UnlockCursor(*window);
//       else
//           glfwsys->LockCursor(*window);
//       c.mouseLocked = !c.mouseLocked;
//   }
// }

glm::vec3 FreeCamSystem::pitchAndYawVector(float pitch, float yaw) {
  glm::vec3 front;
  front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
  front.y = sin(glm::radians(pitch));
  front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
  return front;
}

CameraComponent* FreeCamSystem::Camera(FreecamComponent* freecam){
  return &freecamdata[freecam->cID].camera;
}