#include "FreeType.h"

namespace freetype
{
    TFreeType::TFreeType()
    {}

    TFreeType::~TFreeType()
    {
        FT_Done_Face(ftface);
        FT_Done_FreeType(ftlib);
    }

    int TFreeType::GetSymbol(const char &symbol, ftchar *ftchar_p, int font_size)
    {
        int errorCode = 0;

        for(unsigned int i = 0; i < m_cached_chars.size(); i++)
            if((m_cached_chars[i]->font_size == font_size) && (m_cached_chars[i]->symbol == symbol))
            {
                memcpy(ftchar_p, m_cached_chars[i], sizeof(ftchar));
                return 0;
            }

        errorCode = FT_Set_Char_Size(ftface, 0, font_size * 64, 96, 96);
        if(errorCode != 0)
        {
            cout << "Failed to set char size. error code: " << errorCode << "\n";
            return errorCode;
        }

        errorCode = FT_Load_Char(ftface, (int)symbol, FT_LOAD_RENDER);
        if(errorCode != 0)
        {
            cout << "Failed to load glyph of symbol '" << symbol << "'\n";
            return errorCode;
        }

        FT_Matrix matrix;
        matrix.xx = (1 * 0x10000L); matrix.yx = (0);
        matrix.xy = (0); matrix.yy = (-1 * 0x10000L);
        FT_Set_Transform(ftface, &matrix, 0);

        int width = ftface->glyph->bitmap.width;
        int height = ftface->glyph->bitmap.rows;
        float advance = ftface->glyph->metrics.horiAdvance / 64;
        float bearingY = ftface->glyph->metrics.horiBearingY / 64;

        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        GLuint tempTexture;
        glGenTextures(1, &tempTexture);
        glBindTexture(GL_TEXTURE_2D, tempTexture);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, width, height, 0, GL_ALPHA, GL_UNSIGNED_BYTE, ftface->glyph->bitmap.buffer);
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

        ftchar *tempChar = (ftchar*)malloc(sizeof(ftchar));
        memcpy(tempChar, ftchar_p, sizeof(ftchar));
        m_cached_chars.push_back(tempChar);
        cout << "symbol '" << tempChar->symbol << "' cached\n";

        return errorCode;
    }

    int TFreeType::GetTextInfo(string text, int font_size, textinf *text_info)
    {
        int errorCode = 0;

        int total_width = 0;
        int max_height = 0;

        for(unsigned int i = 0; i < text.size(); i++)
        {
            errorCode = FT_Set_Char_Size(ftface, 0, font_size * 64, 96, 96);
            if(errorCode != 0)
            {
                cout << "Failed to freetype set char size. Error code: " << errorCode << "\n";
                return errorCode;
            }

            errorCode = FT_Load_Char(ftface, (int)text[i], FT_LOAD_RENDER);
            if(errorCode != 0)
            {
                cout << "Failed to load Glyph of symbol '" << text[i] << "'\n";
                return errorCode;
            }

            FT_Matrix matrix;
            matrix.xx = (1 * 0x10000L); matrix.yx = (0);
            matrix.xy = (0); matrix.yy = (-1 * 0x10000L);
            FT_Set_Transform(ftface, &matrix, 0);

            int glyph_height = ftface->glyph->metrics.height / 64;
            int advance = ftface->glyph->metrics.horiAdvance / 64;

            total_width += advance;
            max_height += glyph_height;
        }
        text_info->font_size = font_size;
        text_info->width = total_width;
        text_info->height = max_height / text.size();
        return errorCode;
    }

    void TFreeType::Init(string directory, string font_name)
    {
        int errorCode;

        errorCode=FT_Init_FreeType(&ftlib);
        if(errorCode != 0)
            cout << "Failed to init FreeType library\n";

        string fpos = directory + font_name;
        errorCode = FT_New_Face(ftlib, fpos.c_str(), 0, &ftface);
        if(errorCode != 0)
            cout << "Failed to init FreeType face. error code: " << errorCode << "\n";

        use_kerning = FT_HAS_KERNING(ftface);

        return;
    }
}
