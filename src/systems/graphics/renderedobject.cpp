#include "renderedobject.h"
#include "madd.h"
#include "camera.h"
#include "vertexarray.h"
#include "shaderprogram.h"
#include "gameobject.h"
#include "texture.h"

RenderedObject::RenderedObject(GameObject* parent):parent(parent),shader(nullptr),shouldRender(false),textureObj(nullptr){
}

RenderedObject::~RenderedObject(){
    delete VAO;
    delete shader;
    for(auto texture : textures)
        delete texture;
}

void RenderedObject::RenderInit(std::vector<float> vertices, std::string vertexShader, std::string fragmentShader){
    shouldRender = true;
    vsPath = vertexShader;
    fsPath = fragmentShader;
    model = glm::mat4(1.0f);
    VAO = new VertexArray(vertices);
    LoadShader();
}

void RenderedObject::LoadShader() {
    ShaderProgram* _shader;
    _shader = new ShaderProgram(vsPath, fsPath);
    if (shader) 
        delete shader;
    shader = _shader;
    
    shader->Enable();
    //Update Locations for new shader
    shaderTimeLocation = shader->GetUniformLocation("time");
    
    modelLoc = shader->GetUniformLocation("model");
    viewLoc = shader->GetUniformLocation("view");
    projectionLoc = shader->GetUniformLocation("projection");
    shadeLoc = shader->GetUniformLocation("shade");
    textureLoc = shader->GetUniformLocation("textureEnabled");
    shade = glm::vec4(1.f);
    ShaderProgram::SetFloat4fUniform(shadeLoc, &shade);
    ShaderProgram::SetMartix4fUniform(modelLoc, &model);
}

bool RenderedObject::Render(){
    if (shouldRender) {
        shader->Enable();
        Camera* camera = Madd::GetInstance().GetMainCamera();
        if (camera) {
            ShaderProgram::SetMartix4fUniform(viewLoc, camera->GetView());
            ShaderProgram::SetMartix4fUniform(projectionLoc, camera->GetProjection());
        }
        else
            return false;
        ShaderProgram::SetFloatUniform(shaderTimeLocation, Madd::GetInstance().GetTime());
        shader->Enable();
        if(textureObj != nullptr){
            shader->SetIntUniform(textureLoc,1);
            Texture::SetActiveTexture(0);
            textureObj->Enable();
        }else{
            shader->SetIntUniform(textureLoc,0);
        }

        VAO->Draw();
    }
    return true;
}

void RenderedObject::Rendered(bool rendered) {
    shouldRender = rendered;
}

glm::mat4 RenderedObject::GetTransformation(){
    return model;
}

void RenderedObject::SetTransformation(glm::mat4 newMatrix){
    shader->Enable();
    model = newMatrix;
    ShaderProgram::SetMartix4fUniform(modelLoc, &model);
}

void RenderedObject::SetShade(glm::vec4 newShade){
    shade = newShade;
    ShaderProgram::SetFloat4fUniform(shadeLoc, &shade);
}

int RenderedObject::AddTexture(std::string texture) {
    Texture* temp = new Texture(texture);
    textures.push_back(temp);
    textureObj = textures.back();
    return temp->GetID();
}

void RenderedObject::SetTexture(unsigned int id) {
    for (auto texture : textures)
        if (texture->GetID() == id)
            textureObj = texture;
}
