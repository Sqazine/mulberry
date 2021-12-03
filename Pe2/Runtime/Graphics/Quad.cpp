#include "Quad.h"
#include <vector>
#include <iostream>
namespace Pe2
{
    Quad::Quad()
    {
        m_VertexArray = std::make_unique<VertexArray>();
        m_VertexArray->SetActive(true);

        m_Position =
            {
                Vec2(-1.0f, 1.0f),
                Vec2(-1.0f, -1.0f),
                Vec2(1.0f, -1.0f),
                Vec2(1.0f, 1.0f)};

        m_Texcoord =
            {
                Vec2(0.0f, 1.0f),
                Vec2(0.0f, 0.0f),
                Vec2(1.0f, 0.0f),
                Vec2(1.0f, 1.0f)};

        m_PositionBuffer = std::make_unique<VertexBuffer<Vec2>>(m_Position);
        m_TexcoordBuffer = std::make_unique<VertexBuffer<Vec2>>(m_Texcoord);

        m_Indices =
            {
                0, 1, 2,
                0, 2, 3};
        m_IndexBuffer = std::make_unique<IndexBuffer>(m_Indices);
    }

    Quad::Quad(const Quad &other)
    {
        *this = other;
    }
    Quad &Quad::operator=(const Quad &other)
    {
        if (this == &other)
            return *this;

        m_Position = other.m_Position;
        m_Texcoord = other.m_Texcoord;
        m_Indices = other.m_Indices;

        m_VertexArray = std::make_unique<VertexArray>();
        m_PositionBuffer = std::make_unique<VertexBuffer<Vec2>>();
        m_TexcoordBuffer = std::make_unique<VertexBuffer<Vec2>>();
        m_IndexBuffer = std::make_unique<IndexBuffer>();

        UpdateBuffers();
        return *this;
    }

    Quad::~Quad()
    {
    }

    const std::vector<Vec2> &Quad::GetPosition() const
    {
        return m_Position;
    }

    const std::vector<Vec2> &Quad::GetTexcoord() const
    {
        return m_Texcoord;
    }

    const std::vector<uint8_t> &Quad::GetIndex() const
    {
        return m_Indices;
    }

    const VertexArray *Quad::GetVertexArray() const
    {
        return m_VertexArray.get();
    }
    const VertexBuffer<Vec2> *Quad::GetPositionBuffer() const
    {
        return m_PositionBuffer.get();
    }
    const VertexBuffer<Vec2> *Quad::GetTexcoordBuffer() const
    {
        return m_TexcoordBuffer.get();
    }
    const IndexBuffer *Quad::GetIndexBuffer() const
    {
        return m_IndexBuffer.get();
    }

    void Quad::UpdateBuffers()
    {
        if (m_Position.size() > 0)
            m_PositionBuffer->Set(m_Position);
        if (m_Texcoord.size() > 0)
            m_TexcoordBuffer->Set(m_Texcoord);
        if (m_Indices.size() > 0)
            m_IndexBuffer->Set(m_Indices);
    }

    void Quad::Bind(int position, int texcoord)
    {
        m_VertexArray->SetActive(true);
        if (position >= 0)
            m_PositionBuffer->BindTo(position);
        if (texcoord >= 0)
            m_TexcoordBuffer->BindTo(texcoord);
    }
    void Quad::UnBind(int position, int texcoord)
    {
        if (position >= 0)
            m_PositionBuffer->UnBindFrom(position);
        if (texcoord >= 0)
            m_TexcoordBuffer->UnBindFrom(texcoord);

        m_VertexArray->SetActive(false);
    }
}