#include "GLDrawPass.h"
#include <glad/glad.h>
namespace mulberry
{
    void GLDrawPass::SetClearColor(const Color &clearColor)
    {
        mClearColor = clearColor;
    }
    void GLDrawPass::IsClearColorBuffer(bool isClear)
    {
        mIsClearColorBuffer = isClear;
    }

    void GLDrawPass::Begin()
    {
        glClearColor(mClearColor.r, mClearColor.g, mClearColor.b, mClearColor.a);

        if (mIsClearColorBuffer)
            glClear(GL_COLOR_BUFFER_BIT);
    }

    void GLDrawPass::End()
    {
    }
}