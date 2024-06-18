#pragma once
#include <cstdint>

#define SAFE_DELETE(x)   \
    do                   \
    {                    \
        if (x)           \
        {                \
            delete x;    \
            x = nullptr; \
        }                \
    } while (0);

namespace mulberry
{
#define ENUM_CLASS_OP(CastName, EnumName, RawEnum)                   \
    inline EnumName operator|(EnumName lhs, EnumName rhs)            \
    {                                                                \
        return static_cast<EnumName>(CastName(lhs) | CastName(rhs)); \
    }                                                                \
    inline EnumName operator&(EnumName lhs, EnumName rhs)            \
    {                                                                \
        return static_cast<EnumName>(CastName(lhs) & CastName(rhs)); \
    }

    uint32_t GetBiggerTwoPower(uint32_t val);
}