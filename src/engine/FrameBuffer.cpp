#include "FrameBuffer.h"

TFrameBuffer::TFrameBuffer()
{}

TFrameBuffer::TFrameBuffer(int width, int height)
{}

TFrameBuffer::~TFrameBuffer()
{}

void TFrameBuffer::Create(int width, int height)
{
    m_width = width;
    m_height = height;

    glGenRenderbuffers(1, &m_depth_id);
    glBindRenderbuffer(GL_RENDERBUFFER, m_depth_id);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);

    glGenTextures(1, &m_texture_id);
    glBindTexture(GL_TEXTURE_2D, m_texture_id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glBindTexture(GL_TEXTURE_2D, 0);

    glGenFramebuffers(1, &m_framebuffer_id);
    glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer_id);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_texture_id, 0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_depth_id);

    int fbo_status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if(fbo_status == GL_FRAMEBUFFER_COMPLETE)
        m_status = true;
    else
        m_status = false;

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void TFrameBuffer::CreateMultisampled(int width, int height, int samples)
{
    m_width = width;
    m_height = height;

    glGenRenderbuffers(1, &m_rbo_color_id);
    glBindRenderbuffer(GL_RENDERBUFFER, m_rbo_color_id);
    glRenderbufferStorageMultisample(GL_RENDERBUFFER, samples, GL_RGB8, width, height);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);

    glGenRenderbuffers(1, &m_rbo_depth_id);
    glBindRenderbuffer(GL_RENDERBUFFER, m_rbo_depth_id);
    glRenderbufferStorageMultisample(GL_RENDERBUFFER, samples, GL_DEPTH_COMPONENT, width, height);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);

    glGenFramebuffers(1, &m_framebuffer_id);
    glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer_id);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, m_rbo_color_id);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_rbo_depth_id);

    int FBOStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if(FBOStatus == GL_FRAMEBUFFER_COMPLETE)
        m_status = true;
    else
        m_status = false;

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void TFrameBuffer::Bind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer_id);
    glPushAttrib(GL_VIEWPORT_BIT);
    glViewport(0, 0, m_width, m_height);
}

void TFrameBuffer::Unbind()
{
    glPopAttrib();
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
