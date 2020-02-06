#include "camerasystem.h"
#include "madd.h"

void CameraSystem::Init() {}

CameraSystem::~CameraSystem(){
}

bool CameraSystem::Register(Component *component) {
  component->cID = Madd::GetInstance().GetNewComponentID();
  cameradata[component->cID] = CameraData(dynamic_cast<CameraComponent*>(component));
  dynamic_cast<CameraComponent *>(component)->update = true;
  return true;
}

bool CameraSystem::Unregister(Component *component) {
  if(cameradata.contains(component->cID)){
    cameradata.erase(component->cID);
    return true;
  }
  return false;
}

void CameraSystem::Update() {
  for (auto &[cid,camdata] : cameradata) {
    CameraComponent* c = camdata.cam;
    camdata.projection = glm::perspective(glm::radians(c->fov), c->aspectratio, c->near, c->far);
    camdata.front = glm::normalize(c->lookAt);
    camdata.view = glm::lookAt(c->pos, c->pos + camdata.front, camdata.up);
  }
}

glm::mat4* CameraSystem::View(CameraComponent* c){
  return &cameradata[c->cID].view;
}

glm::mat4* CameraSystem::Projection(CameraComponent* c){
  return &cameradata[c->cID].projection;
}
