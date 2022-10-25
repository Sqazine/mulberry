#include "RenderMaterial.h"

namespace mulberry
{

    const std::string spriteVertShader = "#version 330 core\n"
                                         "out vec2 fragTexcoord;\n"
                                         "in vec2 inPosition;\n"
                                         "in vec2 inTexcoord;\n"
                                         "uniform mat4 modelMat;\n"
                                         "uniform mat4 viewMat;\n"
                                         "uniform mat4 projMat;\n"
                                         "void main()\n"
                                         "{\n"
                                         "	gl_Position=projMat*viewMat*modelMat*vec4(inPosition,0.0,1.0);\n"
                                         "	fragTexcoord=inTexcoord;\n"
                                         "}";

    const std::string spriteFragShader = "#version 330 core\n"
                                         "out vec4 outColor;\n"
                                         "in vec2 fragTexcoord;\n"
                                         "uniform sampler2D sprite;\n"
                                         "void main()\n"
                                         "{\n"
                                         "	outColor=texture(sprite,fragTexcoord);\n"
                                         "}";

    const std::string gizmoVertShader = "#version 330 core\n"
                                        "in vec2 inPosition;\n"
                                        "uniform mat4 modelMat;\n"
                                        "uniform mat4 viewMat;\n"
                                        "uniform mat4 projMat;\n"
                                        "void main()\n"
                                        "{\n"
                                        "	gl_Position=projMat*viewMat*modelMat*vec4(inPosition,0.0,1.0);\n"
                                        "}";

    const std::string gizmoFragShader = "#version 330 core\n"
                                        "out vec4 outColor;\n"
                                        "void main()\n"
                                        "{\n"
                                        "	outColor=vec4(0.0,1.0,0.0,1.0);\n"
                                        "}";

    SpriteMaterial::SpriteMaterial()
    {
        auto vertShader = GL::ShaderModule(GL::VERTEX_SHADER, spriteVertShader);
        auto fragShader = GL::ShaderModule(GL::FRAGMENT_SHADER, spriteFragShader);
        shaderProgram = std::make_unique<GL::ShaderProgram>();
        shaderProgram->AttachShader(vertShader);
        shaderProgram->AttachShader(fragShader);
    }
    SpriteMaterial::~SpriteMaterial()
    {
    }

    void SpriteMaterial::SetSpriteTexture(GL::Texture *sprite)
    {
        spriteTexture=sprite;
    }
}