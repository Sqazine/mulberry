#pragma once
#include <cstdint>
#include <vector>
#include <string>
#include <glad/glad.h>

namespace Pe2
{

    class IndexBuffer
    {
    public:
        IndexBuffer();
        template <typename T>
        IndexBuffer(const std::vector<T> &input);
        ~IndexBuffer();

        template <typename T>
        void Set(const std::vector<T> &input);

        uint32_t Size() const;

        uint32_t GetDataType() const;

        uint32_t GetID() const;

    private:
        IndexBuffer(const IndexBuffer &) = delete;
        IndexBuffer &operator=(const IndexBuffer &) = delete;

        uint32_t DataTypeMap(std::string_view typeStr);

        uint32_t m_IndexBufferID;
        uint32_t m_Size;
        uint32_t m_DataType;
    };

    template <typename T>
    inline IndexBuffer::IndexBuffer(const std::vector<T> &input)
    {
        glGenBuffers(1, &m_IndexBufferID);
        Set(input);
    }

    template <typename T>
    inline void IndexBuffer::Set(const std::vector<T> &input)
    {
        m_DataType = DataTypeMap(typeid(T).name());
        m_Size = input.size();
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBufferID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Size * sizeof(T), input.data(), GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    inline IndexBuffer::IndexBuffer()
        : m_Size(0)
    {
        glGenBuffers(1, &m_IndexBufferID);
    }

    inline IndexBuffer::~IndexBuffer()
    {
        glDeleteBuffers(1, &m_IndexBufferID);
    }

    inline uint32_t IndexBuffer::Size() const
    {
        return m_Size;
    }

    inline uint32_t IndexBuffer::GetDataType() const
    {
        return m_DataType;
    }

    inline uint32_t IndexBuffer::GetID() const
    {
        return m_IndexBufferID;
    }

    inline uint32_t IndexBuffer::DataTypeMap(std::string_view typeStr)
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