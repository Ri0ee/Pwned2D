#include "Gui.h"

namespace gui
{
    TGui::TGui()
    {
        m_visible = false;
    }

    TGui::~TGui()
    {
        cout << "TGui destructor called\n";
    }

    void TGui::Init(freetype::TFreeType *ftlib, graphics::TRenderer *rndr, int window_width, int window_height)
    {
        m_ftlib = ftlib;
        m_renderer = rndr;

        m_window_width = window_width;
        m_window_height = window_height;

        color btncolor{77, 0, 57, 50};
        color hl_btncolor{133, 51, 85, 50};
        color fg_btncolor{255, 51, 204, 100};

        vector<vec2> vertex;
        vertex.push_back(vec2(0, 0));    vertex.push_back(vec2(300, 0));
        vertex.push_back(vec2(300, 40)); vertex.push_back(vec2(50, 40));
        TButton button_1("Start", vertex, vec2(window_width - 300, 10), 1, btncolor, fg_btncolor, hl_btncolor, "left");
        AddButton(button_1);
        TButton button_2("Button_2", vertex, vec2(window_width - 300, 80), 2, btncolor, fg_btncolor, hl_btncolor, "middle");
        AddButton(button_2);
        TButton button_3("Button_3", vertex, vec2(window_width - 300, 150), 3, btncolor, fg_btncolor, hl_btncolor, "right");
        AddButton(button_3);

        m_visible = true;
    }

    void TGui::Reset()
    {
        m_vecUIButton.clear();
        m_visible = false;
    }

    TButton& TGui::GetButton(string button_name)
    {
        for(unsigned int i = 0; i < m_vecUIButton.size(); i++)
            if(m_vecUIButton[i].m_name == button_name)
                return m_vecUIButton[i];
        return m_vecUIButton[0];
    }

    void TGui::AddButton(TButton button)
    {
        button.SetFontLib(m_ftlib);
        m_vecUIButton.push_back(button);
    }

    void TGui::Draw()
    {
        if(m_visible)
        {
            for(unsigned int i = 0; i < m_vecUIButton.size(); i++)
                m_vecUIButton[i].Draw();
        }
    }

    void TGui::CheckCollsions(vec2 point)
    {
        if(m_visible)
        {
            for(unsigned int i = 0; i < m_vecUIButton.size(); i++)
                m_vecUIButton[i].CheckCollision(point);
        }
    }

    void TGui::Press()
    {
        if(m_visible)
        {
            for(unsigned int i = 0; i < m_vecUIButton.size(); i++)
                m_vecUIButton[i].Press();
        }
    }
}
