#pragma once

#include <iostream>
#include <string>

#define GLEW_STATIC
#include <GL/glew.h>

#include "ShaderLoader.h"

using std::string;

class TBlurShader
{
    public:
        TBlurShader();
        TBlurShader(string directory, string file_name);
        virtual ~TBlurShader();

        void Create(string directory, string file_name);
        void Activate(float coef, float dir1, float dir2);
        void Deactivate();

    private:
        GLuint m_shader_program;
        GLuint m_direction_loc;
        GLuint m_coef_loc;
};
