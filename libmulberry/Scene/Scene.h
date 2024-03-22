#pragma once
#include <vector>
#include <string>
#include <string_view>
#include "Entity.h"
#include "Object.h"
#include "AssetManager.h"
namespace mulberry
{
    class Scene : public Object
    {
    public:
        Scene(std::string_view name);
        ~Scene();

        Entity *CreateEntity(std::string_view name);
        Entity *GetEntity(std::string_view name);
        bool RemoveEntity(std::string_view name);
        void RemoveAllEntities();

        AssetManager *GetSceneAssetManager();

        std::vector<Entity *> GetAllEntities() const;

    private:
        friend class App;
		virtual void Init();
		virtual void Update();
		virtual void Render();
		virtual void RenderGizmo();
		virtual void Destroy();

        friend class SceneRenderer;
        std::vector<std::unique_ptr<Entity>> mEntities;
        std::unique_ptr<AssetManager> mSceneAssetManager;
    };
}