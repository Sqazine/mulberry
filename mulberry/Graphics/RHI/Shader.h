#pragma once
#include <string_view>
#include <memory>
#include <vector>
#include "GraphicsContext.h"
#include "Buffer.h"
#include "Texture.h"
#include "VK/Shader.h"

namespace mulberry
{
    class Shader
    {
    public:
        Shader(ShaderStage type, std::string_view content);
        ~Shader();

        const ShaderStage &Type() const;
    private:
        friend class RasterShaderGroup;
        std::unique_ptr<class vk::Shader> mVKShaderImpl;
    };
}