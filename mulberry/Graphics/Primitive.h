#pragma once
#include <memory>
#include <vector>
#include "Vec2.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
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

		const VertexArray *GetVertexArray() const;
		const VertexBuffer<Vec2> *GetPositionBuffer() const;
		const VertexBuffer<Vec2> *GetTexcoordBuffer() const;
		const IndexBuffer *GetIndexBuffer() const;

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

		std::unique_ptr<VertexArray> mVertexArray;
		std::unique_ptr<VertexBuffer<Vec2>> mPositionBuffer;
		std::unique_ptr<VertexBuffer<Vec2>> mTexcoordBuffer;
		std::unique_ptr<IndexBuffer> mIndexBuffer;
	};
}