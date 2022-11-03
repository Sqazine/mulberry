#include "ShipMoveComponent.h"
COMPONENT_DEFINITION(mulberry::Component, ShipMoveComponent)
ShipMoveComponent::ShipMoveComponent()
{
}
ShipMoveComponent::~ShipMoveComponent()
{
}

void ShipMoveComponent::Init()
{
    REQUIRED_COMPONENT(mulberry::TransformComponent);

    mulberry::GL::TextureInfo textureInfo{};
    textureInfo.data = GetSceneAssetManager()->LoadImgData(std::string(RESOURCES_DIR) + "ShipWithThrust.png");
    textureInfo.filterMode = mulberry::GL::FilterMode::LINEAR;
    movingTexture.reset(new mulberry::GL::Texture(textureInfo));

    textureInfo = {};
    textureInfo.data = GetSceneAssetManager()->LoadImgData(std::string(RESOURCES_DIR) + "Ship.png");
    textureInfo.filterMode = mulberry::GL::FilterMode::LINEAR;
    staticTexture.reset(new mulberry::GL::Texture(textureInfo));

    if (!ownerRenderComponent)
        ownerRenderComponent = GetOwner()->GetComponent<mulberry::RenderComponent>();

    ownerRenderComponent->SetMaterial(new mulberry::SpriteMaterial());
    ((mulberry::SpriteMaterial *)ownerRenderComponent->GetMaterial())->SetSprite(staticTexture.get());

    if (!ownerTransformComponent)
        ownerTransformComponent = GetOwner()->GetComponent<mulberry::TransformComponent>();
    ownerTransformComponent->SetRotation(90.0f);
    ownerTransformComponent->SetPosition(0.0f, (-mulberry::App::GetWindowExtent().y + textureInfo.data.height * ownerTransformComponent->GetScale().y) / 2.0f);
}

void ShipMoveComponent::ProcessInput(const mulberry::InputDevice *inputDevice)
{
    if (inputDevice->keyboard.GetKeyState(mulberry::KEYCODE_W) == mulberry::ButtonState::HOLD)
        moveForward = true;
    else
        moveForward = false;

    if (inputDevice->keyboard.GetKeyState(mulberry::KEYCODE_S) == mulberry::ButtonState::HOLD)
        moveBackward = true;
    else
        moveBackward = false;

    if (inputDevice->keyboard.GetKeyState(mulberry::KEYCODE_A) == mulberry::ButtonState::HOLD)
        rotLeft = true;
    else
        rotLeft = false;

    if (inputDevice->keyboard.GetKeyState(mulberry::KEYCODE_D) == mulberry::ButtonState::HOLD)
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
        ((mulberry::SpriteMaterial *)ownerRenderComponent->GetMaterial())->SetSprite(movingTexture.get());
    else
        ((mulberry::SpriteMaterial *)ownerRenderComponent->GetMaterial())->SetSprite(staticTexture.get());
}