#pragma once

#include <vector>
#include <string>
#include <iostream>

#include "Structures.h"
#include "Button.h"

using std::cout;
using std::cin;
using std::string;
using std::vector;

namespace gui
{
    class TGui
    {
        public:
            TGui();
            virtual ~TGui();

            void Init(freetype::TFreeType *ftlib, graphics::TRenderer *rndr, int window_width, int window_height);
            void Draw();
            void Reset();
            void Press();
            void CheckCollsions(vec2 point);

            TButton& GetButton(string button_name);
            void AddButton(TButton button);

            vector<TButton> m_vecUIButton;

            bool m_visible;
            freetype::TFreeType *m_ftlib;
            graphics::TRenderer *m_renderer;
            input::TInputManager *m_input_manager;

            int m_window_width;
            int m_window_height;
    };
}
