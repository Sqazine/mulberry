#pragma once
#include <cstdint>
#include <vector>
#include <glad/glad.h>
#include "Vec2.h"
#include "Core/NonCopyable.h"
namespace mulberry
{
	template <typename T>
	class GLVertexBuffer : public NonCopyable
	{
	public:
		GLVertexBuffer();
		GLVertexBuffer(const std::vector<T> &inputArray);
		~GLVertexBuffer();

		void Set(const std::vector<T> &inputArray);

		uint32_t Size();

	protected:
		friend class GLShaderProgram;
		uint32_t mVertexBufferID;
		uint32_t mSize;

	private:
		friend class GLShaderProgram;
		void SetAttribPointer(uint32_t slot) const;
	};

	template <typename T>
	inline GLVertexBuffer<T>::GLVertexBuffer()
	{
		glGenBuffers(1, &mVertexBufferID);
		mSize = 0;
	}
	template <typename T>
	inline GLVertexBuffer<T>::GLVertexBuffer(const std::vector<T> &inputArray)
	{
		glGenBuffers(1, &mVertexBufferID);
		Set(inputArray);
	}

	template <typename T>
	inline GLVertexBuffer<T>::~GLVertexBuffer()
	{
		glDeleteBuffers(1, &mVertexBufferID);
	}

	template <typename T>
	inline void GLVertexBuffer<T>::Set(const std::vector<T> &inputArray)
	{
		mSize = inputArray.size();
		glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferID);
		glBufferData(GL_ARRAY_BUFFER, mSize * sizeof(T), inputArray.data(), GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	template <>
	inline void GLVertexBuffer<int32_t>::SetAttribPointer(uint32_t slot) const
	{
		glVertexAttribIPointer(slot, 1, GL_INT, GL_FALSE, reinterpret_cast<void *>(0));
	}

	template <>
	inline void GLVertexBuffer<float>::SetAttribPointer(uint32_t slot) const
	{
		glVertexAttribPointer(slot, 1, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<void *>(0));
	}

	template <>
	inline void GLVertexBuffer<Vec2>::SetAttribPointer(uint32_t slot) const
	{
		glVertexAttribPointer(slot, 2, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<void *>(0));
	}

	template <typename T>
	inline uint32_t GLVertexBuffer<T>::Size()
	{
		return mSize;
	}

}