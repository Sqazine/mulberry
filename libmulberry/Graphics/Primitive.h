#pragma once
#include <memory>
#include <vector>
#include "Vec2.h"
#include "GL/GLVertexArray.h"
#include "GL/GLVertexBuffer.h"
#include "GL/GLIndexBuffer.h"
namespace mulberry
{
	enum class PrimitiveType
	{
		SPRITE,
		QUAD,
		CIRCLE,
		LINE,
		POINT
	};
	class Primitive
	{
	public:
		Primitive(PrimitiveType type = PrimitiveType::SPRITE);
		Primitive(const std::vector<Vec2> &pos,
				  const std::vector<Vec2> &texcoord,
				  const std::vector<uint32_t> &indices);
		Primitive(const Primitive &other);
		Primitive &operator=(const Primitive &other);
		~Primitive();

		const std::vector<Vec2> &GetPosition() const;
		const std::vector<Vec2> &GetTexcoord() const;
		const std::vector<uint32_t> &GetIndex() const;

		const GLVertexArray *GetVertexArray() const;
		const GLVertexBuffer<Vec2> *GetPositionBuffer() const;
		const GLVertexBuffer<Vec2> *GetTexcoordBuffer() const;
		const GLIndexBuffer *GetIndexBuffer() const;

		void Bind(int32_t position = -1, int32_t texcoord = -1);
		void UnBind(int32_t position = -1, int32_t texcoord = -1);

	protected:
		void UpdateBuffers();
		void CreateSprite();
		void CreateQuad();
		void CreateCircle();
		void CreateLine();
		void CreatePoint();

		std::vector<Vec2> mPosition;
		std::vector<Vec2> mTexcoord;

		std::vector<uint32_t> mIndices;

		std::unique_ptr<GLVertexArray> mVertexArray;
		std::unique_ptr<GLVertexBuffer<Vec2>> mPositionBuffer;
		std::unique_ptr<GLVertexBuffer<Vec2>> mTexcoordBuffer;
		std::unique_ptr<GLIndexBuffer> mIndexBuffer;
	};
}