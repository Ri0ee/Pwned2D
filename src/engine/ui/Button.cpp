#include "Button.h"

TButton::TButton() {}

TButton::TButton(string button_name, vector<vec2> shape, vec2 position, int align, color background_color, color foreground_color, color highlight_color, string caption)
{
	m_visible = true;
	m_collided = false;
	m_has_callback = false;

	m_name = button_name;
	m_caption = caption;
	m_pos = position;
	m_background = background_color;
	m_foreground = foreground_color;
	m_highlight_color = highlight_color;
	m_pressed_color = color{highlight_color.a * 0.5, highlight_color.b * 0.5, highlight_color.g * 0.5, 100};
	m_shape = shape;
	m_align = align;

	m_font_info.font_size = 30;
	m_font_info.height = 0;
	m_font_info.width = 0;

	FindBoudaries();
}

TButton::~TButton()
{
    cout << "button destructor called" << endl;
}

void TButton::SetRenderer(graphics::TRenderer *rndr)
{
	m_renderer = rndr;
}

void TButton::SetFontLib(freetype::TFreeType *ftlib)
{
	m_ftlib = ftlib;
	m_ftlib->GetTextInfo(m_caption, 30, &m_font_info);
}

void TButton::SetCallback(void (*callback_function)(void))
{
	m_callback_function = callback_function;
	m_has_callback = true;
}

void TButton::Draw()
{
	if(m_visible)
	{
		if(m_collided)
        {
            if(m_pressed)
                m_renderer->DrawPolygon(m_shape, m_pressed_color, m_pos, true);
            else
                m_renderer->DrawPolygon(m_shape, m_highlight_color, m_pos, true);
        }
		else
			m_renderer->DrawPolygon(m_shape, m_background, m_pos, true);

		switch(m_align)
		{
            case 1: ///Left align
                m_renderer->DrawText(m_caption, m_foreground, vec2(m_pos.a, m_pos.b + m_height - (m_font_info.height / 2) + 5), m_font_info.font_size, &m_ftlib);
                break;
            case 2: ///Middle align
                m_renderer->DrawText(m_caption, m_foreground, vec2(m_pos.a + ((int)m_width / 2) - (m_font_info.width / 2), m_pos.b + m_height - (m_font_info.height / 2) + 5), m_font_info.font_size, &m_ftlib);
                break;
            case 3: ///Right align
                m_renderer->DrawText(m_caption, m_foreground, vec2(m_pos.a + m_width - m_font_info.width, m_pos.b + m_height - (m_font_info.height / 2) + 5), m_font_info.font_size, &m_ftlib);
                break;
		}
	}
}

void TButton::CheckCollision(vec2 point)
{
	m_collided = PointCollisionTest(m_shape, vec2(point.a - m_pos.a, point.b - m_pos.b));
}

void TButton::Press()
{
	if(m_collided && m_visible)
        m_pressed = true;
}

void TButton::Release()
{
	if(m_pressed && m_visible)
	{
	    m_pressed = false;
		if(m_has_callback)
			m_callback_function();
		else
			cout << "button with caption '" << m_caption << "' does not have callback function\n";
	}
}

void TButton::FindBoudaries()
{
	float MaxW = m_shape[0].a, MaxH = m_shape[0].b;
	for(auto it = m_shape.begin(); it != m_shape.end(); it++)
    {
        MaxW = max(MaxW, it->a);
        MaxH = max(MaxH, it->b);
    }
	m_width = MaxW;
	m_height = MaxH;
}
