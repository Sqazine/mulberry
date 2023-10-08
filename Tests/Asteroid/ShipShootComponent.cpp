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

    mulberry::TextureInfo textureInfo{};
    textureInfo.data = GetSceneAssetManager()->LoadImgData(std::string(RESOURCES_DIR) + "Laser.png");
    textureInfo.filterMode = mulberry::FilterMode::LINEAR;
    mLaserTexture.reset(new mulberry::Texture(textureInfo));

    if (!mOwnerTransformComponent)
        mOwnerTransformComponent = GetOwner()->GetComponent<mulberry::TransformComponent>();
}

void ShipShootComponent::Update()
{
    float deltaTime = mulberry::App::GetInstance().GetTimer()->GetDeltaTime();

    if (mulberry::App::GetInstance().GetInput()->GetKeyboard()->GetKeyState(mulberry::KeyCode::KEYCODE_SPACE) == mulberry::ButtonState::PRESS)
        GetLaserEntity();
}

void ShipShootComponent::Move()
{
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
        return mLaserCaches[slot].laserEntity;
}

int8_t ShipShootComponent::FindLaserCacheSlot()
{
    for (int32_t i = 0; i < mLaserCaches.size(); ++i)
        if (mLaserCaches[i].laserUsable == true)
            return i;
    return -1;
}

void ShipShootComponent::FlushLasers()
{
}