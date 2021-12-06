#pragma once
#include <vector>
#include <string>
#include <string_view>
#include "Entity.h"
#include "Object.h"
namespace Pe2
{
    class Scene : public Object
    {
    public:
        Scene(std::string_view name);
        ~Scene();

        Entity *CreateEntity(std::string_view name);
        bool RemoveEntity(std::string_view name);
        void RemoveAllEntities();

    private:
        std::vector<std::unique_ptr<Entity>> m_Entities;
    };
}