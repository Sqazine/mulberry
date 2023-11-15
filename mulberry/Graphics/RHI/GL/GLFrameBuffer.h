#pragma once
#include <cstdint>
#include <vector>
#include "GLTexture.h"
namespace mulberry
{
    class GLFrameBuffer
    {
    public:
        GLFrameBuffer();
        GLFrameBuffer(const GLTexture *colorAttachment0);
        GLFrameBuffer(const std::vector<GLTexture *> &colorAttachments);
        ~GLFrameBuffer();

        void SetActive(bool isActive);

    private:
        uint32_t mFrameBufferID;
    };
}