#pragma once

namespace mulberry
{
    class NonCopyable
    {
    public:
        NonCopyable() = default;
       virtual ~NonCopyable() = default;

        NonCopyable(const NonCopyable &) = delete;
        const NonCopyable &operator=(const NonCopyable &) = delete;
    };

}