#include "IO.h"
#include "Core/Logger.h"
#include <fstream>
namespace mulberry::IO
{
    std::string LoadText(std::string_view path)
    {
        std::ifstream file(path.data(), std::ios::in);
        if (!file.is_open())
        {
            MULBERRY_CORE_ERROR("failed to load text:{}\n");
            exit(1);
        }
        std::stringstream sstream;
        sstream << file.rdbuf();
        std::string content = sstream.str();
        file.close();

        return content;
    }

    void WriteText(std::string_view path, std::string_view data)
    {
        std::ofstream file(path.data(), std::ios::out | std::ios::trunc);
        if (!file.is_open())
        {
            MULBERRY_CORE_ERROR("failed to write text:{}\n");
            exit(1);
        }

        file.write(data.data(), sizeof(char) * data.size());
        file.close();
    }

    void WriteTextAppend(std::string_view path, std::string_view data)
    {
        std::ofstream file(path.data(), std::ios::out | std::ios::app);
        if (!file.is_open())
        {
            MULBERRY_CORE_ERROR("failed to write text:{}\n");
            exit(1);
        }

        file.write(data.data(), sizeof(char) * data.size());
        file.close();
    }
}