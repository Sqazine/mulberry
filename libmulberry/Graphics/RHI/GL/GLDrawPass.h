#pragma once
#include "Math/Color.h"
namespace mulberry
{
    class GLDrawPass
    {
    public:
        void SetClearColor(const Color &clearColor);
        void IsClearColorBuffer(bool isClear);

        void Begin();
        void End();

    private:
        Color mClearColor;
        bool mIsClearColorBuffer;
    };
}