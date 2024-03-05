#include "ShipShootComponent.h"
#include "LaserMoveComponent.h"
ShipShootComponent::ShipShootComponent()
{
}
ShipShootComponent::~ShipShootComponent()
{
}

void ShipShootComponent::Init()
{
    RequiredComponent<mulberry::TransformComponent>();

   /* mulberry::TextureInfo textureInfo{};
    textureInfo.data = GetSceneAssetManager()->LoadImageData("Assets/Laser.png");
    textureInfo.minFilter = mulberry::FilterMode::LINEAR;
    textureInfo.magFilter = mulberry::FilterMode::LINEAR;
    mLaserTexture.reset(new mulberry::Texture(textureInfo));*/

    if (!mOwnerTransformComponent)
        mOwnerTransformComponent = GetOwner()->GetComponent<mulberry::TransformComponent>();
}

void ShipShootComponent::Update()
{
    float deltaTime = mulberry::App::GetInstance().GetTimer()->GetDeltaTime();

    FlushLasers();

    if (mulberry::App::GetInstance().GetInput()->GetKeyboard()->GetKeyState(mulberry::KeyCode::KEYCODE_SPACE) == mulberry::ButtonState::PRESS)
        GetLaserEntity();
}

mulberry::Entity *ShipShootComponent::GetLaserEntity()
{
    auto slot = FindLaserCacheSlot();
    if (slot == -1)
    {
        auto laser = GetScene()->CreateEntity("Laser");
        auto spriteComp = laser->CreateComponent<mulberry::SpriteComponent>();
        spriteComp->SetSprite(mLaserTexture.get());

        auto transformComp = laser->GetComponent<mulberry::TransformComponent>();
        transformComp->SetPosition(mOwnerTransformComponent->GetPosition());
        transformComp->SetRotation(mOwnerTransformComponent->GetRotation());

        auto laserMoveComp = laser->CreateComponent<LaserMoveComponent>();
        laserMoveComp->SetDir(mOwnerTransformComponent->GetLocalAxisX());

        mLaserCaches.emplace_back(laser, false);

        return laser;
    }
    else
    {
        auto laser = mLaserCaches[slot].laserEntity;
        mLaserCaches[slot].laserUsable = false;

        auto spriteComp = laser->GetComponent<mulberry::SpriteComponent>();
        spriteComp->SetSprite(mLaserTexture.get());

        auto transformComp = laser->GetComponent<mulberry::TransformComponent>();
        transformComp->SetPosition(mOwnerTransformComponent->GetPosition());
        transformComp->SetRotation(mOwnerTransformComponent->GetRotation());

        auto laserMoveComp = laser->GetComponent<LaserMoveComponent>();
        laserMoveComp->SetDir(mOwnerTransformComponent->GetLocalAxisX());

        return laser;
    }
}

int8_t ShipShootComponent::FindLaserCacheSlot()
{
    for (int32_t i = 0; i < mLaserCaches.size(); ++i)
        if (mLaserCaches[i].laserUsable == true)
            return i;
    return -1;
}

void ShipShootComponent::FlushLaserEntity(LaserCache &cache)
{
    if (cache.laserUsable)
        return;

    mCameraComponent = GetOwner()->GetOwner()->GetEntity("Camera")->GetComponent<mulberry::CameraComponent>();
    auto spriteExtent = mLaserTexture->GetExtent();
    auto extent = mCameraComponent->GetExtent();

    mulberry::Vec2 edge = mulberry::Vec2((extent.x + spriteExtent.x) / 2.0f, (extent.y + spriteExtent.y) / 2.0f);

    auto transformComp = cache.laserEntity->GetComponent<mulberry::TransformComponent>();

    if (transformComp->GetPosition().x >= edge.x || transformComp->GetPosition().x <= -edge.x || transformComp->GetPosition().y >= edge.y || transformComp->GetPosition().y <= -edge.y)
        cache.laserUsable = true;
}

void ShipShootComponent::FlushLasers()
{
    for (auto &laserCahce : mLaserCaches)
        FlushLaserEntity(laserCahce);
}