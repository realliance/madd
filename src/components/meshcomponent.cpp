#include "meshcomponent.h"
#include "madd.h"

ComponentType MeshComponent::cType = Madd::GetNewComponentType();
ComponentType MeshComponent::Type(){ return cType; }
