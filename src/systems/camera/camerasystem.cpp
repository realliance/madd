#include "camerasystem.h"
#include "madd.h"
#include <glm/gtc/matrix_transform.hpp>

void CameraSystem::Init() {}

void CameraSystem::Deinit() { delete this; }

bool CameraSystem::Register(Component *component) {
  component->cID = Madd::GetInstance().GetNewComponentID();
  cameras.push_back(dynamic_cast<CameraComponent *>(component));
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
    updateComponent(*c);
  }
}

void CameraSystem::updateComponent(CameraComponent &c) {
  if (c.fov != c._fov) {
    c._fov = c.fov;
    float ratio =
        (float)Madd::GetInstance().GetWidth() / Madd::GetInstance().GetHeight();
    c.projection = glm::perspective(glm::radians(c.fov), ratio, 0.1f, 100.0f);
  }

  bool dirty = false;
  if (c.pos != c._pos) {
    c._pos = c.pos;
    dirty = true;
  }
  if (c.lookAt != c._lookAt) {
    c._lookAt = c.lookAt;
    c.front = glm::normalize(c.lookAt);
    dirty = true;
  }
  if (dirty) {
    c.view = glm::lookAt(c.pos, c.pos + c.front, c.up);
  }
}

CameraComponent CameraSystem::Construct() {
  CameraComponent c{};
  c.pos = glm::vec3(0.0f, 0.0f, 3.0f);
  c.front = glm::vec3(0.0f, 0.0f, -1.0f);
  c.up = glm::vec3(0.0f, 1.0f, 0.0f);
  c.fov = 45.f;
  c.view = glm::lookAt(c.pos, c.pos + c.front, c.up);
  c.projection = glm::mat4(1.0f);
  c.projection = glm::perspective(glm::radians(45.0f),
                                  (float)Madd::GetInstance().GetWidth() /
                                      Madd::GetInstance().GetHeight(),
                                  0.1f, 100.0f);
  return c;
}

void CameraSystem::UpdateProjection(CameraComponent &c, int width, int height) {
  for (CameraComponent *c : cameras) {
    c->projection = glm::perspective(glm::radians(c->fov),
                                     (float)Madd::GetInstance().GetWidth() /
                                         Madd::GetInstance().GetHeight(),
                                     0.1f, 100.0f);
  }
}

glm::vec3 CameraSystem::PitchAndYawVector(CameraComponent &c, float pitch,
                                          float yaw) {
  glm::vec3 front;
  front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
  front.y = sin(glm::radians(pitch));
  front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
  return front;
}
