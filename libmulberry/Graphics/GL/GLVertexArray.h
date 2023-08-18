#pragma once
#include <cstdint>
#include <glad/glad.h>

namespace mulberry
{

    class GLVertexArray
    {
    public:
        GLVertexArray();
        ~GLVertexArray();
        void SetActive(bool isActive);

    private:
        uint32_t mVertexArrayID;
    };

    inline GLVertexArray::GLVertexArray()
    {
        glGenVertexArrays(1, &mVertexArrayID);
    }

    inline GLVertexArray::~GLVertexArray()
    {
        glDeleteVertexArrays(1,&mVertexArrayID);
    }

    inline void GLVertexArray::SetActive(bool isActive)
    {
        if (isActive)
            glBindVertexArray(mVertexArrayID);
        else
            glBindVertexArray(0);
    }
}