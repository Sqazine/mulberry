#pragma once
#include <string_view>
#include <memory>
#include <vector>
#include "Base.h"
#include "GraphicsContext.h"
#include "Buffer.h"
#include "Texture.h"

namespace mulberry
{
    class Shader : GRAPHICS_RHI_IMPL_DECL(Shader)
    {
    public:
        Shader(ShaderStage type, std::string_view content);
        ~Shader();

        const ShaderStage &Type() const;
    };
}