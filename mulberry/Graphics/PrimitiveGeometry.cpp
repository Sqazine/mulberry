#include "PrimitiveGeometry.h"
#include <vector>
#include <iostream>
namespace mulberry
{
    PrimitiveGeometry::PrimitiveGeometry(PrimitiveGeometryType type)
    {
        switch (type)
        {
        case PrimitiveGeometryType::SPRITE:
            CreateSprite();
            break;
        case PrimitiveGeometryType::QUAD:
            CreateQuad();
            break;
        case PrimitiveGeometryType::CIRCLE:
            CreateCircle();
            break;
        case PrimitiveGeometryType::POINT:
            CreatePoint();
            break;
        case PrimitiveGeometryType::LINE:
            CreateLine();
            break;
        default:
            break;
        }
    }

    PrimitiveGeometry::PrimitiveGeometry(const std::vector<Vec2> &pos, const std::vector<Vec2> &texcoord, const std::vector<uint32_t> &indices)
        : mPosition(pos), mTexcoord(texcoord), mIndices(indices)
    {
        mPositionBuffer = std::make_unique<rhi::VertexBuffer>(mPosition);
        mTexcoordBuffer = std::make_unique<rhi::VertexBuffer>(mTexcoord);

        mIndexBuffer = std::make_unique<rhi::IndexBuffer>(mIndices);
    }

    PrimitiveGeometry::PrimitiveGeometry(const PrimitiveGeometry &other)
    {
        *this = other;
    }
    PrimitiveGeometry &PrimitiveGeometry::operator=(const PrimitiveGeometry &other)
    {
        if (this == &other)
            return *this;

        mPosition = other.mPosition;
        mTexcoord = other.mTexcoord;
        mIndices = other.mIndices;

        mPositionBuffer = std::make_unique<rhi::VertexBuffer>();
        mTexcoordBuffer = std::make_unique<rhi::VertexBuffer>();
        mIndexBuffer = std::make_unique<rhi::IndexBuffer>();

        UpdateBuffers();
        return *this;
    }

    PrimitiveGeometry::~PrimitiveGeometry()
    {
    }

    const std::vector<Vec2> &PrimitiveGeometry::GetPosition() const
    {
        return mPosition;
    }

    const std::vector<Vec2> &PrimitiveGeometry::GetTexcoord() const
    {
        return mTexcoord;
    }

    const std::vector<uint32_t> &PrimitiveGeometry::GetIndex() const
    {
        return mIndices;
    }

    const rhi::VertexBuffer *PrimitiveGeometry::GetPositionBuffer() const
    {
        return mPositionBuffer.get();
    }
    const rhi::VertexBuffer *PrimitiveGeometry::GetTexcoordBuffer() const
    {
        return mTexcoordBuffer.get();
    }
    const rhi::IndexBuffer *PrimitiveGeometry::GetIndexBuffer() const
    {
        return mIndexBuffer.get();
    }

    void PrimitiveGeometry::UpdateBuffers()
    {
        if (mPosition.size() > 0)
            mPositionBuffer->Fill(mPosition);
        if (mTexcoord.size() > 0)
            mTexcoordBuffer->Fill(mTexcoord);
        if (mIndices.size() > 0)
            mIndexBuffer->Fill(mIndices);
    }

    void PrimitiveGeometry::CreateSprite()
    {
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

        mPositionBuffer = std::make_unique<rhi::VertexBuffer>(mPosition);
        mTexcoordBuffer = std::make_unique<rhi::VertexBuffer>(mTexcoord);

        mIndices =
            {
                0, 1, 2,
                0, 2, 3};
        mIndexBuffer = std::make_unique<rhi::IndexBuffer>(mIndices);
    }

    void PrimitiveGeometry::CreateQuad()
    {
        mPosition =
            {
                Vec2(-1.0f, 1.0f),
                Vec2(-1.0f, -1.0f),
                Vec2(1.0f, -1.0f),
                Vec2(1.0f, 1.0f),
                Vec2(0.0f, 0.0f),
                Vec2(0.0f, 1.0f),
            };

        mPositionBuffer = std::make_unique<rhi::VertexBuffer>(mPosition);

        mIndices =
            {
                0, 1,
                1, 2,
                2, 3,
                3, 0,
                4, 5};
        mIndexBuffer = std::make_unique<rhi::IndexBuffer>(mIndices);
    }

    void PrimitiveGeometry::CreateCircle()
    {
        for (float i = 0.0f; i <= 360.0f; i += 12.0f)
        {
            Vec2 pos = Vec2::Rotate(Vec2::UNIT_X, math::ToRadian(i));
            mPosition.emplace_back(pos);
        }

        int32_t i = 0;
        for (i = 0; i < mPosition.size(); ++i)
        {
            mIndices.emplace_back(i);
            mIndices.emplace_back(i + 1);
        }

        mPositionBuffer = std::make_unique<rhi::VertexBuffer>(mPosition);
        mIndexBuffer = std::make_unique<rhi::IndexBuffer>(mIndices);
    }

    void PrimitiveGeometry::CreateLine()
    {
        mPosition = {Vec2(-1.0f, 0.0f), Vec2(1.0f, 0.0f)};
        mPositionBuffer = std::make_unique<rhi::VertexBuffer>(mPosition);

        mIndices = {
            0,
            1,
        };
        mIndexBuffer = std::make_unique<rhi::IndexBuffer>(mIndices);
    }

    void PrimitiveGeometry::CreatePoint()
    {
        mPosition = {Vec2(0.0f, 0.0f)};
        mTexcoord = {Vec2(0.0f, 0.0f)};

        mPositionBuffer = std::make_unique<rhi::VertexBuffer>(mPosition);
        mTexcoordBuffer = std::make_unique<rhi::VertexBuffer>(mTexcoord);

        mIndexBuffer = nullptr;
    }
}