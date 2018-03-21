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

            void Draw();
            void Reset();
            void CheckCollsions(vec2 point);
            void AddButton(TButton button);
            void Press();

            vector<TButton> m_vecUIButton;

            bool m_visible;
    };
}
