#include "ShaderLoader.h"

Shader::Shader(){}
Shader::~Shader(){}

string Shader::ReadShader(string filename)
{
    string shaderCode;
    std::ifstream file(filename.c_str(), std::ios::in | std::ios::binary);

    if(!file.good())
    {
        cerr << "Can't read file '" << filename << "'\n";
        std::terminate();
    }

    file.seekg(0, std::ios::end);
    shaderCode.resize((unsigned int)file.tellg());
    file.seekg(0, std::ios::beg);

    file.read(&shaderCode[0], shaderCode.size());
    file.close();
    return shaderCode;
}

GLuint Shader::CreateShader(GLenum shaderType, string source, string shaderName)
{
    int compile_result = 0;

    GLuint shader = glCreateShader(shaderType);
    const char *shader_code_ptr = source.c_str();
    const int shader_code_size = source.size();

    glShaderSource(shader, 1, &shader_code_ptr, &shader_code_size);
    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compile_result);

    //check for errors
    if (compile_result == GL_FALSE)
    {
        int info_log_length = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &info_log_length);
        vector<char> shader_log(info_log_length);
        glGetShaderInfoLog(shader, info_log_length, NULL, &shader_log[0]);
        cout << "Failed to compile shader: '" << shaderName << "'\n" << &shader_log[0] << "\n";
        return 0;
    }
    return shader;
}

GLuint Shader::CreateProgram(string vertexShaderFilename, string fragmentShaderFilename)
{
    string vertex_shader_code = ReadShader(vertexShaderFilename);
    string fragment_shader_code = ReadShader(fragmentShaderFilename);
    GLuint vertex_shader = CreateShader(GL_VERTEX_SHADER, vertex_shader_code, "vertex shader");
    GLuint fragment_shader = CreateShader(GL_FRAGMENT_SHADER, fragment_shader_code, "fragment shader");

    int link_result = 0;
    GLuint program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);

    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &link_result);

    if (link_result == GL_FALSE)
    {
        int info_log_length = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &info_log_length);
        vector<char> program_log(info_log_length);
        glGetProgramInfoLog(program, info_log_length, NULL, &program_log[0]);
        cout << "Failed to link shader program \n" << &program_log[0] << "\n";
        return 0;
    }
    return program;
}
