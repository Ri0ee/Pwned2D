#include "Render.h"

namespace graphics
{
    TRenderer::TRenderer()
    {
        m_use_msaa = false;
        m_fps = 0;
    }

    TRenderer::~TRenderer()
    {
        cout << "TRenderer destructor called\n";
    }

    void TRenderer::BeginRender()
    {
        if(m_fbo_msaa.m_status && m_use_msaa)
        {
            m_fbo_msaa.Bind();
            Clear();
        }
        else
        {
            m_fbo.Bind();
            Clear();
        }
    }

    void TRenderer::EndRender()
    {
        if(m_fbo_msaa.m_status && m_use_msaa)
        {
            m_fbo_msaa.Unbind();

            glBindFramebuffer(GL_READ_FRAMEBUFFER, m_fbo_msaa.m_framebuffer_id);
            glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_fbo.m_framebuffer_id);
            glBlitFramebuffer(0, 0, m_fbo_msaa.m_width, m_fbo_msaa.m_height, 0, 0, m_fbo.m_width, m_fbo.m_height, GL_COLOR_BUFFER_BIT, GL_LINEAR);
            glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
            glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
        }
        else
        {
            m_fbo.Unbind();
            Clear();
        }
        Clear();
        DrawTexture(vec2(0, 0), m_window_width, m_window_height, m_fbo.m_texture_id, false);
    }

    /*
    void TRenderer::GameplayRender()
    {
        color text_color{255, 255, 255, 100};

        DrawText("fps: " + to_string(fps), text_color, vec2(0, 10), 10, ftlib);
        DrawText((Game.m_collision_flag?"collision: yes":"collision: no"), text_color, vec2(0, 21), 10, ftlib);
        DrawText("depth: " + to_string(Game.m_collsion_depth), text_color, vec2(0, 32), 10, ftlib);
        DrawText("mouse pos: (" + to_string(mouse_pos.a) + ";" + to_string(mouse_pos.b) + ")", text_color, vec2(0, 44), 10, ftlib);

        DrawTexture(vec2(100, 100), 100, 100, resmngr.m_game_textures.back(), true);
    }
    */

    void TRenderer::DrawFPSCounter()
    {
        //DrawText("fps: " + to_string(fps), text_color, vec2(0, 10), 10, ftlib);
    }

    void TRenderer::DebugInfo()
    {
        cout << "OpenGL version: " << glGetString(GL_VERSION) << "\n";
        cout << "Shading language version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << "\n";
        cout << "Vendor: " << glGetString(GL_VENDOR) << "\n";
        cout << "Renderer: " << glGetString(GL_RENDERER) << "\n";
        cout << "Maximum MSAA Samples: " << m_max_msaa_samples << "\n";
    }

    void TRenderer::Init(int window_width, int window_height)
    {
        m_window_width = window_width;
        m_window_height = window_height;

        glewExperimental = GL_TRUE;
        glewInit();

        glViewport(0, 0, m_window_width, m_window_height);
        glMatrixMode(GL_PROJECTION);
        glOrtho(0, m_window_height, m_window_height, 0, -1, 1);
        glMatrixMode(GL_MODELVIEW);
        glEnable(GL_TEXTURE_2D);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

        glGetIntegerv(GL_MAX_SAMPLES, &m_max_msaa_samples);

        m_fbo.Create(m_window_width, m_window_height);
        m_fbo_msaa.CreateMultisampled(m_window_width, m_window_height, 4);

        DebugInfo();
    }

    void TRenderer::Clear()
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glLoadIdentity();
    }

    void TRenderer::DrawTexture(vec2 position, float width, float height, GLuint texture, bool use_blend)
    {
        float X0 = position.a;
        float Y0 = position.b;

        if(use_blend)
        {
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        }
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        glBegin(GL_QUADS);
            glTexCoord2f(0, 0); glVertex3f(X0, Y0 + height, 0.0f);
            glTexCoord2f(1, 0); glVertex3f(X0 + width, Y0 + height, 0.0f);
            glTexCoord2f(1, 1); glVertex3f(X0 + width, Y0, 0.0f);
            glTexCoord2f(0, 1); glVertex3f(X0, Y0, 0.0f);
        glEnd();
        glBindTexture(GL_TEXTURE_2D, 0);
        if(use_blend)
            glDisable(GL_BLEND);
    }

    void TRenderer::DrawPolygon(vector<vec2> shape, color shape_color, vec2 position, bool use_blend)
    {
        float X0 = position.a;
        float Y0 = position.b;

        if(use_blend)
        {
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        }

        #ifdef DRAWMODE_FILLED
        glColor4f(float(shape_color.r) / 255, float(shape_color.g) / 255, float(shape_color.b) / 255, float(shape_color.a) / 100);
        glBegin(GL_POLYGON);
        for(unsigned int i = 0; i < shape.size(); i++)
            glVertex2f(X0 + shape[i].a, Y0 + shape[i].b);
        glEnd();
        #endif

        #ifdef DRAWMODE_WIREFRAME
        for(unsigned int i = 0; i < shape.size() - 1; i++)
        {
            glColor4f(float(shape_color.r) / 255, float(shape_color.g) / 255, float(shape_color.b) / 255, float(shape_color.a) / 100);
            glBegin(GL_LINES);
            glVertex2f(X0 + shape[i].a, Y0 + shape[i].b);
            glVertex2f(X0 + shape[i+1].a, Y0 + shape[i+1].b);
            glEnd();
        }
        glColor4f(float(shape_color.r) / 255, float(shape_color.g) / 255, float(shape_color.b) / 255, float(shape_color.a) / 100);
        glBegin(GL_LINES);
        glVertex2f(X0 + shape[0].a, Y0 + shape[0].b);
        glVertex2f(X0 + shape[shape.size()-1].a, Y0 + shape[shape.size()-1].b);
        glEnd();
        #endif

        if(use_blend)
            glDisable(GL_BLEND);
        glColor4f(1, 1, 1, 1);
    }

    void TRenderer::DrawText(string text, color text_color, vec2 position, int text_size, freetype::TFreeType &ftlib)
    {
        float shift = 0;
        for(unsigned int i = 0; i < text.size(); i++)
        {
            freetype::ftchar *tempChar = new freetype::ftchar();
            ftlib.GetSymbol(text[i], tempChar, text_size);

            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glColor4f(float(text_color.r) / 255, float(text_color.g) / 255, float(text_color.b) / 255, float(text_color.a) / 100);
            DrawTexture(vec2(position.a + shift, position.b - tempChar->bearingY), tempChar->width, tempChar->height, tempChar->texture, false);
            glColor4f(1, 1, 1, 1);
            glDisable(GL_BLEND);

            shift+=tempChar->advance;

            delete tempChar;
        }
    }
}
