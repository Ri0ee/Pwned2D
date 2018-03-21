#pragma once

#include "TGALoader.h"
#define GLEW_STATIC
#include <GL/glew.h>

#include <iostream>
#include <string>

using std::string;
using std::cout;

class TTextureLoader
{
    public:
        TTextureLoader();
        virtual ~TTextureLoader();

        GLuint GetTexture(string file_name);

        NS_TGALOADER::IMAGE m_tgatexture;
};
