#ifndef SHADER_SOURCES_H
#define SHADER_SOURCES_H

#include <string>

namespace shaders{

const std::string defaultVectorShader =
"#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"\n"
"void main()\n"
"{\n"
"    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\n";

const std::string defaultFragmentShader = 
"#version 330 core\n"
"out vec4 FragColor;\n"
"\n"
"void main()\n"
"{\n"
"    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n";

}

#endif //SHADER_SOURCES_H