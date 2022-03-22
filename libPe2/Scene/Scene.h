#pragma once
#include <vector>
#include <string>
#include <string_view>
#include "Entity.h"
#include "Object.h"
#include "../ResourceManager.h"
namespace Pe2
{
    class Scene : public Object
    {
    public:
        Scene(std::string_view name);
        ~Scene();

        Entity *CreateEntity(std::string_view name);
        Entity* GetEntity(std::string_view name);
        bool RemoveEntity(std::string_view name);
        void RemoveAllEntities();

        ResourceManager& GetResourceManager();

        std::vector<Entity*> GetAllEntities() const;
    private:
        friend class SceneRenderer;
        std::vector<std::unique_ptr<Entity>> mEntities;
        ResourceManager mSceneResourceManager;
    };
}