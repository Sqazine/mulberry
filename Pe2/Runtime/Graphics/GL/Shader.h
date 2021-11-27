#pragma once
#include <string>
#include <map>
#include <glad/glad.h>
#include "Uniform.h"
#include "../../Math/Vec2.h"
#include "../../Math/Mat4.h"


namespace Pe2::GL
{
    enum ShaderModuleType
    {
        VERTEX_SHADER = GL_VERTEX_SHADER,
        FRAGMENT_SHADER = GL_FRAGMENT_SHADER,
    };
    class ShaderModule
    {
    public:
        ShaderModule();
        ~ShaderModule();

        bool CompileSource(const ShaderModuleType &type, std::string_view content);
        bool CompileBinary(const ShaderModuleType &type, std::string_view content);

        const ShaderModuleType &Type() const;

    private:
        bool IsCompiled();

        friend class ShaderProgram;

        uint32_t m_ShaderID;
        ShaderModuleType m_Type;
    };

    class ShaderProgram //shader程序体
    {
    public:
        ShaderProgram();
        ~ShaderProgram();

        void SetActive(bool isActive);

        template <typename T>
        void SetUniformValue(std::string_view name, T value);

        template <typename T>
        void SetUniformArray(std::string_view name, const std::vector<T> &valueArray);

        bool AttachShader(const ShaderModule* shader);

        uint32_t GetAttribute(std::string_view name) const;
        uint32_t GetUniform(std::string_view name) const;

    private:
        void PopulateAttributes();
        void PopulateUniforms();

        std::map<std::string, uint32_t> m_ActiveAttributes;
        std::map<std::string, uint32_t> m_ActiveUniforms;

        bool IsValidProgram();
        uint32_t m_ProgramID;
    };

#define SHADER_PROGRAM_SET_VALUE(type)                                            \
    template <>                                                                   \
    inline void ShaderProgram::SetUniformValue(std::string_view name, type value) \
    {                                                                             \
        Uniform<type>::Set(GetUniform(name.data()), value);                       \
    }

#define SHADER_PROGRAM_SET_VALUEARRAY(type)                                                                \
    template <>                                                                                            \
    inline void ShaderProgram::SetUniformArray(std::string_view name, const std::vector<type> &valueArray) \
    {                                                                                                      \
        Uniform<type>::Set(GetUniform(name.data()), valueArray);                                           \
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