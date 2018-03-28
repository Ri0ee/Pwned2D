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
	m_shape = shape;
	m_align = align;

	m_font_info.font_size = 30;
	m_font_info.height = 0;
	m_font_info.width = 0;

	FindBoudaries();
}

TButton::~TButton()
{

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
			m_renderer->DrawPolygon(m_shape, m_highlight_color, m_pos, true);
		else
			m_renderer->DrawPolygon(m_shape, m_background, m_pos, true);

		switch(m_align)
		{
		case 1:
			m_renderer->DrawText(m_caption, m_foreground, vec2(m_pos.a, m_pos.b + m_height - (m_font_info.height / 2) + 5), m_font_info.font_size, m_ftlib);
			break;
		case 2:
			m_renderer->DrawText(m_caption, m_foreground, vec2(m_pos.a + ((int)m_width / 2) - (m_font_info.width / 2), m_pos.b + m_height - (m_font_info.height / 2) + 5), m_font_info.font_size, m_ftlib);
			break;
		case 3:
			m_renderer->DrawText(m_caption, m_foreground, vec2(m_pos.a + m_width - m_font_info.width, m_pos.b + m_height - (m_font_info.height / 2) + 5), m_font_info.font_size, m_ftlib);
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
	{
		if(m_has_callback)
			m_callback_function();
		else
			cout << "button with caption '" << m_caption << "' does not have callback function\n";
	}
}

void TButton::FindBoudaries()
{
	float MaxW = 0, MaxH = m_shape[0].a;
	for(unsigned int i = 0; i < m_shape.size(); i++)
	{
		MaxW = std::max(m_shape[i].a, MaxW);
		MaxH = std::max(m_shape[i].b, MaxH);
	}
	m_width = MaxW;
	m_height = MaxH;
}
