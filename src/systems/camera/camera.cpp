#include "camera.h"
#include "madd.h"
#include <glm/gtc/matrix_transform.hpp>

CameraComponent Camera::Construct(){
  CameraComponent c{};
  c.pos = glm::vec3(0.0f, 0.0f, 3.0f);
  c.front = glm::vec3(0.0f, 0.0f, -1.0f);
  c.up = glm::vec3(0.0f, 1.0f, 0.0f);
  c.view = glm::lookAt(c.pos, c.pos + c.front, c.up);
  c.projection = glm::mat4(1.0f);
  c.projection = glm::perspective(glm::radians(45.0f), (float)Madd::GetInstance().GetWidth() / Madd::GetInstance().GetHeight(), 0.1f, 100.0f);
  return c;
}


void Camera::Destruct(CameraComponent& c){

}

void Camera::UpdateProjection(CameraComponent& c){
  c.projection = glm::perspective(glm::radians(45.0f), (float)Madd::GetInstance().GetWidth() / Madd::GetInstance().GetHeight(), 0.1f, 100.0f);
}

void Camera::LookAt(CameraComponent& c, glm::vec3 pos){
  c.front = glm::normalize(pos);
  c.view = glm::lookAt(c.pos, c.pos + c.front, c.up);
}

void Camera::MovePosition(CameraComponent& c, glm::vec3 movementVector){
  c.pos += movementVector;
  c.view = glm::lookAt(c.pos, c.pos + c.front, c.up);
}

void Camera::SetPosition(CameraComponent& c, glm::vec3 pos){
  c.pos = pos;
}

void Camera::SetPitchAndYaw(CameraComponent& c, float pitch, float yaw){
    glm::vec3 front;
    front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
    front.y = sin(glm::radians(pitch));
    front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
    c.front = glm::normalize(front);
    c.view = glm::lookAt(c.pos, c.pos + c.front, c.up);
}
