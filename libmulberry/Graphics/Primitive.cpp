#include "Primitive.h"
#include <vector>
#include <iostream>
namespace mulberry
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

    Primitive::Primitive(const std::vector<Vec2> &pos, const std::vector<Vec2> &texcoord, const std::vector<uint32_t> &indices)
        : mPosition(pos), mTexcoord(texcoord), mIndices(indices)
    {
        mVertexArray = std::make_unique<GL::VertexArray>();
        mVertexArray->SetActive(true);

        mPositionBuffer = std::make_unique<GL::VertexBuffer<Vec2>>(mPosition);
        mTexcoordBuffer = std::make_unique<GL::VertexBuffer<Vec2>>(mTexcoord);

        mIndexBuffer = std::make_unique<GL::IndexBuffer>(mIndices);
    }

    Primitive::Primitive(const Primitive &other)
    {
        *this = other;
    }
    Primitive &Primitive::operator=(const Primitive &other)
    {
        if (this == &other)
            return *this;

        mPosition = other.mPosition;
        mTexcoord = other.mTexcoord;
        mIndices = other.mIndices;

        mVertexArray = std::make_unique<GL::VertexArray>();
        mPositionBuffer = std::make_unique<GL::VertexBuffer<Vec2>>();
        mTexcoordBuffer = std::make_unique<GL::VertexBuffer<Vec2>>();
        mIndexBuffer = std::make_unique<GL::IndexBuffer>();

        UpdateBuffers();
        return *this;
    }

    Primitive::~Primitive()
    {
    }

    const std::vector<Vec2> &Primitive::GetPosition() const
    {
        return mPosition;
    }

    const std::vector<Vec2> &Primitive::GetTexcoord() const
    {
        return mTexcoord;
    }

    const std::vector<uint32_t> &Primitive::GetIndex() const
    {
        return mIndices;
    }

    const GL::VertexArray *Primitive::GetVertexArray() const
    {
        return mVertexArray.get();
    }
    const GL::VertexBuffer<Vec2> *Primitive::GetPositionBuffer() const
    {
        return mPositionBuffer.get();
    }
    const GL::VertexBuffer<Vec2> *Primitive::GetTexcoordBuffer() const
    {
        return mTexcoordBuffer.get();
    }
    const GL::IndexBuffer *Primitive::GetIndexBuffer() const
    {
        return mIndexBuffer.get();
    }

    void Primitive::UpdateBuffers()
    {
        if (mPosition.size() > 0)
            mPositionBuffer->Set(mPosition);
        if (mTexcoord.size() > 0)
            mTexcoordBuffer->Set(mTexcoord);
        if (mIndices.size() > 0)
            mIndexBuffer->Set(mIndices);
    }

    void Primitive::CreateQuad()
    {
        mVertexArray = std::make_unique<GL::VertexArray>();
        mVertexArray->SetActive(true);

        mPosition =
            {
                Vec2(-1.0f, 1.0f),
                Vec2(-1.0f, -1.0f),
                Vec2(1.0f, -1.0f),
                Vec2(1.0f, 1.0f)};

        mTexcoord =
            {
                Vec2(0.0f, 1.0f),
                Vec2(0.0f, 0.0f),
                Vec2(1.0f, 0.0f),
                Vec2(1.0f, 1.0f)};

        mPositionBuffer = std::make_unique<GL::VertexBuffer<Vec2>>(mPosition);
        mTexcoordBuffer = std::make_unique<GL::VertexBuffer<Vec2>>(mTexcoord);

        mIndices =
            {
                0, 1, 2,
                0, 2, 3};
        mIndexBuffer = std::make_unique<GL::IndexBuffer>(mIndices);
    }
    void Primitive::CreateCircle()
    {
        mVertexArray = std::make_unique<GL::VertexArray>();
        mVertexArray->SetActive(true);

        for (float i = 0.0f; i < 360.0f; i += 12.0f)
        {
            Vec2 pos = Vec2::Rotate(Vec2::UNIT_X, MathUtils::ToRadian(i));
            mPosition.emplace_back(pos);
            Vec2 uv = pos * 0.5f + 0.5f;
            mTexcoord.emplace_back(uv);
        }

        mPositionBuffer = std::make_unique<GL::VertexBuffer<Vec2>>(mPosition);
        mTexcoordBuffer = std::make_unique<GL::VertexBuffer<Vec2>>(mTexcoord);
        mIndexBuffer = std::make_unique<GL::IndexBuffer>(mIndices);
    }
    void Primitive::CreateLine()
    {
        mVertexArray = std::make_unique<GL::VertexArray>();
        mVertexArray->SetActive(true);

        mPosition = {Vec2(-1.0f, 0.0f), Vec2(1.0f, 0.0f)};
        mTexcoord = {Vec2(0.0f, 0.5f), Vec2(1.0f, 0.5f)};

        mPositionBuffer = std::make_unique<GL::VertexBuffer<Vec2>>(mPosition);
        mTexcoordBuffer = std::make_unique<GL::VertexBuffer<Vec2>>(mTexcoord);

        mIndices = {
            0,
            1,
        };
        mIndexBuffer = std::make_unique<GL::IndexBuffer>(mIndices);
    }
    void Primitive::CreatePoint()
    {
        mVertexArray = std::make_unique<GL::VertexArray>();
        mVertexArray->SetActive(true);

        mPosition = {Vec2(0.0f, 0.0f)};

        mTexcoord = {Vec2(0.0f, 0.0f)};

        mPositionBuffer = std::make_unique<GL::VertexBuffer<Vec2>>(mPosition);
        mTexcoordBuffer = std::make_unique<GL::VertexBuffer<Vec2>>(mTexcoord);

        mIndices = {0};
        mIndexBuffer = std::make_unique<GL::IndexBuffer>(mIndices);
    }

    void Primitive::Bind(int32_t position, int32_t texcoord)
    {
        mVertexArray->SetActive(true);
        if (position >= 0)
            mPositionBuffer->BindTo(position);
        if (texcoord >= 0)
            mTexcoordBuffer->BindTo(texcoord);
    }
    void Primitive::UnBind(int32_t position, int32_t texcoord)
    {
        if (position >= 0)
            mPositionBuffer->UnBindFrom(position);
        if (texcoord >= 0)
            mTexcoordBuffer->UnBindFrom(texcoord);

        mVertexArray->SetActive(false);
    }
}