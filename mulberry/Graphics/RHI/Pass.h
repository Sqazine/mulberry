#pragma once
#include <memory>
#include <vector>
#include "Base.h"
#include "Color.h"
#include "Texture.h"
#include "Pipeline.h"
#include "Graphics/RHI/VK/Pass.h"
namespace mulberry::rhi
{
    class GraphicsPass : GRAPHICS_RHI_IMPL_DECL(GraphicsPass)
    {
    public:
        GraphicsPass();
        ~GraphicsPass();

        void SetClearColor(const Color &clearColor);
        void IsClearColorBuffer(bool isClear);

        void SetViewport(const Viewport &viewport);

        void SetPipeline(const GraphicsPipeline &pipeline);

        void Begin();
        void End();
    };
}