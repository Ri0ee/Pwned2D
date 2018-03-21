#include "Gui.h"

namespace gui
{
    TGui::TGui()
    {
        m_visible = false;
    }

    TGui::~TGui()
    {}

    void TGui::Reset()
    {
        m_vecUIButton.clear();
        m_visible = false;
    }

    void TGui::AddButton(TButton button)
    {
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
