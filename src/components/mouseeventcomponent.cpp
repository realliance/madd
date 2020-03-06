#include "mouseeventcomponent.h"
#include "madd.h"

ComponentType MouseEventComponent::cType = Madd::GetNewComponentType();
ComponentType MouseEventComponent::Type(){ return cType; }
