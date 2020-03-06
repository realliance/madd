#include "shadercomponent.h"
#include "madd.h"

ComponentType ShaderComponent::cType = Madd::GetNewComponentType();
ComponentType ShaderComponent::Type(){ return cType; }
