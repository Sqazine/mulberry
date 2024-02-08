#include "Shader.h"
#include "App.h"
namespace mulberry::rhi
{
    Shader::Shader(ShaderStage type, std::string_view content)
    {
        GRAPHICS_RHI_IMPL_SWITCHER(mVKShaderImpl = std::make_unique<vk::Shader>(type, content));
    }
    Shader::~Shader()
    {
        GRAPHICS_RHI_IMPL_SWITCHER(mVKShaderImpl.reset(nullptr));
    }

    const ShaderStage &Shader::Type() const
    {
        GRAPHICS_RHI_IMPL_SWITCHER(return mVKShaderImpl->Type());
    }
}