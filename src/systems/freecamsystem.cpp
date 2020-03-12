#include <systems/freecamsystem.h>
#include <vector>
#include "madd.h"
#include <systems/glfwsystem.h>
#include <assets/keycodes.h>
#include <component.h>


bool FreeCamSystem::Register(Component* component){
  component->cID = Madd::GetInstance().GetNewComponentID();
  freecams.push_back(dynamic_cast<FreecamComponent*>(component));
  Madd::GetInstance().RegisterComponent(&dynamic_cast<FreecamComponent*>(component)->camera);
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
    c->camera.update = true;
  }
}

FreecamComponent FreeCamSystem::Construct(){
    FreecamComponent c = FreecamComponent{};
    c.camera = CameraSystem::Construct();
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

#include <iostream>
void FreeCamSystem::ToggleMouseLock(FreecamComponent& c, WindowComponent* window, int key, int action){
  GlfwSystem* glfwsys= Madd::GetInstance().GetSystem<GlfwSystem>();
  if(action == KEY_PRESS){
      c.lastCursor = glm::vec2{};
      if(c.mouseLocked)
          glfwsys->UnlockCursor(*window);
      else
          glfwsys->LockCursor(*window);
      c.mouseLocked = !c.mouseLocked;
  }
}
