#pragma once
#include <vector>
#include <string>
#include <string_view>
#include "Entity.h"
namespace Pe2
{
    class Scene
    {
    public:
        Scene(std::string_view name);
        ~Scene();

        const Entity *CreateEmptyEntity(std::string_view name);
        bool RemoveEntity(std::string_view name);
        void ClearEntity();

        
    private:
        std::string m_Name;
        std::vector<std::unique_ptr<Entity>> m_Entities;
    };
}