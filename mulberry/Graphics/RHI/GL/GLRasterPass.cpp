#include "GLRasterPass.h"
#include <glad/glad.h>
namespace mulberry
{
    void GLRasterPass::SetClearColor(const Color &clearColor)
    {
        mClearColor = clearColor;
    }
    void GLRasterPass::IsClearColorBuffer(bool isClear)
    {
        mIsClearColorBuffer = isClear;
    }

    void GLRasterPass::Begin()
    {
        glClearColor(mClearColor.r, mClearColor.g, mClearColor.b, mClearColor.a);

        if (mIsClearColorBuffer)
            glClear(GL_COLOR_BUFFER_BIT);
    }

    void GLRasterPass::End()
    {
    }
}