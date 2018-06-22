#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include <vector>
#include <string>
#include <glm/glm.hpp>
#include "vertexarray.h"
#include "shaderprogram.h"

class Madd;
class GameObject{
    public:
        GameObject(Madd* context);
        ~GameObject();
        bool ReloadShader();
        bool RenderInit(std::vector<float> _vertices, std::vector<unsigned int> _indices, std::string vertexShader, std::string fragmentShader);
        bool Render();
        bool Update();
        
    private:
        std::vector<float> vertices;
        std::vector<unsigned int> indices;
        int indicesSize;
        
        std::string vsPath;
        std::string fsPath;
        VertexArray* VAO;
        ShaderProgram* shader;
        bool rendered;
        Madd* context;

        unsigned int shaderTimeLocation;
        unsigned int transformLoc;
        glm::mat4 trans;
};

#endif //GAMEOBJECT_H