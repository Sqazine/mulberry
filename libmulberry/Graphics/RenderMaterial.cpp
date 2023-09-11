#include "RenderMaterial.h"
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

    void RenderMaterial::SetShaderProgram(ShaderProgram *program)
    {
        shaderProgram.reset(program);
    }

    ShaderProgram *RenderMaterial::GetShaderProgram() const
    {
        return shaderProgram.get();
    }

    SpriteMaterial::SpriteMaterial()
        : mTiling(1.0), mOffset(0.0)
    {
        auto vertShader = ShaderModule(ShaderType::VERTEX, spriteVertShader);
        auto fragShader = ShaderModule(ShaderType::FRAGMENT, spriteFragShader);
        shaderProgram = std::make_unique<ShaderProgram>();
        shaderProgram->AttachShader(vertShader);
        shaderProgram->AttachShader(fragShader);
    }
    
    SpriteMaterial::~SpriteMaterial()
    {
    }

    void SpriteMaterial::SetSprite(Texture *sprite)
    {
        this->mSprite = sprite;
    }

    const Texture *SpriteMaterial::GetSprite() const
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

    void SpriteMaterial::SetUniformValue() const
    {
        shaderProgram->SetTexture("sprite",mSprite);
        shaderProgram->SetUniformValue("tiling", mTiling);
        shaderProgram->SetUniformValue("offset", mOffset);
    }

    void SpriteMaterial::ResetUniformValue() const
    {
       
    }

    GizmoMaterial::GizmoMaterial()
    {
        auto vertShader = ShaderModule(ShaderType::VERTEX, gizmoVertShader);
        auto fragShader = ShaderModule(ShaderType::FRAGMENT, gizmoFragShader);
        shaderProgram = std::make_unique<ShaderProgram>();
        shaderProgram->AttachShader(vertShader);
        shaderProgram->AttachShader(fragShader);
    }

    GizmoMaterial::~GizmoMaterial()
    {
    }
}