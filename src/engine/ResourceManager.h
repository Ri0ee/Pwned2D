#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <TextureLoader.h>

using std::string;
using std::vector;
using std::cout;
using std::endl;

namespace resources
{
    class TResourceManager
    {
        public:
            TResourceManager(string current_dir);
            virtual ~TResourceManager();

            void LoadTextures();
            void LoadSettings();

            string m_current_dir;
            TTextureLoader m_texture_loader;
            vector<GLuint> m_game_textures;
    };
}
