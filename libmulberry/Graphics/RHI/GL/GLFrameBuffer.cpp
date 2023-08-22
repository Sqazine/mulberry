#include "GLFrameBuffer.h"
#include <glad/glad.h>
namespace mulberry
{
    GLFrameBuffer::GLFrameBuffer()
    {
        glGenFramebuffers(1, &mFrameBufferID);
    }

    GLFrameBuffer::GLFrameBuffer(const GLTexture *colorAttachment0)
    {
        glGenFramebuffers(1, &mFrameBufferID);
        SetActive(true);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorAttachment0->GetHandle(), 0);
        SetActive(false);
    }

    GLFrameBuffer::GLFrameBuffer(const std::vector<GLTexture *> &colorAttachments)
    {
        glGenFramebuffers(1, &mFrameBufferID);
        SetActive(true);
        for (int32_t i = 0; i < colorAttachments.size(); ++i)
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, colorAttachments[i]->GetHandle(), 0);
        SetActive(false);
    }

    GLFrameBuffer::~GLFrameBuffer()
    {
        glDeleteFramebuffers(1, &mFrameBufferID);
    }

    void GLFrameBuffer::SetActive(bool isActive)
    {
        if (isActive)
            glBindFramebuffer(GL_FRAMEBUFFER, mFrameBufferID);
        else
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
}