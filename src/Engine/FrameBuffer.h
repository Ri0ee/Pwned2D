#pragma once

#include <iostream>

#define GLEW_STATIC
#include <GL/glew.h>

class TFrameBuffer
{
    public:
        TFrameBuffer();
        TFrameBuffer(int width, int height);
        virtual ~TFrameBuffer();

        void Create(int width, int height);
        void CreateMultisampled(int width, int height, int samples);
        void Bind();
        void Unbind();

        int m_width;
        int m_height;
        int m_status;

        GLuint m_framebuffer_id;

        GLuint m_texture_id;
        GLuint m_depth_id;

        GLuint m_rbo_color_id;
        GLuint m_rbo_depth_id;
};
