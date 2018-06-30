#include "camera.h"
#include "madd.h"
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
Camera::Camera(Madd* parent):view(glm::mat4(1.0f)),projection(glm::mat4(1.0f)),parent(parent),x(0.0f),y(0.0f),z(0.0f){
    view = glm::translate(view, glm::vec3(x, y, z));
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
    view = glm::translate(view, glm::vec3(x, y, z));
    projection = glm::perspective(glm::radians(45.0f), (float)parent->GetWidth() / parent->GetHeight(), 0.1f, 100.0f);
}

void Camera::MovePosition(float _x, float _y, float _z){
    std::cout<<_y;
    view = glm::translate(view, glm::vec3(_x, _y, _z));
}

void Camera::SetPosition(float _x, float _y, float _z){
    view = glm::mat4(1.0f);
    view = glm::translate(view, glm::vec3(_x, _y, _z));
}