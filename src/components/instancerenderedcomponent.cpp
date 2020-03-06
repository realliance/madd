#include "instancerenderedcomponent.h"
#include "madd.h"

ComponentType InstanceRenderedComponent::cType = Madd::GetNewComponentType();
ComponentType InstanceRenderedComponent::Type(){ return cType; }
