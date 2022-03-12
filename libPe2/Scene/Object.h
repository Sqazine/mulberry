#pragma once
#include <string_view>
namespace Pe2
{
    class Object
    {
    public:
        Object(std::string_view name);
        virtual ~Object();

        void SetName(std::string_view name);
        const std::string &GetName() const;

    protected:
        std::string mName;
    };
}