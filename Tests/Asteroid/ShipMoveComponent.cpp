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
    textureInfo.data = GetSceneAssetManager()->LoadImgData(std::string(RESOURCES_DIR) + "ShipWithThrust.png");
    textureInfo.filterMode = mulberry::FilterMode::LINEAR;
    movingTexture.reset(new mulberry::Texture(textureInfo));

    textureInfo = {};
    textureInfo.data = GetSceneAssetManager()->LoadImgData(std::string(RESOURCES_DIR) + "Ship.png");
    textureInfo.filterMode = mulberry::FilterMode::LINEAR;
    staticTexture.reset(new mulberry::Texture(textureInfo));

    if (!ownerSpriteComponent)
        ownerSpriteComponent = GetOwner()->GetComponent<mulberry::SpriteComponent>();

    ownerSpriteComponent->SetSprite(staticTexture.get());

    if (!ownerTransformComponent)
        ownerTransformComponent = GetOwner()->GetComponent<mulberry::TransformComponent>();
    ownerTransformComponent->SetRotation(90.0f);
    ownerTransformComponent->SetPosition(0.0f, (-mulberry::App::GetInstance().GetWindow()->GetSize().y + textureInfo.data.height * ownerTransformComponent->GetScale().y) / 2.0f);
}

void ShipMoveComponent::ProcessInput(const mulberry::InputDevice &inputDevice)
{
    if (inputDevice.keyboard->GetKeyState(mulberry::KeyCode::KEYCODE_W) == mulberry::ButtonState::HOLD)
        moveForward = true;
    else
        moveForward = false;

    if (inputDevice.keyboard->GetKeyState(mulberry::KEYCODE_S) == mulberry::ButtonState::HOLD)
        moveBackward = true;
    else
        moveBackward = false;

    if (inputDevice.keyboard->GetKeyState(mulberry::KEYCODE_A) == mulberry::ButtonState::HOLD)
        rotLeft = true;
    else
        rotLeft = false;

    if (inputDevice.keyboard->GetKeyState(mulberry::KEYCODE_D) == mulberry::ButtonState::HOLD)
        rotRight = true;
    else
        rotRight = false;
}

void ShipMoveComponent::Update(float deltaTime)
{
    if (moveForward)
        ownerTransformComponent->Translate(ownerTransformComponent->GetLocalAxisX() * moveSpeed * deltaTime);
    if (moveBackward)
        ownerTransformComponent->Translate(-ownerTransformComponent->GetLocalAxisX() * moveSpeed * deltaTime);

    if (rotLeft)
        ownerTransformComponent->Rotate(rotSpeed * deltaTime);

    if (rotRight)
        ownerTransformComponent->Rotate(-rotSpeed * deltaTime);

    if (moveForward || moveBackward)
        ownerSpriteComponent->SetSprite(movingTexture.get());
    else
        ownerSpriteComponent->SetSprite(staticTexture.get());
}