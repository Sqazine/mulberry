#include "ShipMoveComponent.h"
COMPONENT_DEFINITION(Pe2::Component, ShipMoveComponent)
ShipMoveComponent::ShipMoveComponent()
{
}
ShipMoveComponent::~ShipMoveComponent()
{
}

void ShipMoveComponent::Init()
{
    REQUIRED_COMPONENT(Pe2::TransformComponent);

    Pe2::GL::TextureInfo textureInfo{};
    textureInfo.data =  GetSceneAssetManager()->LoadImgData(std::string(RESOURCES_DIR) + "ShipWithThrust.png");
    textureInfo.filterMode = Pe2::GL::FilterMode::LINEAR;
    movingTexture.reset(new Pe2::GL::Texture(textureInfo));

    textureInfo = {};
    textureInfo.data =GetSceneAssetManager()->LoadImgData(std::string(RESOURCES_DIR) + "Ship.png");
    textureInfo.filterMode = Pe2::GL::FilterMode::LINEAR;
    staticTexture.reset(new Pe2::GL::Texture(textureInfo));

    if (!ownerSpriteComponent)
        ownerSpriteComponent = GetOwner()->GetComponent<Pe2::SpriteComponent>();

    ownerSpriteComponent->SetTexture(staticTexture.get());

    if (!ownerTransformComponent)
        ownerTransformComponent = GetOwner()->GetComponent<Pe2::TransformComponent>();
    ownerTransformComponent->SetRotation(90.0f);
    ownerTransformComponent->SetPosition(0.0f, (-Pe2::App::GetWindowExtent().y + textureInfo.data.height * ownerTransformComponent->GetScale().y) / 2.0f);
}

void ShipMoveComponent::ProcessInput(const Pe2::InputDevice *inputDevice)
{
    if (inputDevice->keyboard.GetKeyState(Pe2::KEYCODE_W) == Pe2::ButtonState::HOLD)
        moveForward = true;
    else
        moveForward = false;

    if (inputDevice->keyboard.GetKeyState(Pe2::KEYCODE_S) == Pe2::ButtonState::HOLD)
        moveBackward = true;
    else
        moveBackward = false;

    if (inputDevice->keyboard.GetKeyState(Pe2::KEYCODE_A) == Pe2::ButtonState::HOLD)
        rotLeft = true;
    else
        rotLeft = false;

    if (inputDevice->keyboard.GetKeyState(Pe2::KEYCODE_D) == Pe2::ButtonState::HOLD)
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
        ownerSpriteComponent->SetTexture(movingTexture.get());
    else
        ownerSpriteComponent->SetTexture(staticTexture.get());
}