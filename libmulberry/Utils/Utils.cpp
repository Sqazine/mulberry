#include "Utils.h"

namespace mulberry
{
    uint32_t GetBiggerTwoPower(uint32_t val)
    {
        if (val & (val - 1))
        {
            val |= val >> 1;
            val |= val >> 2;
            val |= val >> 4;
            val |= val >> 8;
            val |= val >> 16;
            return val + 1;
        }
        else
            return val == 0 ? 1 : val;
    }
}