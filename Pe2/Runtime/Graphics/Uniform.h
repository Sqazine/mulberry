#pragma once
#include <cstdint>
#include <glad/glad.h>
#include <vector>
#include "../Math/Vec2.h"
#include "../Math/Mat4.h"

namespace Pe2
{

	template <typename T>
	class Uniform
	{
	public:
		inline static void Set(uint32_t slot, const std::vector<T> &valueArray);
		inline static void Set(uint32_t slot, const T &value);

	private:
		inline static void SetValue(uint32_t slot, T *valueArray, uint32_t arrayLength);
		Uniform() {}
		Uniform(const Uniform &) = delete;
		Uniform &operator=(const Uniform &) = delete;
		~Uniform() {}
	};

#define UNIFORM_ARRAY_IMPL(gl_func, tType, dType)                                                \
	template <>                                                                                  \
	inline void Uniform<tType>::SetValue(uint32_t slot, tType *valueArray, uint32_t arrayLength) \
	{                                                                                            \
		gl_func(slot, (GLsizei)arrayLength, reinterpret_cast<dType *>(&valueArray[0]));          \
	}

#define UNIFORM_MATRIX_ARRAY_IMPL(gl_func, tType, dType)                                          \
	template <>                                                                                   \
	inline void Uniform<tType>::SetValue(uint32_t slot, tType *valueArray, uint32_t arrayLength)  \
	{                                                                                             \
		gl_func(slot, (GLsizei)arrayLength, GL_FALSE, reinterpret_cast<dType *>(&valueArray[0])); \
	}

	UNIFORM_ARRAY_IMPL(glUniform1iv, int32_t, int32_t)
	UNIFORM_ARRAY_IMPL(glUniform1uiv, uint32_t, uint32_t)
	UNIFORM_ARRAY_IMPL(glUniform1fv, float, float)
	UNIFORM_ARRAY_IMPL(glUniform1dv, double, double)

	UNIFORM_ARRAY_IMPL(glUniform2fv, Vec2, float)
	UNIFORM_MATRIX_ARRAY_IMPL(glUniformMatrix4fv, Mat4, float)

	template <typename T>
	inline void Uniform<T>::Set(uint32_t slot, const std::vector<T> &valueArray)
	{
		SetValue(slot, (T *)&valueArray[0], static_cast<uint32_t>(valueArray.size()));
	}

	template <typename T>
	inline void Uniform<T>::Set(uint32_t slot, const T &value)
	{
		SetValue(slot, (T *)&value, 1);
	}
}