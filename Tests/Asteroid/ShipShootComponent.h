#pragma once
#include "libmulberry/libmulberry.h"
#include <array>
class ShipShootComponent : public mulberry::Component
{
public:
    ShipShootComponent();
    ~ShipShootComponent();

    void Init() override;
    void Update() override;

    void Move();

private:
     mulberry::TransformComponent *mOwnerTransformComponent = nullptr;

    mulberry::Entity *GetLaserEntity();
    void FlushLasers();

    int8_t FindLaserCacheSlot();

    std::unique_ptr<mulberry::Texture> mLaserTexture;

    struct LaserCache
    {
        LaserCache(mulberry::Entity *e, bool u) : laserEntity(e), laserUsable(u) {}
        mulberry::Entity *laserEntity{nullptr};
        bool laserUsable{false};
    };

    std::vector<LaserCache> mLaserCaches;

    float moveSpeed = 500;
};
