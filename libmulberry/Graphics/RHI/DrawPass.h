#pragma once
#include <memory>
#include "Math/Color.h"
#include "Graphics/RHI/GL/GLDrawPass.h"
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
    };
}