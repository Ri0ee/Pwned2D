#pragma once

#include <string>
#include <vector>
#include <algorithm>

#include "Structures.h"
#include "PointCollision.h"
#include "Render.h"
#include "FreeType.h"

using std::cout;
using std::cin;
using std::string;
using std::vector;

class TButton
{
    public:
        TButton(vector<vec2> shape, vec2 position, int align, color background_color, color foreground_color, color highlight_color, string caption, freetype::TFreeType *ftlib);
        virtual ~TButton();

        void Draw();
        void FindBoudaries();
        void CheckCollision(vec2 point);
        void Press();
        void SetCallback(void (*callback_function)());

        freetype::TFreeType *m_ftlib;

        vector<vec2> m_shape;
        string m_caption;
        vec2 m_pos;

        color m_background;
        color m_foreground;
        color m_highlight_color;

        float m_width;
        float m_height;
        bool m_visible;
        bool m_collided;
        bool m_has_callback;
        int m_align;

        freetype::textinf m_font_info;

        void (*m_callback_function)();
};
