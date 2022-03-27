#include "Object.h"

namespace mulberry
{
    Object::Object(std::string_view name)
        : mName(name)
    {
    }
    Object::~Object()
    {
    }

    void Object::SetName(std::string_view name)
    {
        mName = name;
    }
    const std::string &Object::GetName() const
    {
        return mName;
    }
}