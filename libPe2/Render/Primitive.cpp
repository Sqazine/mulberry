#include "Primitive.h"
#include <vector>
#include <iostream>
namespace Pe2
{
    Primitive::Primitive(PrimitiveType type)
    {
        switch (type)
        {
        case PrimitiveType::QUAD:
            CreateQuad();
            break;
        case PrimitiveType::CIRCLE:
            CreateCircle();
            break;
        case PrimitiveType::POINT:
            CreatePoint();
            break;
        case PrimitiveType::LINE:
            CreateLine();
            break;
        default:
            break;
        }
    }

    Primitive::Primitive(const Primitive &other)
    {
        *this = other;
    }
    Primitive &Primitive::operator=(const Primitive &other)
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

    Primitive::~Primitive()
    {
    }

    const std::vector<Vec2> &Primitive::GetPosition() const
    {
        return m_Position;
    }

    const std::vector<Vec2> &Primitive::GetTexcoord() const
    {
        return m_Texcoord;
    }

    const std::vector<uint8_t> &Primitive::GetIndex() const
    {
        return m_Indices;
    }

    const VertexArray *Primitive::GetVertexArray() const
    {
        return m_VertexArray.get();
    }
    const VertexBuffer<Vec2> *Primitive::GetPositionBuffer() const
    {
        return m_PositionBuffer.get();
    }
    const VertexBuffer<Vec2> *Primitive::GetTexcoordBuffer() const
    {
        return m_TexcoordBuffer.get();
    }
    const IndexBuffer *Primitive::GetIndexBuffer() const
    {
        return m_IndexBuffer.get();
    }

    void Primitive::UpdateBuffers()
    {
        if (m_Position.size() > 0)
            m_PositionBuffer->Set(m_Position);
        if (m_Texcoord.size() > 0)
            m_TexcoordBuffer->Set(m_Texcoord);
        if (m_Indices.size() > 0)
            m_IndexBuffer->Set(m_Indices);
    }

    void Primitive::CreateQuad()
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
    void Primitive::CreateCircle()
    {
        m_VertexArray = std::make_unique<VertexArray>();
        m_VertexArray->SetActive(true);

        for (uint32_t i = 0; i < 360; i += 12)
        {
            Vec2 pos = Vec2::Rotate(Vec2::UNITX, MathUtils::ToRadian(i));
            m_Position.emplace_back(pos);
            Vec2 uv = pos * 0.5f + 0.5f;
            m_Texcoord.emplace_back(uv);
        }

        m_PositionBuffer = std::make_unique<VertexBuffer<Vec2>>(m_Position);
        m_TexcoordBuffer = std::make_unique<VertexBuffer<Vec2>>(m_Texcoord);

        m_Indices =
            {
                0, 1, 2,
                0, 2, 3};
        m_IndexBuffer = std::make_unique<IndexBuffer>(m_Indices);
    }
    void Primitive::CreateLine()
    {
        m_VertexArray = std::make_unique<VertexArray>();
        m_VertexArray->SetActive(true);

        m_Position = {Vec2(-1.0f, 0.0f), Vec2(1.0f, 0.0f)};
        m_Texcoord = {Vec2(0.0f, 0.5f), Vec2(1.0f, 0.5f)};

        m_PositionBuffer = std::make_unique<VertexBuffer<Vec2>>(m_Position);
        m_TexcoordBuffer = std::make_unique<VertexBuffer<Vec2>>(m_Texcoord);

        m_Indices = {
            0,
            1,
        };
        m_IndexBuffer = std::make_unique<IndexBuffer>(m_Indices);
    }
    void Primitive::CreatePoint()
    {
        m_VertexArray = std::make_unique<VertexArray>();
        m_VertexArray->SetActive(true);

        m_Position = {Vec2(0.0f, 0.0f)};

        m_Texcoord = {Vec2(0.0f, 0.0f)};

        m_PositionBuffer = std::make_unique<VertexBuffer<Vec2>>(m_Position);
        m_TexcoordBuffer = std::make_unique<VertexBuffer<Vec2>>(m_Texcoord);

        m_Indices = {0};
        m_IndexBuffer = std::make_unique<IndexBuffer>(m_Indices);
    }

    void Primitive::Bind(int position, int texcoord)
    {
        m_VertexArray->SetActive(true);
        if (position >= 0)
            m_PositionBuffer->BindTo(position);
        if (texcoord >= 0)
            m_TexcoordBuffer->BindTo(texcoord);
    }
    void Primitive::UnBind(int position, int texcoord)
    {
        if (position >= 0)
            m_PositionBuffer->UnBindFrom(position);
        if (texcoord >= 0)
            m_TexcoordBuffer->UnBindFrom(texcoord);

        m_VertexArray->SetActive(false);
    }
}