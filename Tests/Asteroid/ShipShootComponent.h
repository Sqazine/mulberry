#pragma once
#include "mulberry/mulberry.h"
#include <array>
class ShipShootComponent : public mulberry::Component
{
public:
    ShipShootComponent();
    ~ShipShootComponent();

    void Init() override;
    void Update() override;
private:
     mulberry::TransformComponent *mOwnerTransformComponent = nullptr;
       mulberry::CameraComponent *mCameraComponent = nullptr;

    struct LaserCache
    {
        LaserCache(mulberry::Entity *e, bool u) : laserEntity(e), laserUsable(u) {}
        mulberry::Entity *laserEntity{nullptr};
        bool laserUsable{false};
    };

    mulberry::Entity *GetLaserEntity();
    void FlushLasers();

    int8_t FindLaserCacheSlot();

    void FlushLaserEntity(LaserCache& cache);

    std::vector<LaserCache> mLaserCaches;

    std::unique_ptr<mulberry::Texture> mLaserTexture;
};
