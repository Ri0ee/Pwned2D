#include "GlitchShader.h"

TGlitchShader::TGlitchShader()
{}

TGlitchShader::TGlitchShader(string directory, string file_name)
{
    Create(directory, file_name);
}

TGlitchShader::~TGlitchShader()
{
    glDeleteProgram(m_shader_program);
}

void TGlitchShader::Create(string directory, string file_name)
{
    Shader ShaderLoader;
    m_shader_program = ShaderLoader.CreateProgram(directory + "Shaders\\" + file_name + ".vs",
                                                 directory + "Shaders\\" + file_name + ".fs");
    m_resolution_loc = glGetUniformLocation(m_shader_program, "resolution");
    m_coef_loc = glGetUniformLocation(m_shader_program, "coef");
}

void TGlitchShader::Activate(float coef, int width, int height)
{
    glUseProgram(m_shader_program);
    glUniform2i(m_resolution_loc, width, height);
    glUniform1f(m_coef_loc, coef);
}

void TGlitchShader::Deactivate()
{
    glUseProgram(0);
}
