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

    Entity *Scene::GetEntity(std::string_view name)
    {
        auto iter = std::find_if(m_Entities.begin(), m_Entities.end(), [=](auto &entity)
                                 { return entity->GetName() == name; });
        if (iter == m_Entities.end())
            return nullptr;
        return iter->get();
    }

    bool Scene::RemoveEntity(std::string_view name)
    {
        auto iter = std::find_if(m_Entities.begin(), m_Entities.end(), [=](auto &entity)
                                 { return entity->GetName() == name; });
        bool exists = iter != m_Entities.end();
        if (exists)
            m_Entities.erase(iter);
        return exists;
    }
    void Scene::RemoveAllEntities()
    {
        std::vector<std::unique_ptr<Entity>>().swap(m_Entities);
    }

    ResourceManager& Scene::GetResourceManager()
    {
        return m_SceneResourceManager;
    }
}