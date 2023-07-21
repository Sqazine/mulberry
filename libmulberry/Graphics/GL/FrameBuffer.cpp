#include "FrameBuffer.h"
#include <glad/glad.h>
namespace mulberry::gl
{
    FrameBuffer::FrameBuffer()
    {
        glGenFramebuffers(1, &mFrameBufferID);
    }

    FrameBuffer::FrameBuffer(const Texture *colorAttachment0)
    {
        glGenFramebuffers(1, &mFrameBufferID);
        SetActive(true);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorAttachment0->GetID(), 0);
        SetActive(false);
    }

    FrameBuffer::FrameBuffer(const std::vector<Texture *> &colorAttachments)
    {
        glGenFramebuffers(1, &mFrameBufferID);
        SetActive(true);
        for (int32_t i = 0; i < colorAttachments.size(); ++i)
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, colorAttachments[i]->GetID(), 0);
        SetActive(false);
    }

    FrameBuffer::~FrameBuffer()
    {
        glDeleteFramebuffers(1, &mFrameBufferID);
    }

    void FrameBuffer::SetActive(bool isActive)
    {
        if (isActive)
            glBindFramebuffer(GL_FRAMEBUFFER, mFrameBufferID);
        else
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
}