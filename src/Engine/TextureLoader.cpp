#include "TextureLoader.h"

TTextureLoader::TTextureLoader()
{}

TTextureLoader::~TTextureLoader()
{}

GLuint TTextureLoader::GetTexture(string file_name)
{
    if(!m_tgatexture.LoadTGA(file_name))
        cout << "Failed to load texture: " << file_name << "\n";

    GLuint temp_texture_id;

    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
    glGenTextures(1, &temp_texture_id);
    glBindTexture(GL_TEXTURE_2D, temp_texture_id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_tgatexture.getWidth(), m_tgatexture.getHeight(), 0, GL_BGRA, GL_UNSIGNED_BYTE, m_tgatexture.getDataForOpenGL());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glBindTexture(GL_TEXTURE_2D, 0);

    return temp_texture_id;
}
