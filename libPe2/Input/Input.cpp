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

    std::unique_ptr<Keyboard> Input::m_Keyboard = nullptr;
    std::unique_ptr<Mouse> Input::m_Mouse = nullptr;
    std::vector<std::unique_ptr<Controller>> Input::m_Controllers{};

    void Input::Init()
    {
        m_Keyboard = std::make_unique<Keyboard>();
        m_Mouse = std::make_unique<Mouse>();
        m_Keyboard->m_CurKeyState = SDL_GetKeyboardState(nullptr);
        m_Keyboard->m_PreKeyState = new uint8_t[KEYCODE_NUM];
        memset(m_Keyboard->m_PreKeyState, 0, KEYCODE_NUM);
    }

    void Input::PreUpdate()
    {
        memcpy_s(m_Keyboard->m_PreKeyState, KEYCODE_NUM, m_Keyboard->m_CurKeyState, KEYCODE_NUM);
        m_Mouse->m_PreButtons = m_Mouse->m_CurButtons;
        m_Mouse->m_PrePos = m_Mouse->m_CurPos;
        m_Mouse->m_MouseScrollWheel = Vec2::ZERO;
    }

    void Input::PostUpdate()
    {
        Vec2 p = Vec2::ZERO;
        if (!m_Mouse->m_IsRelative)
            m_Mouse->m_CurButtons = SDL_GetMouseState((int32_t *)(&p.x), (int32_t *)(&p.y));
        else
            m_Mouse->m_CurButtons = SDL_GetRelativeMouseState((int32_t *)(&p.x), (int32_t *)(&p.y));
        m_Mouse->m_CurPos = p;
    }

    void Input::ProcessInput(SDL_Event event)
    {
        switch (event.type)
        {
        case SDL_MOUSEWHEEL:
            m_Mouse->m_MouseScrollWheel = Vec2(event.wheel.x, static_cast<float>(event.wheel.y));
            break;
        default:
            break;
        }
    }

    const Keyboard *Input::GetKeyboard()
    {
        return m_Keyboard.get();
    }

    const Mouse *Input::GetMouse()
    {
        return m_Mouse.get();
    }

    const Controller *Input::GetController(uint32_t idx)
    {
        if (m_Controllers.empty() || idx < 0 || idx >= m_Controllers.size())
            return nullptr;
        return m_Controllers[idx].get();
    }
}