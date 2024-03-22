#pragma once
#include <string>
#include <string_view>
namespace mulberry::IO
{
    std::string LoadText(std::string_view path);
    void WriteText(std::string_view path,std::string_view data);

    void WriteTextAppend(std::string_view path,std::string_view data);
}