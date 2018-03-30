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
#include <iterator>

using std::cout;
using std::endl;
using std::string;
using std::min;
using std::max;
using std::vector;

namespace freetype
{
	struct ftchar
	{
	public:
		void operator=(const ftchar &other_char)
		{
			advance = other_char.advance;
			bearingY = other_char.bearingY;
			font_size = other_char.font_size;
			height = other_char.height;
			symbol = other_char.symbol;
			texture = other_char.texture;
			width = other_char.width;
		}

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
            TFreeType(string current_dir, string font_name);
            virtual ~TFreeType();

            int GetSymbol(char symbol, ftchar *ftchar_p, int font_size);
            int GetTextInfo(string text, int font_size, textinf *text_info);
            bool m_status;

        private:
            FT_Library m_ftlib;
            FT_Face m_ftface;
            vector<ftchar> m_cached_chars;
	};
}
