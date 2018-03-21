#include "BlurShader.h"

TBlurShader::TBlurShader()
{}

TBlurShader::TBlurShader(string directory, string file_name)
{
    Create(directory, file_name);
}

TBlurShader::~TBlurShader()
{
    glDeleteProgram(m_shader_program);
}

void TBlurShader::Create(string directory, string file_name)
{
    Shader ShaderLoader;
    m_shader_program = ShaderLoader.CreateProgram(directory + "Shaders\\" + file_name + ".vs",
                                                  directory + "Shaders\\" + file_name + ".fs");
    m_direction_loc = glGetUniformLocation(m_shader_program, "direction");
    m_coef_loc = glGetUniformLocation(m_shader_program, "coef");
}

void TBlurShader::Activate(float coef, float dir1, float dir2)
{
    glUseProgram(m_shader_program);
    glUniform2f(m_direction_loc, dir1, dir2);
    glUniform1f(m_coef_loc, coef);
}

void TBlurShader::Deactivate()
{
    glUseProgram(0);
}
