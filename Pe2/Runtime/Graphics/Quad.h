#pragma once
#include <memory>
#include <vector>
#include "../Math/Vec2.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
namespace Pe2
{
	class Quad
	{
	public:
		Quad();
		Quad(const Quad &other);
		Quad &operator=(const Quad &other);
		~Quad();

		const std::vector<Vec2> &GetPosition() const;
		const std::vector<Vec2> &GetTexcoord() const;
		const std::vector<uint8_t> &GetIndex() const;

		const VertexArray* GetVertexArray() const;
		const VertexBuffer<Vec2>* GetPositionBuffer() const;
		const VertexBuffer<Vec2>* GetTexcoordBuffer() const;
		const IndexBuffer* GetIndexBuffer() const;

		void Bind(int position = -1, int texcoord = -1);
		void UnBind(int position = -1, int texcoord = -1);

	protected:
		void UpdateBuffers();

		std::vector<Vec2> m_Position;
		std::vector<Vec2> m_Texcoord;

		std::vector<uint8_t> m_Indices;

		std::unique_ptr<VertexArray> m_VertexArray;
		std::unique_ptr<VertexBuffer<Vec2>> m_PositionBuffer;
		std::unique_ptr<VertexBuffer<Vec2>> m_TexcoordBuffer;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
	};
}