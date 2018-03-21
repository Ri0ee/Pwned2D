#pragma once

#include <ft2build.h>
#include <freetype/freetype.h>
#include <freetype/ftglyph.h>
#include <freetype/ftoutln.h>
#include <freetype/fttrigon.h>
#include <freetype/ftstroke.h>

#define GLEW_STATIC
#include <GL/glew.h>

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using std::cout;
using std::string;
using std::min;
using std::max;
using std::vector;

namespace freetype
{
    struct ftchar
    {
        public:
            char symbol;
            GLuint texture;
            int width, height, font_size;
            float advance, bearingY;
    };

    struct textinf
    {
        public:
            int width, height;
            int font_size;
    };

    class TFreeType
    {
        public:
            TFreeType();
            virtual ~TFreeType();

            FT_Library ftlib;
            FT_Face ftface;

            bool use_kerning;
            vector<ftchar*> m_cached_chars;

            void Init(string directory, string font_name);
            int GetSymbol(const char &symbol, ftchar *ftchar_p, int font_size);
            int GetTextInfo(string text, int font_size, textinf *text_info);
    };
}
