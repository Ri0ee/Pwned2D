#include "FreeType.h"

namespace freetype
{
	TFreeType::TFreeType(string current_dir, string font_name)
	{
		int errorCode = 0;
		m_status = true;
		string fpos = current_dir + font_name;

		errorCode = FT_Init_FreeType(&m_ftlib); ///Init freetype library
		if(errorCode != 0)
        {
            cout << "failed to init freetype library. error code = " << errorCode << endl;
            m_status = false;
        }

        if(!m_status)
        {
            errorCode = FT_New_Face(m_ftlib, fpos.c_str(), 0, &m_ftface); ///Init font
            if(errorCode != 0)
            {
                cout << "failed to init freetype face. error code = " << errorCode << endl;
                m_status = false;
            }
        }
	}

	TFreeType::~TFreeType()
	{
	    if(m_status)
        {
            FT_Done_Face(m_ftface);
            FT_Done_FreeType(m_ftlib);
        }
	}

	int TFreeType::GetSymbol(char symbol, ftchar *ftchar_p, int font_size)
	{
		int errorCode = 0;

        for(auto cached_char = m_cached_chars.begin(); cached_char != m_cached_chars.end(); cached_char++)
        {
            if((cached_char->font_size == font_size) && (cached_char->symbol == symbol))
            {
                ftchar_p = &*cached_char;
                return 0;
            }
        }

		errorCode = FT_Set_Char_Size(m_ftface, 0, font_size * 64, 96, 96); ///96 x 96 is default Windows font resolution
		if(errorCode != 0)
			return errorCode;

		errorCode = FT_Load_Char(m_ftface, (int)symbol, FT_LOAD_RENDER);
		if(errorCode != 0)
			return errorCode;

		FT_Matrix matrix;
		matrix.xx = (1 * 0x10000L);
		matrix.yx = (0);
		matrix.xy = (0);
		matrix.yy = (-1 * 0x10000L);
		FT_Set_Transform(m_ftface, &matrix, 0);

		int width = m_ftface->glyph->bitmap.width;
		int height = m_ftface->glyph->bitmap.rows;
		float advance = m_ftface->glyph->metrics.horiAdvance / 64;
		float bearingY = m_ftface->glyph->metrics.horiBearingY / 64;

		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		GLuint tempTexture;
		glGenTextures(1, &tempTexture);
		glBindTexture(GL_TEXTURE_2D, tempTexture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, width, height, 0, GL_ALPHA, GL_UNSIGNED_BYTE, m_ftface->glyph->bitmap.buffer);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glBindTexture(GL_TEXTURE_2D, 0);

		glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

		ftchar_p->height = height;
		ftchar_p->width = width;
		ftchar_p->advance = advance;
		ftchar_p->bearingY = bearingY;
		ftchar_p->texture = tempTexture;
		ftchar_p->font_size = font_size;
		ftchar_p->symbol = symbol;

        ftchar tempChar = *ftchar_p;
        m_cached_chars.push_back(tempChar);

		return errorCode;
	}

	int TFreeType::GetTextInfo(string text, int font_size, textinf *text_info)
	{
		int errorCode = 0;
		int total_width = 0;
		int max_height = 0;

		for(auto i = 0; i < text.size(); i++)
		{
			errorCode = FT_Set_Char_Size(m_ftface, 0, font_size * 64, 96, 96); ///96 x 96 is default Windows font resolution
			if(errorCode != 0)
				return errorCode;

			errorCode = FT_Load_Char(m_ftface, (int)text[i], FT_LOAD_RENDER);
			if(errorCode != 0)
				return errorCode;

			FT_Matrix matrix;
			matrix.xx = (1 * 0x10000L);
			matrix.yx = (0);
			matrix.xy = (0);
			matrix.yy = (-1 * 0x10000L);
			FT_Set_Transform(m_ftface, &matrix, 0);

			int glyph_height = m_ftface->glyph->metrics.height / 64;
			int advance = m_ftface->glyph->metrics.horiAdvance / 64;

			total_width += advance;
			max_height += glyph_height;
		}
		text_info->font_size = font_size;
		text_info->width = total_width;
		text_info->height = max_height / text.size();
		return errorCode;
	}
}
