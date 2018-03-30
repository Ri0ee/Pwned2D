#pragma once

#define DRAWMODE_FILLED

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>
#include <vector>
#include <iostream>

#include "Structures.h"
#include "FreeType.h"
#include "FrameBuffer.h"
#include "GlitchShader.h"
#include "BasicShader.h"
#include "BlurShader.h"
#include "Utility.h"
#include "WindowManager.h"

using std::cout;
using std::endl;
using std::string;
using std::vector;

namespace graphics
{
	class TRenderer
	{
	public:
		TRenderer();
		virtual ~TRenderer();

		void Clear();
		void BeginRender();
		void EndRender();
		void DebugInfo();
		void DrawFPSCounter();
		void DrawTexture(vec2 position, float width, float height, GLuint texture, bool use_blend);
		void DrawPolygon(vector<vec2> shape, color shape_color, vec2 position, bool use_blend);
		void DrawText(string text, color text_color, vec2 position, int text_size, freetype::TFreeType *ftlib);

		TFrameBuffer m_fbo;
		TFrameBuffer m_fbo_msaa;

		TGlitchShader m_glitch_shader;
		TBlurShader m_blur_shader;
		TBasicShader m_basic_shader;

		int m_window_width;
		int m_window_height;
		int m_max_msaa_samples;

		float m_fps;
		int m_frame_count;

		bool m_use_msaa;

		window::TWindowManager* m_window_manager;
	};
}
