#ifndef RENDEREDOBJECT_H
#define RENDEREDOBJECT_H

#include <vector>
#include <string.h>
#include <glm/glm.hpp>
#include "vertexarray.h"
#include "shaderprogram.h"
#include "gameobject.h"

class RenderedObject{
    public:
        RenderedObject(GameObject* parent);
        ~RenderedObject();
        bool RenderInit(std::vector<float> _vertices,
                        std::vector<unsigned int> _indices,
                        std::string vertexShader,
                        std::string fragmentShader,
                        bool rgbcolor);
        bool ReloadShader();
        bool Render();
        glm::mat4 GetTransformation();
        void SetTransformation(glm::mat4 newMatrix);
    private:
        std::vector<float> vertices;
        std::vector<unsigned int> indices;
        int indicesSize;
        
        std::string vsPath;
        std::string fsPath;
        VertexArray* VAO;
        ShaderProgram* shader;
        GameObject* parent;

        unsigned int shaderTimeLocation;
        unsigned int transformLoc;
        glm::mat4 trans;
};

#endif //RENDEREDOBJECT_H