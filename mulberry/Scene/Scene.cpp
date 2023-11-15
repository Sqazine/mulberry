#include "Scene.h"

namespace mulberry
{
    Scene::Scene(std::string_view name)
        : Object(name),mSceneAssetManager(std::make_unique<AssetManager>())
    {
    }
    Scene::~Scene()
    {
    }

    Entity *Scene::CreateEntity(std::string_view name)
    {
        auto entity = std::make_unique<Entity>(name);
        entity->mOwner = this;
        Entity *result = entity.get();
        mEntities.emplace_back(std::move(entity));
        return result;
    }

    Entity *Scene::GetEntity(std::string_view name)
    {
        auto iter = std::find_if(mEntities.begin(), mEntities.end(), [=](auto &entity)
                                 { return entity->GetName() == name; });
        if (iter == mEntities.end())
            return nullptr;
        return iter->get();
    }

    bool Scene::RemoveEntity(std::string_view name)
    {
        auto iter = std::find_if(mEntities.begin(), mEntities.end(), [=](auto &entity)
                                 { return entity->GetName() == name; });
        bool exists = iter != mEntities.end();
        if (exists)
            mEntities.erase(iter);
        return exists;
    }
    void Scene::RemoveAllEntities()
    {
        std::vector<std::unique_ptr<Entity>>().swap(mEntities);
    }

    AssetManager *Scene::GetSceneAssetManager()
    {
        return mSceneAssetManager.get();
    }

    std::vector<Entity *> Scene::GetAllEntities() const
    {
        std::vector<Entity *> result;
        for (const auto &e : mEntities)
            result.emplace_back(e.get());
        return result;
    }
}