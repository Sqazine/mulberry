#pragma once
#include <memory>
#include <vector>
#include "Defs.h"
#include "Color.h"
#include "Texture.h"
#include "Pipeline.h"
#include "Graphics/RHI/VK/Pass.h"
namespace mulberry
{
    class SwapChainPass : GRAPHICS_RHI_IMPL_DECL(SwapChainPass)
    {
    public:
        SwapChainPass();
        ~SwapChainPass();

        void SetViewport(const Viewport &viewport);

        void SetPipeline(const GraphicsPipeline &pipeline);

        void Begin();
        void End();

        ColorAttachment* GetColorAttachment() const;
    };
}