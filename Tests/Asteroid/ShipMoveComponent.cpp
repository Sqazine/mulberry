#include "ShipMoveComponent.h"

ShipMoveComponent::ShipMoveComponent()
{
}
ShipMoveComponent::~ShipMoveComponent()
{
}

void ShipMoveComponent::Init()
{
    RequiredComponent<mulberry::TransformComponent>();

    mulberry::TextureInfo textureInfo{};
    textureInfo.data = GetSceneAssetManager()->LoadImgData("Assets/ShipWithThrust.png");
    textureInfo.minFilter = mulberry::FilterMode::LINEAR;
    textureInfo.magFilter = mulberry::FilterMode::LINEAR;
    movingTexture.reset(new mulberry::Texture(textureInfo));

    textureInfo = {};
    textureInfo.data = GetSceneAssetManager()->LoadImgData("Assets/Ship.png");
    textureInfo.minFilter = mulberry::FilterMode::LINEAR;
    textureInfo.magFilter = mulberry::FilterMode::LINEAR;
    staticTexture.reset(new mulberry::Texture(textureInfo));

    if (!mOwnerSpriteComponent)
        mOwnerSpriteComponent = GetOwner()->GetComponent<mulberry::SpriteComponent>();
    mOwnerSpriteComponent->SetSprite(staticTexture.get());

    if (!mOwnerTransformComponent)
        mOwnerTransformComponent = GetOwner()->GetComponent<mulberry::TransformComponent>();
    mOwnerTransformComponent->SetRotation(90.0f);
    mOwnerTransformComponent->SetPosition(0.0f, (-mulberry::App::GetInstance().GetWindow()->GetSize().y + textureInfo.data.height * mOwnerTransformComponent->GetScale().y) / 2.0f);
}

void ShipMoveComponent::Update()
{
    Move();
}

void ShipMoveComponent::Move()
{
    float deltaTime = mulberry::App::GetInstance().GetTimer()->GetDeltaTime();

    mCameraComponent = GetOwner()->GetOwner()->GetEntity("Camera")->GetComponent<mulberry::CameraComponent>();

    if (mulberry::App::GetInstance().GetWindow()->IsWindowCloseButtonClick())
        mulberry::App::GetInstance().Quit();

    mulberry::Vec2 offset;
    mulberry::Vec2 newPos;

    if (mulberry::App::GetInstance().GetInput()->GetKeyboard()->GetKeyState(mulberry::KeyCode::KEYCODE_W) == mulberry::ButtonState::HOLD)
    {
        offset = mOwnerTransformComponent->GetLocalAxisX() * moveSpeed * deltaTime;
        moveForward = true;
    }
    else
        moveForward = false;

    if (mulberry::App::GetInstance().GetInput()->GetKeyboard()->GetKeyState(mulberry::KEYCODE_S) == mulberry::ButtonState::HOLD)
    {
        offset = -mOwnerTransformComponent->GetLocalAxisX() * moveSpeed * deltaTime;
        moveBackward = true;
    }
    else
        moveBackward = false;

    newPos = mOwnerTransformComponent->GetPosition() + offset;

    auto spriteExtent = mOwnerSpriteComponent->GetSprite()->GetExtent();

    auto extent = mCameraComponent->GetExtent();

    mulberry::Vec2 edge = mulberry::Vec2((extent.x - spriteExtent.x) / 2.0, (extent.y - spriteExtent.y) / 2.0);

    if (newPos.x <= -edge.x)
        newPos.x = -edge.x;

    if (newPos.x >= edge.x)
        newPos.x = edge.x;

    if (newPos.y <= -edge.y)
        newPos.y = -edge.y;

    if (newPos.y >= edge.y)
        newPos.y = edge.y;

    mOwnerTransformComponent->SetPosition(newPos);

    if (mulberry::App::GetInstance().GetInput()->GetKeyboard()->GetKeyState(mulberry::KEYCODE_A) == mulberry::ButtonState::HOLD)
        mOwnerTransformComponent->Rotate(rotSpeed * deltaTime);

    if (mulberry::App::GetInstance().GetInput()->GetKeyboard()->GetKeyState(mulberry::KEYCODE_D) == mulberry::ButtonState::HOLD)
        mOwnerTransformComponent->Rotate(-rotSpeed * deltaTime);

    if (moveForward || moveBackward)
        mOwnerSpriteComponent->SetSprite(movingTexture.get());
    else
        mOwnerSpriteComponent->SetSprite(staticTexture.get());
}