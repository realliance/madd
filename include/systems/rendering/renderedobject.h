#ifndef RENDEREDOBJECT_H
#define RENDEREDOBJECT_H

#include <vector>
#include <string>
#include <glm/glm.hpp>

#include "components/renderedcomponent.h"
#include "system.h"

class RenderedObject{
    public:
        RenderedObject() = delete;
        static RenderedComponent Construct(std::vector<float> vertices, std::string vertexShaderPath, std::string fragmentShaderPath);
        static void Destruct(RenderedComponent& r);
        static void ReloadShader(RenderedComponent& r);
        static bool Render(const RenderedComponent& r);
        static void Rendered(RenderedComponent& r, bool rendered);
        static glm::mat4 GetTransformation(const RenderedComponent& r);
        static void SetTransformation(RenderedComponent& r, glm::mat4 newMatrix);
        static void SetShade(RenderedComponent& r, glm::vec4 newShade);
        static int AddTexture(RenderedComponent& r, std::string texture);
        static void SetTexture(RenderedComponent& r, unsigned int id);
};

#endif //RENDEREDOBJECT_H
