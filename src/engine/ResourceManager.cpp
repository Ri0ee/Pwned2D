#include "ResourceManager.h"

namespace resources
{
    TResourceManager::TResourceManager(string current_dir)
    {
        cout << "resource manager constructor called" << endl;
        m_current_dir = current_dir;

        LoadTextures();
        LoadSettings();
    }

    TResourceManager::~TResourceManager()
    {
        cout << "resource manager destructor called" << endl;
    }

    void TResourceManager::LoadTextures()
    {
        m_game_textures.push_back(m_texture_loader.GetTexture(m_current_dir + "Textures\\ship.tga"));
    }

    void TResourceManager::LoadSettings()
    {
        //TODO: Fill that space with something
    }
}
