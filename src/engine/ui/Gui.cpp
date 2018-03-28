#include "Gui.h"

namespace gui
{
    TGui::TGui(freetype::TFreeType *ftlib, graphics::TRenderer *renderer, input::TInputManager *inputmngr)
    {
        m_visible = false;
        m_ftlib = ftlib;
        m_renderer = renderer;
        m_input_manager = inputmngr;
        m_window_width = renderer->m_window_width;
        m_window_height = renderer->m_window_height;
    }

    TGui::~TGui()
    {

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

        vector<vec2> button_shape;
        button_shape.push_back(vec2(0, 0));    button_shape.push_back(vec2(300, 0));
        button_shape.push_back(vec2(300, 40)); button_shape.push_back(vec2(50, 40));

        TButton button_1, button_2, button_3;
        button_1 = TButton("Start", button_shape, vec2(window_width - 300, 10), 1, btncolor, fg_btncolor, hl_btncolor, "Start");     AddButton(button_1);
        button_2 = TButton("Button_2", button_shape, vec2(window_width - 300, 80), 2, btncolor, fg_btncolor, hl_btncolor, "middle"); AddButton(button_2);
        button_3 = TButton("Button_3", button_shape, vec2(window_width - 300, 150), 3, btncolor, fg_btncolor, hl_btncolor, "right"); AddButton(button_3);

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
        m_vecUIButton.push_back(button);
        button.SetFontLib(m_ftlib);
        button.SetRenderer(m_renderer);
    }

    void TGui::Draw()
    {
        if(m_visible)
        {
            for(auto button = m_vecUIButton.begin(); button != m_vecUIButton.end(); button++)
                button->Draw();
        }
    }

    void TGui::CheckCollsions(vec2 point)
    {
        if(m_visible)
        {
            for(auto i = 0; i < m_vecUIButton.size(); i++)
                m_vecUIButton[i].CheckCollision(point);
        }
    }

    void TGui::Press()
    {
        if(m_visible)
        {
            for(auto i = 0; i < m_vecUIButton.size(); i++)
                m_vecUIButton[i].Press();
        }
    }
}
