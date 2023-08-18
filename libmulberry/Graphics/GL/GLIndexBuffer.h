#pragma once
#include <cstdint>
#include <vector>
#include <string>
#include <glad/glad.h>

namespace mulberry
{
    class GLIndexBuffer
    {
    public:
        GLIndexBuffer();
        template <typename T>
        GLIndexBuffer(const std::vector<T> &input);
        ~GLIndexBuffer();

        template <typename T>
        void Set(const std::vector<T> &input);

        uint32_t Size() const;

        uint32_t GetDataType() const;

        uint32_t GetHandle() const;

    private:
        uint32_t DataTypeMap(std::string_view typeStr);

        uint32_t mIndexBufferID;
        uint32_t mSize;
        uint32_t mDataType;
    };

    template <typename T>
    inline GLIndexBuffer::GLIndexBuffer(const std::vector<T> &input)
    {
        glGenBuffers(1, &mIndexBufferID);
        Set(input);
    }

    template <typename T>
    inline void GLIndexBuffer::Set(const std::vector<T> &input)
    {
        mDataType = DataTypeMap(typeid(T).name());
        mSize = input.size();
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBufferID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, mSize * sizeof(T), input.data(), GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    inline GLIndexBuffer::GLIndexBuffer()
        : mSize(0)
    {
        glGenBuffers(1, &mIndexBufferID);
    }

    inline GLIndexBuffer::~GLIndexBuffer()
    {
        glDeleteBuffers(1, &mIndexBufferID);
    }

    inline uint32_t GLIndexBuffer::Size() const
    {
        return mSize;
    }

    inline uint32_t GLIndexBuffer::GetDataType() const
    {
        return mDataType;
    }

    inline uint32_t GLIndexBuffer::GetHandle() const
    {
        return mIndexBufferID;
    }

    inline uint32_t GLIndexBuffer::DataTypeMap(std::string_view typeStr)
    {
        if (typeStr.compare("uint32_t") == 0 || typeStr.compare("unsigned int") == 0)
            return GL_UNSIGNED_INT;
        else if (typeStr.compare("int32_t") == 0 || typeStr.compare("int") == 0)
            return GL_INT;
        else if (typeStr.compare("uint8_t") == 0 || typeStr.compare("unsigned char") == 0)
            return GL_UNSIGNED_BYTE;
        else if (typeStr.compare("int8_t") == 0 || typeStr.compare("signed char") == 0 || typeStr.compare("char") == 0)
            return GL_BYTE;
        else if (typeStr.compare("int16_t") == 0 || typeStr.compare("short") == 0)
            return GL_SHORT;
        else if (typeStr.compare("uint16_t") == 0 || typeStr.compare("unsigned short") == 0)
            return GL_SHORT;
        else if (typeStr.compare("float") == 0)
            return GL_FLOAT;
        return GL_NONE;
    }
}