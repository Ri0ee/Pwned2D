#pragma once

#define DRAWMODE_FILLED

#define GLEW_STATIC
#include <GL/glew.h>

#include <string>
#include <vector>
#include <iostream>

#include "Structures.h"
#include "FreeType.h"

using std::cout;
using std::cin;
using std::string;
using std::vector;

namespace graphics
{
    void Clear(void);
    void DrawRectangleT(float X0, float Y0, float width, float height, GLuint texture, bool use_blend);
    void DrawRectangleT(vec2 position     , float width, float height, GLuint texture, bool use_blend);
    void DrawTexture(vector<vec2> shape, vec2 position, GLuint texture, bool use_blending);

    void DrawPolygon(vector<vec2> shape, color shape_color, float X0, float Y0, bool use_blend);
    void DrawPolygon(vector<vec2> shape, color shape_color, vec2 position     , bool use_blend);

    void ftDrawText(string text, color text_color, vec2 position, int text_size, freetype::TFreeType &ftlib);
}
