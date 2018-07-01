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
    projection = glm::mat4(1.0f);
    view = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(45.0f), (float)context->GetWidth() / context->GetHeight(), 0.1f, 100.0f);
}

glm::mat4* Camera::GetView(){
    return &view;
}

glm::mat4* Camera::GetProjection(){
    return &projection;
}

void Camera::Update(){
    view = glm::translate(view, position*context->GetDeltaTime());
    projection = glm::perspective(glm::radians(45.0f), (float)context->GetWidth() / context->GetHeight(), 0.1f, 100.0f);
}

void Camera::MovePosition(glm::vec3 movementVector){
    position = movementVector;
}

void Camera::SetPosition(glm::vec3 pos){
    view = glm::mat4(1.0f);
    view = glm::translate(view, pos);
}