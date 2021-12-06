#include "Object.h"

namespace Pe2
{
    Object::Object(std::string_view name)
        : m_Name(name)
    {
    }
    Object::~Object()
    {
    }

    void Object::SetName(std::string_view name)
    {
        m_Name = name;
    }
    const std::string &Object::GetName() const
    {
        return m_Name;
    }
}