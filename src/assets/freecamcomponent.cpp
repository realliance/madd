#include "assets/freecamcomponent.h"
#include "madd.h"

ComponentType FreecamComponent::cType = Madd::GetNewComponentType();
ComponentType FreecamComponent::Type(){ return cType; }
