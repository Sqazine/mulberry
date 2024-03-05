#include "Material.h"
#include <string>
#include "Shader.h"
namespace mulberry
{

    const std::string spriteVertShader = "out vec2 fragTexcoord;\n"
                                         "in vec2 inPosition;\n"
                                         "in vec2 inTexcoord;\n"
                                         "uniform mat4 modelMat;\n"
                                         "uniform mat4 viewMat;\n"
                                         "uniform mat4 projMat;\n"
                                         "uniform vec2 tiling;\n"
                                         "uniform vec2 offset;\n"
                                         "void main()\n"
                                         "{\n"
                                         "	gl_Position=projMat*viewMat*modelMat*vec4(inPosition,0.0,1.0);\n"
                                         "	fragTexcoord= inTexcoord*tiling+offset;\n"
                                         "}";

    const std::string spriteFragShader = "out vec4 outColor;\n"
                                         "in vec2 fragTexcoord;\n"
                                         "uniform sampler2D sprite;\n"
                                         "void main()\n"
                                         "{\n"
                                         "	outColor=texture(sprite,fragTexcoord);\n"
                                         "}";

    const std::string gizmoVertShader = "in vec2 inPosition;\n"
                                        "uniform mat4 modelMat;\n"
                                        "uniform mat4 viewMat;\n"
                                        "uniform mat4 projMat;\n"
                                        "void main()\n"
                                        "{\n"
                                        "	gl_Position=projMat*viewMat*modelMat*vec4(inPosition,0.0,1.0);\n"
                                        "}";

    const std::string gizmoFragShader = "out vec4 outColor;\n"
                                        "void main()\n"
                                        "{\n"
                                        "	outColor=vec4(0.0,1.0,0.0,1.0);\n"
                                        "}";

    SpriteMaterial::SpriteMaterial()
        : mTiling(1.0), mOffset(0.0)
    {
        GetGraphicsPipeline()->SetVertexShader(new rhi::Shader(rhi::ShaderStage::VERTEX, spriteVertShader))
                              .SetFragmentShader(new rhi::Shader(rhi::ShaderStage::FRAGMENT, spriteFragShader))
                              .SetCullMode(rhi::CullMode::BACK)
                              .SetPrimitiveTopology(rhi::PrimitiveTopology::TRIANGLE_LIST);
    }

    SpriteMaterial::~SpriteMaterial()
    {
    }

    void SpriteMaterial::SetSprite(rhi::Texture *sprite)
    {
        this->mSprite = sprite;
    }

    const rhi::Texture *SpriteMaterial::GetSprite() const
    {
        return mSprite;
    }

    void SpriteMaterial::SetTiling(const Vec2 &t)
    {
        mTiling = t;
    }

    const Vec2 &SpriteMaterial::GetTiling() const
    {
        return mTiling;
    }

    void SpriteMaterial::SetOffSet(const Vec2 &o)
    {
        mOffset = o;
    }

    const Vec2 &SpriteMaterial::GetOffset() const
    {
        return mOffset;
    }

    void SpriteMaterial::SetDefaultUniformValue() const
    {
        /*shaderProgram->SetTexture("sprite",mSprite);
        shaderProgram->SetDefaultUniformValue("tiling", mTiling);
        shaderProgram->SetDefaultUniformValue("offset", mOffset);*/
    }

    GizmoMaterial::GizmoMaterial()
    {
        auto vertShader = rhi::Shader(rhi::ShaderStage::VERTEX, gizmoVertShader);
        auto fragShader = rhi::Shader(rhi::ShaderStage::FRAGMENT, gizmoFragShader);
        /*  shaderProgram = std::make_unique<ShaderGroup>();
          shaderProgram->AttachShader(vertShader);
          shaderProgram->AttachShader(fragShader);*/
    }

    GizmoMaterial::~GizmoMaterial()
    {
    }
}