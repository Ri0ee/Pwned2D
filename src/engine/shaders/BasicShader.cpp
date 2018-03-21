#include "BasicShader.h"

TBasicShader::TBasicShader()
{}

TBasicShader::TBasicShader(string directory, string file_name)
{
    Create(directory, file_name);
}

TBasicShader::~TBasicShader()
{
    glDeleteProgram(m_shader_program);
}

void TBasicShader::Create(string directory, string file_name)
{
    Shader ShaderLoader;
    m_shader_program = ShaderLoader.CreateProgram(directory + "Shaders\\" + file_name + ".vs",
                                                  directory + "Shaders\\" + file_name + ".fs");
}

void TBasicShader::Activate()
{
    glUseProgram(m_shader_program);
}

void TBasicShader::Deactivate()
{
    glUseProgram(0);
}
