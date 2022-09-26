#pragma once
#include <cstdint>
#include <vector>
#include "Texture.h"
namespace  mulberry::GL
{
    class FrameBuffer
    {
    public:
        FrameBuffer();
        FrameBuffer(const Texture *colorAttachment0);
        FrameBuffer(const std::vector<Texture *> &colorAttachments);
        ~FrameBuffer();

        void SetActive(bool isActive);

    private:
        uint32_t mFrameBufferID;
    };
}