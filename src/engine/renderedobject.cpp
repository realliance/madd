#include "renderedobject.h"
#include "madd.h"
#include "camera.h"

RenderedObject::RenderedObject(GameObject* parent):parent(parent),shader(nullptr){
}

RenderedObject::~RenderedObject(){
    delete VAO;
    delete shader;
    delete textureObj;
}

bool RenderedObject::RenderInit(std::vector<float> vertices,
                                std::vector<unsigned int> indices,
                                std::string vertexShader,
                                std::string fragmentShader,
                                std::string texture){
    vsPath = vertexShader;
    fsPath = fragmentShader;
    model = glm::mat4(1.0f);
    VAO = new VertexArray(vertices, indices);
    textureObj = new Texture(texture);

    if(!LoadShader())
        return false;
    shader->Enable();
    shader->AddInt("texture1",0);
    return true;
}

bool RenderedObject::LoadShader() {
    ShaderProgram* _shader;
    try {
        _shader = new ShaderProgram(vsPath, fsPath);
    } catch (int e) {
        return false;
    }
    if (shader) 
        delete shader;
    shader = _shader;
    
    //Update Locations for new shader
    shaderTimeLocation = shader->GetUniformLocation("time");
    modelLoc = shader->GetUniformLocation("model");
    viewLoc = shader->GetUniformLocation("view");
    projectionLoc = shader->GetUniformLocation("projection");
    ShaderProgram::SetMartix4fUniform(modelLoc, &model);
    return true;
}

bool RenderedObject::Render(){
    Camera* camera = parent->GetContext()->GetMainCamera();
    ShaderProgram::SetMartix4fUniform(viewLoc, camera->GetView());
    ShaderProgram::SetMartix4fUniform(projectionLoc, camera->GetProjection());
    ShaderProgram::SetFloatUniform(shaderTimeLocation, parent->GetContext()->GetTime());
    shader->Enable();
    Texture::SetActiveTexture(0);
    textureObj->Enable();

    VAO->Draw();
    return true;
}

glm::mat4 RenderedObject::GetTransformation(){
    return model;
}
void RenderedObject::SetTransformation(glm::mat4 newMatrix){
    model = newMatrix;
    ShaderProgram::SetMartix4fUniform(modelLoc, &model);
}