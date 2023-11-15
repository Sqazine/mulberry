#pragma once
#include <memory>
#include "Math/Color.h"
#include "Graphics/RHI/GL/GLDrawPass.h"
#include "Graphics/RHI/VK/VKDrawPass.h"
namespace mulberry
{
    class DrawPass
    {
    public:
        DrawPass();
        ~DrawPass();

        void SetClearColor(const Color &clearColor);
        void IsClearColorBuffer(bool isClear);

        void Begin();
        void End();

    private:
        std::unique_ptr<GLDrawPass> mGLDrawPass;
        std::unique_ptr<VKDrawPass> mVKDrawPass;
    };
}