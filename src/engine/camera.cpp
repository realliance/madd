#include "camera.h"
#include "madd.h"
#include <glm/gtc/matrix_transform.hpp>
Camera::Camera(Madd* context){
    Init(context);
}

Camera::~Camera(){

}

void Camera::Init(Madd* _context){
    context = _context;
    cameraPosition = glm::vec3(0.0f,0.0f,3.0f);
    targetPosition = glm::vec3(0.0f,0.0f,0.0f);
    upVector = glm::vec3(0.0f,1.0f,0.0f);
    view = glm::mat4(1.0f);
    projection = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(45.0f), (float)context->GetWidth() / context->GetHeight(), 0.1f, 100.0f);
}

glm::mat4* Camera::GetView(){
    return &view;
}

glm::mat4* Camera::GetProjection(){
    return &projection;
}

void Camera::Update(){
    view = glm::lookAt(cameraPosition,targetPosition,upVector);
    projection = glm::perspective(glm::radians(45.0f), (float)context->GetWidth() / context->GetHeight(), 0.1f, 100.0f);
}

void Camera::MovePosition(glm::vec3 movementVector){
    cameraPosition += movementVector*context->GetDeltaTime();
    targetPosition += movementVector*context->GetDeltaTime();
}

void Camera::SetPosition(glm::vec3 pos){
    cameraPosition = pos;
    pos.z -= 3.0f;
    targetPosition = pos;
}