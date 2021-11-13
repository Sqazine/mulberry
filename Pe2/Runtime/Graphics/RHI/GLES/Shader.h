#pragma once
#include <string>
#include <map>
#include <glad/glad.h>
#include "Uniform.h"
#include "Math/Vector2.h"
#include "Math/Vector3.h"
#include "Math/Vector4.h"
#include "Math/Matrix2.h"
#include "Math/Matrix3.h"
#include "Math/Matrix4.h"
#include "Math/Quaternion.h"
#include "Math/DualQuaternion.h"

namespace GL
{
    enum ShaderModuleType
    {
        VERTEX_SHADER = GL_VERTEX_SHADER,
        FRAGMENT_SHADER = GL_FRAGMENT_SHADER,
        GEOMETRY_SHADER = GL_GEOMETRY_SHADER,
        TESSELLATION_CONTROL_SHADER = GL_TESS_CONTROL_SHADER,
        TESSELLATION_EVAL_SHADER = GL_TESS_EVALUATION_SHADER,
        COMPUTE_SHADER = GL_COMPUTE_SHADER,
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

        bool AttachShader(const std::shared_ptr<ShaderModule> &shader);

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

    SHADER_PROGRAM_SET_VALUE(Vector2i32)
    SHADER_PROGRAM_SET_VALUE(Vector2u32)
    SHADER_PROGRAM_SET_VALUE(Vector2f)
    SHADER_PROGRAM_SET_VALUE(Vector2d)

    SHADER_PROGRAM_SET_VALUE(Vector3i32)
    SHADER_PROGRAM_SET_VALUE(Vector3u32)
    SHADER_PROGRAM_SET_VALUE(Vector3f)
    SHADER_PROGRAM_SET_VALUE(Vector3d)

    SHADER_PROGRAM_SET_VALUE(Vector4i32)
    SHADER_PROGRAM_SET_VALUE(Vector4u32)
    SHADER_PROGRAM_SET_VALUE(Vector4f)
    SHADER_PROGRAM_SET_VALUE(Vector4d)

    SHADER_PROGRAM_SET_VALUE(Quaternioni32)
    SHADER_PROGRAM_SET_VALUE(Quaternionu32)
    SHADER_PROGRAM_SET_VALUE(Quaternionf)
    SHADER_PROGRAM_SET_VALUE(Quaterniond)

    SHADER_PROGRAM_SET_VALUE(DualQuaternioni32)
    SHADER_PROGRAM_SET_VALUE(DualQuaternionu32)
    SHADER_PROGRAM_SET_VALUE(DualQuaternionf)
    SHADER_PROGRAM_SET_VALUE(DualQuaterniond)

    SHADER_PROGRAM_SET_VALUE(Matrix2i32)
    SHADER_PROGRAM_SET_VALUE(Matrix2u32)
    SHADER_PROGRAM_SET_VALUE(Matrix2f)
    SHADER_PROGRAM_SET_VALUE(Matrix2d)

    SHADER_PROGRAM_SET_VALUE(Matrix3i32)
    SHADER_PROGRAM_SET_VALUE(Matrix3u32)
    SHADER_PROGRAM_SET_VALUE(Matrix3f)
    SHADER_PROGRAM_SET_VALUE(Matrix3d)

    SHADER_PROGRAM_SET_VALUE(Matrix4i32)
    SHADER_PROGRAM_SET_VALUE(Matrix4u32)
    SHADER_PROGRAM_SET_VALUE(Matrix4f)
    SHADER_PROGRAM_SET_VALUE(Matrix4d)

    SHADER_PROGRAM_SET_VALUEARRAY(int32_t)
    SHADER_PROGRAM_SET_VALUEARRAY(uint32_t)
    SHADER_PROGRAM_SET_VALUEARRAY(float)
    SHADER_PROGRAM_SET_VALUEARRAY(double)

    SHADER_PROGRAM_SET_VALUEARRAY(Vector2i32)
    SHADER_PROGRAM_SET_VALUEARRAY(Vector2u32)
    SHADER_PROGRAM_SET_VALUEARRAY(Vector2f)
    SHADER_PROGRAM_SET_VALUEARRAY(Vector2d)

    SHADER_PROGRAM_SET_VALUEARRAY(Vector3i32)
    SHADER_PROGRAM_SET_VALUEARRAY(Vector3u32)
    SHADER_PROGRAM_SET_VALUEARRAY(Vector3f)
    SHADER_PROGRAM_SET_VALUEARRAY(Vector3d)

    SHADER_PROGRAM_SET_VALUEARRAY(Vector4i32)
    SHADER_PROGRAM_SET_VALUEARRAY(Vector4u32)
    SHADER_PROGRAM_SET_VALUEARRAY(Vector4f)
    SHADER_PROGRAM_SET_VALUEARRAY(Vector4d)

    SHADER_PROGRAM_SET_VALUEARRAY(Quaternioni32)
    SHADER_PROGRAM_SET_VALUEARRAY(Quaternionu32)
    SHADER_PROGRAM_SET_VALUEARRAY(Quaternionf)
    SHADER_PROGRAM_SET_VALUEARRAY(Quaterniond)

    SHADER_PROGRAM_SET_VALUEARRAY(DualQuaternioni32)
    SHADER_PROGRAM_SET_VALUEARRAY(DualQuaternionu32)
    SHADER_PROGRAM_SET_VALUEARRAY(DualQuaternionf)
    SHADER_PROGRAM_SET_VALUEARRAY(DualQuaterniond)

    SHADER_PROGRAM_SET_VALUEARRAY(Matrix2i32)
    SHADER_PROGRAM_SET_VALUEARRAY(Matrix2u32)
    SHADER_PROGRAM_SET_VALUEARRAY(Matrix2f)
    SHADER_PROGRAM_SET_VALUEARRAY(Matrix2d)

    SHADER_PROGRAM_SET_VALUEARRAY(Matrix3i32)
    SHADER_PROGRAM_SET_VALUEARRAY(Matrix3u32)
    SHADER_PROGRAM_SET_VALUEARRAY(Matrix3f)
    SHADER_PROGRAM_SET_VALUEARRAY(Matrix3d)

    SHADER_PROGRAM_SET_VALUEARRAY(Matrix4i32)
    SHADER_PROGRAM_SET_VALUEARRAY(Matrix4u32)
    SHADER_PROGRAM_SET_VALUEARRAY(Matrix4f)
    SHADER_PROGRAM_SET_VALUEARRAY(Matrix4d)
}