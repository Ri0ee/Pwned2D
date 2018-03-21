#pragma once

#include <iostream>
#include <string>

#define GLEW_STATIC
#include <GL/glew.h>

#include "ShaderLoader.h"

using std::string;

class TGlitchShader
{
    public:
        TGlitchShader();
        TGlitchShader(string directory, string file_name);
        virtual ~TGlitchShader();

        void Create(string directory, string file_name);
        void Activate(float coef, int width, int height);
        void Deactivate();

    private:
        GLuint m_shader_program;
        GLuint m_resolution_loc;
        GLuint m_coef_loc;
};
