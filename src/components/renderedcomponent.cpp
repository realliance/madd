#include "renderedcomponent.h"
#include "madd.h"

ComponentType RenderedComponent::cType = Madd::GetNewComponentType();
ComponentType RenderedComponent::Type(){ return cType; }
