#ifndef RENDEREDOBJECT_H
#define RENDEREDOBJECT_H

#include <vector>
#include <string>
#include <glm/glm.hpp>

class VertexArray;
class ShaderProgram;
class GameObject;
class Texture;
class RenderedObject{
    public:
        RenderedObject(GameObject* parent);
        ~RenderedObject();
        int RenderInit(std::vector<float> vertices, std::string vertexShader, std::string fragmentShader, std::string texture);
        void LoadShader();
        bool Render();
        void Rendered(bool rendered);
        glm::mat4 GetTransformation();
        void SetTransformation(glm::mat4 newMatrix);
        int AddTexture(std::string texture);
        void SetTexture(unsigned int id);
    private:        
        std::string vsPath;
        std::string fsPath;
        VertexArray* VAO;
        std::vector<Texture*> textures;
        Texture* textureObj;
        GameObject* parent;
        ShaderProgram* shader;

        unsigned int shaderTimeLocation;
        unsigned int modelLoc;
        unsigned int viewLoc;
        unsigned int projectionLoc;
        glm::mat4 model;

        bool shouldRender;
};

#endif //RENDEREDOBJECT_H