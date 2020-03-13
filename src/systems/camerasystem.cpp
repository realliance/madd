#include "camerasystem.h"
#include "madd.h"
#include <glm/gtc/matrix_transform.hpp>

SystemType CameraSystem::sType = Madd::GetNewSystemType();

bool CameraSystem::Register(Component *component) {
  cameras.push_back(dynamic_cast<CameraComponent *>(component));
  dynamic_cast<CameraComponent *>(component)->update = true;
  return true;
}

bool CameraSystem::Unregister(Component *component) {
  for (auto i = begin(cameras); i != end(cameras); i++) {
    if ((*i)->cID == component->cID) {
      cameras.erase(i);
      return true;
    }
  }
  return false;
}

void CameraSystem::Update() {
  for (CameraComponent *c : cameras) {
    if(c->update){
      updateComponent(*c);
      c->update = false;
    }
  }
}

void CameraSystem::updateComponent(CameraComponent &c) {
  c.projection = glm::perspective(glm::radians(c.fov), c.aspectratio, c.near, c.far);
  c.front = glm::normalize(c.lookAt);
  c.view = glm::lookAt(c.pos, c.pos + c.front, c.up);
}

CameraComponent CameraSystem::Construct() {
  CameraComponent c{};
  c.pos = glm::vec3(0.0f, 0.0f, 3.0f);
  c.front = glm::vec3(0.0f, 0.0f, -1.0f);
  c.lookAt = c.front;
  c.up = glm::vec3(0.0f, 1.0f, 0.0f);
  c.fov = 45.f;
  c.view = glm::lookAt(c.pos, c.pos + c.front, c.up);
  c.projection = glm::mat4(1.0f);
  c.near = 0.1f;
  c.far = 100.f;
  return c;
}

void CameraSystem::UpdateProjection(CameraComponent &c, int width, int height) {
  c.projection = glm::perspective(glm::radians(c.fov),
                                    (float)width /
                                        height,
                                    0.1f, 100.0f);
}

glm::vec3 CameraSystem::PitchAndYawVector(CameraComponent &c, float pitch,
                                          float yaw) {
  glm::vec3 front;
  front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
  front.y = sin(glm::radians(pitch));
  front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
  return front;
}
