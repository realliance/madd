#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <errors.h>

class Shader {
public:
    Shader(std::string shaderSourceCode, unsigned int shaderType);
    Shader(std::string shaderFileName);
    ~Shader();
    int Link(unsigned int _program);
private:
    void Init();
    unsigned int id;
    const char *source;
    unsigned int shaderType;
    unsigned int program;
};

#endif // SHADER_H