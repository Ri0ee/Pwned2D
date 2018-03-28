#pragma once

#include <string>
#include <iostream>

#include "Game.h"
#include "Render.h"
#include "Gui.h"
#include "FreeType.h"
#include "ResourceManager.h"
#include "InputManager.h"
#include "WindowManager.h"

#include "ETime.h"

using std::string;
using std::cout;
using std::endl;

class TInstance
{
    public:
        TInstance();
        virtual ~TInstance();

        string m_current_dir;
        bool m_should_finish;

        game::TGame*                 Game_Instance;
        window::TWindowManager*      Window_Instance;
        graphics::TRenderer*         Renderer_Instance;
        gui::TGui*                   GUI_Instance;
        freetype::TFreeType*         FT_Instance;
        resources::TResourceManager* RM_Instance;
};
