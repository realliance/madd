#include "renderedobject.h"
#include "madd.h"
#include "camera.h"
#include "vertexarray.h"
#include "shaderprogram.h"
#include "gameobject.h"
#include "texture.h"
#include "texturecomponent.h"


void RenderedObject::Deconstruct(RenderedComponent& r){
    VertexArray::Deconstruct(r.VAO);
    ShaderProgram::Deconstruct(r.shader);
    for(auto texture : r.textures)
        Texture::Deconstruct(texture);
    r = RenderedComponent{};
}

RenderedComponent RenderedObject::Construct(std::vector<float> vertices, std::string vertexShaderPath, std::string fragmentShaderPath){
    RenderedComponent r{};
    r.shouldRender = true;
    r.vsPath = vertexShaderPath;
    r.fsPath = fragmentShaderPath;
    r.model = glm::mat4(1.0f);
    r.VAO = VertexArray::Construct(vertices);
    
    ReloadShader(r);
    
    return r;
}

void RenderedObject::ReloadShader(RenderedComponent &r){
    ShaderComponent _shader{};
    _shader = ShaderProgram::Construct(r.vsPath, r.fsPath);
    if (r.shader.id != 0) 
        ShaderProgram::Deconstruct(r.shader);
    r.shader = _shader;
    
    ShaderProgram::Enable(r.shader);
    //Update Locations for new shader
    r.shaderTimeLocation = ShaderProgram::GetUniformLocation(r.shader, "time");
    
    r.modelLoc = ShaderProgram::GetUniformLocation(r.shader, "model");
    r.viewLoc = ShaderProgram::GetUniformLocation(r.shader, "view");
    r.projectionLoc = ShaderProgram::GetUniformLocation(r.shader, "projection");
    r.shadeLoc = ShaderProgram::GetUniformLocation(r.shader, "shade");
    r.textureLoc = ShaderProgram::GetUniformLocation(r.shader, "textureEnabled");
    r.shade = glm::vec4(1.f);
    ShaderProgram::SetFloat4fUniform(r.shadeLoc, &r.shade);
    ShaderProgram::SetMartix4fUniform(r.modelLoc, &r.model);
}

bool RenderedObject::Render(const RenderedComponent& r){
    if (r.shouldRender) {
        ShaderProgram::Enable(r.shader);
        Camera* camera = Madd::GetInstance().GetMainCamera();
        if (camera) {
            ShaderProgram::SetMartix4fUniform(r.viewLoc, camera->GetView());
            ShaderProgram::SetMartix4fUniform(r.projectionLoc, camera->GetProjection());
        }
        else
            return false;
        ShaderProgram::SetFloatUniform(r.shaderTimeLocation, Madd::GetInstance().GetTime());
        ShaderProgram::Enable(r.shader);
        if(r.textureN < r.textures.size()){
            ShaderProgram::SetIntUniform(r.textureLoc,1);
            Texture::SetActiveTexture(0);
            Texture::Enable(r.textures[r.textureN]);
        }else{
            ShaderProgram::SetIntUniform(r.textureLoc,0);
        }

        VertexArray::Draw(r.VAO);
    }
    return true;
}

void RenderedObject::Rendered(RenderedComponent& r, bool rendered) {
    r.shouldRender = rendered;
}

glm::mat4 RenderedObject::GetTransformation(const RenderedComponent& r){
    return r.model;
}

void RenderedObject::SetTransformation(RenderedComponent& r, glm::mat4 newMatrix){
    ShaderProgram::Enable(r.shader);
    r.model = newMatrix;
    ShaderProgram::SetMartix4fUniform(r.modelLoc, &r.model);
}

void RenderedObject::SetShade(RenderedComponent& r, glm::vec4 newShade){
    r.shade = newShade;
    ShaderProgram::SetFloat4fUniform(r.shadeLoc, &r.shade);
}

int RenderedObject::AddTexture(RenderedComponent& r, std::string texture) {
    r.textures.push_back(Texture::Construct(texture));
    r.textureN = r.textures.size()-1;
    return r.textures[r.textureN].id;
}

void RenderedObject::SetTexture(RenderedComponent& r, uint id) {
    for(int i = 0; i < r.textures.size(); i++){
        if(r.textures[i].id == id){
            r.textureN = i;
        }
    }
}
