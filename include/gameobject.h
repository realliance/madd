#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include <vector>
#include <string>
#include "vertexarray.h"
#include "shaderprogram.h"

class GameObject{
    public:
        GameObject();
        ~GameObject();
        bool ReloadShader();
        bool RenderInit(std::vector<float> _vertices, std::vector<unsigned int> _indices, std::string vertexShader, std::string fragmentShader);
        bool Render();
    private:
        std::vector<float> vertices;
        std::vector<unsigned int> indices;
        int indicesSize;
        std::string vsPath;
        std::string fsPath;
        VertexArray* VAO;
        ShaderProgram* shader;
        bool rendered;

        int shaderTimeLocation;
};

#endif //GAMEOBJECT_H