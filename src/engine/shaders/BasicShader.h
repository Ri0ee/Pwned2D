#pragma once

#include <iostream>
#include <string>

#define GLEW_STATIC
#include <GL/glew.h>

#include "ShaderLoader.h"

using std::string;

class TBasicShader
{
    public:
        TBasicShader();
        TBasicShader(string directory, string file_name);
        virtual ~TBasicShader();

        void Create(string directory, string file_name);
        void Activate();
        void Deactivate();

    private:
        GLuint m_shader_program;
};
