#include "Input.h"
#include <memory>
namespace Pe2
{
    Keyboard::Keyboard()
    {
    }
    Keyboard::~Keyboard()
    {
    }
    bool Keyboard::GetKeyValue(KeyCode keyCode) const
    {
        return m_CurKeyState[keyCode] == 1 ? true : false;
    }

    ButtonState Keyboard::GetKeyState(KeyCode keyCode) const
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

    Mouse::Mouse()
        : m_CurPos(Vec2::ZERO), m_PrePos(Vec2::ZERO), m_MouseScrollWheel(Vec2::ZERO), m_CurButtons(0), m_PreButtons(0)
    {
    }
    Mouse::~Mouse()
    {
    }
    bool Mouse::GetButtonValue(int32_t button) const
    {
        return (m_CurButtons & SDL_BUTTON(button)) == 1;
    }

    ButtonState Mouse::GetButtonState(int32_t button) const
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

    Vec2 Mouse::GetMousePos() const
    {
        return m_CurPos;
    }

    Vec2 Mouse::GetReleativeMove() const
    {
        return m_CurPos - m_PrePos;
    }

    Vec2 Mouse::GetMouseScrollWheel() const
    {
        return m_MouseScrollWheel;
    }

    void Mouse::SetReleativeMode(bool isActive)
    {
        m_IsRelative = isActive;
        if (isActive)
            SDL_SetRelativeMouseMode(SDL_TRUE);
        else
            SDL_SetRelativeMouseMode(SDL_FALSE);
    }

    bool Mouse::IsReleativeMode() const
    {
        return m_IsRelative;
    }

    Controller::Controller()
        : m_IsConnected(false),
          m_LeftStickValue(Vec2::ZERO), m_RightStickValue(Vec2::ZERO),
          m_LeftTriggerValue(0.0f), m_RightTriggerValue(0.0f)
    {
    }

    Controller::~Controller()
    {
    }

    bool Controller::GetButtonValue(SDL_GameControllerButton button) const
    {
        return m_CurrentButtons[button];
    }

    ButtonState Controller::GetButtonState(SDL_GameControllerButton button) const
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

    float Controller::GetLeftTriggerValue() const
    {
        return m_LeftTriggerValue;
    }

    float Controller::GetRightTriggerValue() const
    {
        return m_RightTriggerValue;
    }

    const Vec2 &Controller::GetLeftStickValue() const
    {
        return m_LeftStickValue;
    }

    const Vec2 &Controller::GetRightStickValue() const
    {
        return m_RightStickValue;
    }

    bool Controller::IsConnected() const
    {
        return m_IsConnected;
    }

    Input::Input()
        : m_Device(std::make_unique<InputDevice>())
    {
    }
    Input::~Input()
    {
    }

    const InputDevice *Input::GetDevice()
    {
        return m_Device.get();
    }

    void Input::Init()
    {
        m_Device->keyboard.m_CurKeyState = SDL_GetKeyboardState(nullptr);
        m_Device->keyboard.m_PreKeyState = new uint8_t[KEYCODE_NUM];
        memset(m_Device->keyboard.m_PreKeyState, 0, KEYCODE_NUM);
    }

    void Input::PreUpdate()
    {
        memcpy_s(m_Device->keyboard.m_PreKeyState, KEYCODE_NUM, m_Device->keyboard.m_CurKeyState, KEYCODE_NUM);
        m_Device->mouse.m_PreButtons = m_Device->mouse.m_CurButtons;
        m_Device->mouse.m_PrePos = m_Device->mouse.m_CurPos;
        m_Device->mouse.m_MouseScrollWheel = Vec2::ZERO;
    }

    void Input::PostUpdate()
    {
        Vec2 p = Vec2::ZERO;
        if (!m_Device->mouse.m_IsRelative)
            m_Device->mouse.m_CurButtons = SDL_GetMouseState((int32_t *)(&p.x), (int32_t *)(&p.y));
        else
            m_Device->mouse.m_CurButtons = SDL_GetRelativeMouseState((int32_t *)(&p.x), (int32_t *)(&p.y));
        m_Device->mouse.m_CurPos = p;
    }

    void Input::ProcessInput(SDL_Event event)
    {
        switch (event.type)
        {
        case SDL_MOUSEWHEEL:
            m_Device->mouse.m_MouseScrollWheel = Vec2(event.wheel.x, static_cast<float>(event.wheel.y));
            break;
        default:
            break;
        }
    }
}