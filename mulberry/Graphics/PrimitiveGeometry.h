#pragma once
#include <memory>
#include <vector>
#include "Vec2.h"
#include "RHI/Buffer.h"
namespace mulberry
{
	enum class PrimitiveGeometryType
	{
		SPRITE,
		QUAD,
		CIRCLE,
		LINE,
		POINT
	};
	class PrimitiveGeometry
	{
	public:
		PrimitiveGeometry(PrimitiveGeometryType type = PrimitiveGeometryType::SPRITE);
		PrimitiveGeometry(const std::vector<Vec2> &pos,
				  const std::vector<Vec2> &texcoord,
				  const std::vector<uint32_t> &indices);
		PrimitiveGeometry(const PrimitiveGeometry&other);
		PrimitiveGeometry &operator=(const PrimitiveGeometry&other);
		~PrimitiveGeometry();

		const std::vector<Vec2> &GetPosition() const;
		const std::vector<Vec2> &GetTexcoord() const;
		const std::vector<uint32_t> &GetIndex() const;

		const VertexBuffer *GetPositionBuffer() const;
		const VertexBuffer *GetTexcoordBuffer() const;
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

		std::unique_ptr<VertexBuffer> mPositionBuffer;
		std::unique_ptr<VertexBuffer> mTexcoordBuffer;
		std::unique_ptr<IndexBuffer> mIndexBuffer;
	};
}