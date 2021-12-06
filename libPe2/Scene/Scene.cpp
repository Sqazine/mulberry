#include "Scene.h"

namespace Pe2
{
    Scene::Scene(std::string_view name)
        : Object(name)
    {
    }
    Scene::~Scene()
    {
    }

    Entity *Scene::CreateEntity(std::string_view name)
    {
        auto entity = std::make_unique<Entity>(name);
        Entity *result = entity.get();
        m_Entities.emplace_back(std::move(entity));
        return result;
    }
    bool Scene::RemoveEntity(std::string_view name)
    {
    }
    void Scene::RemoveAllEntities()
    {
    }
}