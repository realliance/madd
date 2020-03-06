#include "texturecomponent.h"
#include "madd.h"

ComponentType TextureComponent::cType = Madd::GetNewComponentType();
ComponentType TextureComponent::Type(){ return cType; }
