#include "camera.h"
#include "madd.h"
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
Camera::Camera(Madd* parent):view(glm::mat4(1.0f)),projection(glm::mat4(1.0f)),parent(parent){
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
    projection = glm::perspective(glm::radians(45.0f), (float)parent->GetWidth() / parent->GetHeight(), 0.1f, 100.0f);
}

Camera::~Camera(){

}

glm::mat4* Camera::GetView(){
    return &view;
}

glm::mat4* Camera::GetProjection(){
    return &projection;
}

void Camera::Update(){
    projection = glm::perspective(glm::radians(45.0f), (float)parent->GetWidth() / parent->GetHeight(), 0.1f, 100.0f);
}