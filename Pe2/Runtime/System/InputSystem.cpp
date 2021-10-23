#include "InputSystem.h"
#include <memory>

KeyboardState::KeyboardState()
{
}
KeyboardState::~KeyboardState()
{
}
bool KeyboardState::GetKeyValue(SDL_Scancode keyCode) const
{
    return m_CurKeyState[keyCode] == 1 ? true : false;
}

ButtonState KeyboardState::GetKeyState(SDL_Scancode keyCode) const
{
    if (m_PreKeyState[keyCode] == 0)
    {
        if (m_CurKeyState[keyCode] == 0)
            return ButtonState::NONE;
        else
            return ButtonState::PRESS;
    }
    else
    {
        if (m_CurKeyState[keyCode] == 0)
            return ButtonState::RELEASE;
        else
            return ButtonState::HOLD;
    }
}

MouseState::MouseState()
    : m_CurPos(Vec2::ZERO), m_PrePos(Vec2::ZERO), m_MouseScrollWheel(Vec2::ZERO), m_CurButtons(0), m_PreButtons(0)
{
}
MouseState::~MouseState()
{
}
bool MouseState::GetButtonValue(int button) const
{
    return (m_CurButtons & SDL_BUTTON(button)) == 1;
}

ButtonState MouseState::GetButtonState(int button) const
{
    if ((m_PreButtons & SDL_BUTTON(button)) == 0)
    {
        if ((m_PreButtons & SDL_BUTTON(button)) == 0)
            return ButtonState::NONE;
        else
            return ButtonState::PRESS;
    }
    else
    {
        if ((m_PreButtons & SDL_BUTTON(button)) == 0)
            return ButtonState::RELEASE;
        else
            return ButtonState::HOLD;
    }
}

Vec2 MouseState::GetMousePos() const
{
    return m_CurPos;
}

Vec2 MouseState::GetReleativeMove() const
{
    return m_CurPos - m_PrePos;
}

Vec2 MouseState::GetMouseScrollWheel() const
{
    return m_MouseScrollWheel;
}

void MouseState::SetReleativeMode(bool isActive)
{
    m_IsRelative = isActive;
    if (isActive)
        SDL_SetRelativeMouseMode(SDL_TRUE);
    else
        SDL_SetRelativeMouseMode(SDL_FALSE);
}

bool MouseState::IsReleativeMode() const
{
    return m_IsRelative;
}

ControllerState::ControllerState()
    : m_IsConnected(false),
      m_LeftStickValue(Vec2::ZERO), m_RightStickValue(Vec2::ZERO),
      m_LeftTriggerValue(0.0f), m_RightTriggerValue(0.0f)
{
}

ControllerState::~ControllerState()
{
}

bool ControllerState::GetButtonValue(SDL_GameControllerButton button) const
{
    return m_CurrentButtons[button];
}

ButtonState ControllerState::GetButtonState(SDL_GameControllerButton button) const
{
    if (m_PreviousButtons[button] == 0)
    {
        if (m_CurrentButtons[button] == 0)
            return ButtonState::NONE;
        else
            return ButtonState::PRESS;
    }
    else
    {
        if (m_CurrentButtons[button] == 0)
            return ButtonState::RELEASE;
        else
            return ButtonState::HOLD;
    }
}

float ControllerState::GetLeftTriggerValue() const
{
    return m_LeftTriggerValue;
}

float ControllerState::GetRightTriggerValue() const
{
    return m_RightTriggerValue;
}

const Vec2 &ControllerState::GetLeftStickValue() const
{
    return m_LeftStickValue;
}

const Vec2 &ControllerState::GetRightStickValue() const
{
    return m_RightStickValue;
}

bool ControllerState::IsConnected() const
{
    return m_IsConnected;
}

InputSystem::InputSystem()
    : m_KeyboardState(std::make_unique<KeyboardState>()), m_MouseState(std::make_unique<MouseState>())
{
    m_KeyboardState->m_CurKeyState = SDL_GetKeyboardState(nullptr);
    m_KeyboardState->m_PreKeyState = new uint8_t[SDL_NUM_SCANCODES];
    memset(m_KeyboardState->m_PreKeyState, 0, SDL_NUM_SCANCODES);
}

InputSystem::~InputSystem()
{
}

void InputSystem::PreUpdate()
{
    memcpy_s(m_KeyboardState->m_PreKeyState, SDL_NUM_SCANCODES, m_KeyboardState->m_CurKeyState, SDL_NUM_SCANCODES);
    m_MouseState->m_PreButtons = m_MouseState->m_CurButtons;
    m_MouseState->m_PrePos = m_MouseState->m_CurPos;
    m_MouseState->m_MouseScrollWheel = Vec2::ZERO;
}

void InputSystem::PostUpdate()
{
    Vec2 p = Vec2::ZERO;
    if (!m_MouseState->m_IsRelative)
        m_MouseState->m_CurButtons = SDL_GetMouseState((int*)(&p.x), (int*)(&p.y));
    else
        m_MouseState->m_CurButtons = SDL_GetRelativeMouseState((int*)(&p.x),(int*)(&p.y));
    m_MouseState->m_CurPos = p;
}

void InputSystem::ProcessInput(SDL_Event event)
{
    switch (event.type)
    {
    case SDL_MOUSEWHEEL:
        m_MouseState->m_MouseScrollWheel = Vec2(event.wheel.x, static_cast<float>(event.wheel.y));
        break;
    default:
        break;
    }
}

const KeyboardState *InputSystem::GetKeyboard() const
{
    return m_KeyboardState.get();
}

const MouseState *InputSystem::GetMouse() const
{
    return m_MouseState.get();
}

const ControllerState *InputSystem::GetControllerState(uint32_t idx) const
{
    if (m_ControllerStates.empty() || idx < 0 || idx >= m_ControllerStates.size())
        return nullptr;
    return m_ControllerStates[idx].get();
}