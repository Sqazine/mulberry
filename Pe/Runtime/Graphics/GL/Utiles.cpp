#include "Utils.h"
#include <glad/glad.h>
namespace Pe2::GL
{
    uint32_t DataStrToGLDataType(std::string_view dataStr)
    {
        if (dataStr.compare("uint32_t") == 0 || dataStr.compare("unsigned int") == 0)
            return GL_UNSIGNED_INT;
        else if (dataStr.compare("int32_t") == 0 || dataStr.compare("int") == 0)
            return GL_INT;
        else if (dataStr.compare("uint8_t") == 0 || dataStr.compare("unsigned char") == 0)
            return GL_UNSIGNED_BYTE;
        else if (dataStr.compare("int8_t") == 0 || dataStr.compare("signed char") == 0 || dataStr.compare("char") == 0)
            return GL_BYTE;
        else if (dataStr.compare("int16_t") == 0 || dataStr.compare("short") == 0)
            return GL_SHORT;
        else if (dataStr.compare("uint16_t") == 0 || dataStr.compare("unsigned short") == 0)
            return GL_SHORT;
        else if (dataStr.compare("float") == 0)
            return GL_FLOAT;
        return GL_NONE;
    }
}