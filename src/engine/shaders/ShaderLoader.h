#pragma once

#define GLEW_STATIC
#include <GL/glew.h>

#include <iostream>
#include <fstream>
#include <vector>

using std::string;
using std::cerr;
using std::cout;
using std::vector;

class Shader
{
    public:
        Shader();
        virtual ~Shader();

        GLuint CreateProgram(string vertexShaderFilename, string fragmentShaderFilename);
    private:
        string ReadShader(string filename);
        GLuint CreateShader(GLenum shaderType, string source, string shaderName);
};
