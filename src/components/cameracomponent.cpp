#include "cameracomponent.h"
#include "madd.h"

ComponentType CameraComponent::cType = Madd::GetNewComponentType();
ComponentType CameraComponent::Type(){ return cType; }
