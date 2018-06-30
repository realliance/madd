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
        bool LoadShader();
        bool Render();
        glm::mat4 GetTransformation();
        void SetTransformation(glm::mat4 newMatrix);
    private:        
        std::string vsPath;
        std::string fsPath;
        VertexArray* VAO;
        Texture* textureObj;
        GameObject* parent;
        ShaderProgram* shader;

        unsigned int shaderTimeLocation;
        unsigned int modelLoc;
        unsigned int viewLoc;
        unsigned int projectionLoc;
        glm::mat4 model;
};

#endif //RENDEREDOBJECT_H