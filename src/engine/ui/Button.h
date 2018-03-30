#pragma once

#include <string>
#include <vector>
#include <algorithm>

#include "Structures.h"
#include "PointCollision.h"
#include "Render.h"
#include "FreeType.h"

using std::cout;
using std::cin;
using std::string;
using std::max;
using std::vector;

class TButton
{
public:
	TButton();
	TButton(string button_name, vector<vec2> shape, vec2 position, int align, color background_color, color foreground_color, color highlight_color, string caption);
	virtual ~TButton();

	void Draw();
	void FindBoudaries();

	void CheckCollision(vec2 point);
	void Press();
	void Release();

	void SetCallback(void (*callback_function)(void));
	void SetFontLib(freetype::TFreeType* ftlib);
	void SetRenderer(graphics::TRenderer* rndr);

	freetype::TFreeType* m_ftlib;
	graphics::TRenderer* m_renderer;

	vector<vec2> m_shape;
	string m_caption;
	vec2 m_pos;

	color m_background;
	color m_foreground;
	color m_highlight_color;
	color m_pressed_color;

	float m_width;
	float m_height;
	bool m_visible;
	bool m_collided;
	bool m_pressed;
	bool m_has_callback;
	int m_align;
	string m_name;

	freetype::textinf m_font_info;
	void (*m_callback_function)(void);
};
