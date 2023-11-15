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

    private:
        friend class GLShaderProgram;
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
}