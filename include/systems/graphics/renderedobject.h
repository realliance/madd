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
        void RenderInit(std::vector<float> vertices, std::string vertexShader, std::string fragmentShader);
        void LoadShader();
        bool Render();
        void Rendered(bool rendered);
        glm::mat4 GetTransformation();
        void SetTransformation(glm::mat4 newMatrix);
        void SetShade(glm::vec4 newShade);
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
        unsigned int shadeLoc;
        unsigned int viewLoc;
        unsigned int projectionLoc;
        unsigned int textureLoc;
        glm::mat4 model;
        glm::vec4 shade;

        bool shouldRender;
};

#endif //RENDEREDOBJECT_H
