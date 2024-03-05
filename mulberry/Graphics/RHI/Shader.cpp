#include "Shader.h"
#include "App.h"
#include "VK/Shader.h"
namespace mulberry::rhi
{
    Shader::Shader(ShaderStage type, std::string_view content)
        : Base(type, content)
    {
    }
    Shader::~Shader()
    {
    }

    const ShaderStage &Shader::Type() const
    {
        GRAPHICS_RHI_IMPL_SWITCHER(return GetVkImpl()->Type());
    }
}