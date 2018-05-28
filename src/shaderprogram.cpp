#include "shaderprogram.h"
#include <iostream>

ShaderProgram::ShaderProgram(std::string vsPath, std::string fsPath){
  Shader *vs;
  Shader *fs;
  try {
    vs = new Shader(vsPath);
    fs = new Shader(fsPath);
  } catch (int e) {
    throw COMPILATION_FAILED;
  }

  id = glCreateProgram();
  glAttachShader(id, vs->Link(id));
  glAttachShader(id, fs->Link(id));
  glLinkProgram(id);

  int success;
  char infoLog[512];
  glGetProgramiv(id, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(id, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::LINKING_FAILED\n" << infoLog << std::endl;
    throw LINKING_FAILED; 
  }

  delete vs;
  delete fs;
}

ShaderProgram::~ShaderProgram(){
    glDeleteProgram(id);
}