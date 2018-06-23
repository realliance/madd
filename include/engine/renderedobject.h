#ifndef RENDEREDOBJECT_H
#define RENDEREDOBJECT_H

#include <vector>
#include <string.h>
#include <glm/glm.hpp>
#include "vertexarray.h"
#include "shaderprogram.h"
#include "gameobject.h"
#include "texture.h"

class RenderedObject{
    public:
        RenderedObject(GameObject* parent);
        ~RenderedObject();
        bool RenderInit(std::vector<float> vertices,
                        std::vector<unsigned int> indices,
                        std::string vertexShader,
                        std::string fragmentShader,
                        std::string texture);
        bool ReloadShader();
        bool Render();
        glm::mat4 GetTransformation();
        void SetTransformation(glm::mat4 newMatrix);
    private:        
        std::string vsPath;
        std::string fsPath;
        VertexArray* VAO;
        Texture* textureObj;
        ShaderProgram* shader;
        GameObject* parent;

        unsigned int shaderTimeLocation;
        unsigned int transformLoc;
        glm::mat4 trans;
};

#endif //RENDEREDOBJECT_H