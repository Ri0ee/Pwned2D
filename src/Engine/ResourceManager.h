#pragma once

#include <string>
#include <vector>
#include <TextureLoader.h>
#include <iostream>

using std::string;
using std::vector;

namespace resources
{
    class TResourceManager
    {
        public:
            TResourceManager();
            virtual ~TResourceManager();

            void Init(string path);
            void LoadTextures();
            void LoadSettings();

            string m_path;
            TTextureLoader m_texture_loader;
            vector<GLuint> m_game_textures;
    };
}
