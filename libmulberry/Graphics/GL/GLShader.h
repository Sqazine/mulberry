#pragma once
#include <string>
#include <map>
#include <glad/glad.h>
#include "GLUniform.h"
#include "GLUtils.h"
#include "Vec2.h"
#include "Math/Mat4.h"
#include "GLTexture.h"

namespace mulberry
{
    class GLShaderModule
    {
    public:
        GLShaderModule(enum ShaderType type, std::string_view content);
        ~GLShaderModule();

        const enum ShaderType &Type() const;

    private:
        void VerifyCompile();

        friend class GLShaderProgram;

        uint32_t mShaderID;
        enum ShaderType mType;
    };

    class GLShaderProgram //shader程序体
    {
    public:
        GLShaderProgram();
        GLShaderProgram(const class RasterPipelineConfig &config);
        ~GLShaderProgram();

        void SetActive(bool isActive);

        template <typename T>
        void SetUniformValue(std::string_view name, T value);

        template <typename T>
        void SetUniformArray(std::string_view name, const std::vector<T> &valueArray);

        void SetTexture(std::string_view name,const GLTexture* texture);

        bool AttachShader(const GLShaderModule &shader);

        uint32_t GetAttribute(std::string_view name) const;
        uint32_t GetUniform(std::string_view name) const;

    private:
        void PopulateAttributes();
        void PopulateUniforms();

        std::map<std::string, uint32_t> mActiveAttributes;
        std::map<std::string, uint32_t> mActiveUniforms;

        uint32_t mTextureBindingIdx;

        bool IsValidProgram();
        uint32_t mProgramID;
    };

#define SHADER_PROGRAM_SET_VALUE(type)                                              \
    template <>                                                                     \
    inline void GLShaderProgram::SetUniformValue(std::string_view name, type value) \
    {                                                                               \
        GLUniform<type>::Set(GetUniform(name.data()), value);                       \
    }

#define SHADER_PROGRAM_SET_VALUEARRAY(type)                                                                  \
    template <>                                                                                              \
    inline void GLShaderProgram::SetUniformArray(std::string_view name, const std::vector<type> &valueArray) \
    {                                                                                                        \
        GLUniform<type>::Set(GetUniform(name.data()), valueArray);                                           \
    }

    SHADER_PROGRAM_SET_VALUE(int32_t)
    SHADER_PROGRAM_SET_VALUE(uint32_t)
    SHADER_PROGRAM_SET_VALUE(float)
    SHADER_PROGRAM_SET_VALUE(double)
    SHADER_PROGRAM_SET_VALUE(Vec2)
    SHADER_PROGRAM_SET_VALUE(Mat4)

    SHADER_PROGRAM_SET_VALUEARRAY(int32_t)
    SHADER_PROGRAM_SET_VALUEARRAY(uint32_t)
    SHADER_PROGRAM_SET_VALUEARRAY(float)
    SHADER_PROGRAM_SET_VALUEARRAY(double)
    SHADER_PROGRAM_SET_VALUEARRAY(Vec2)
    SHADER_PROGRAM_SET_VALUEARRAY(Mat4)
}