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
        return mCurKeyState[keyCode] == 1 ? true : false;
    }

    ButtonState Keyboard::GetKeyState(KeyCode keyCode) const
    {
        if (mPreKeyState[keyCode] == 0)
        {
            if (mCurKeyState[keyCode] == 0)
                return ButtonState::NONE;
            else
                return ButtonState::PRESS;
        }
        else
        {
            if (mCurKeyState[keyCode] == 0)
                return ButtonState::RELEASE;
            else
                return ButtonState::HOLD;
        }
    }

    Mouse::Mouse()
        : mCurPos(Vec2::ZERO), mPrePos(Vec2::ZERO), mMouseScrollWheel(Vec2::ZERO), mCurButtons(0), mPreButtons(0)
    {
    }
    Mouse::~Mouse()
    {
    }
    bool Mouse::GetButtonValue(int32_t button) const
    {
        return (mCurButtons & SDL_BUTTON(button)) == 1;
    }

    ButtonState Mouse::GetButtonState(int32_t button) const
    {
        if ((mPreButtons & SDL_BUTTON(button)) == 0)
        {
            if ((mPreButtons & SDL_BUTTON(button)) == 0)
                return ButtonState::NONE;
            else
                return ButtonState::PRESS;
        }
        else
        {
            if ((mPreButtons & SDL_BUTTON(button)) == 0)
                return ButtonState::RELEASE;
            else
                return ButtonState::HOLD;
        }
    }

    Vec2 Mouse::GetMousePos() const
    {
        return mCurPos;
    }

    Vec2 Mouse::GetReleativeMove() const
    {
        return mCurPos - mPrePos;
    }

    Vec2 Mouse::GetMouseScrollWheel() const
    {
        return mMouseScrollWheel;
    }

    void Mouse::SetReleativeMode(bool isActive)
    {
        mIsRelative = isActive;
        if (isActive)
            SDL_SetRelativeMouseMode(SDL_TRUE);
        else
            SDL_SetRelativeMouseMode(SDL_FALSE);
    }

    bool Mouse::IsReleativeMode() const
    {
        return mIsRelative;
    }

    Controller::Controller()
        : mIsConnected(false),
          mLeftStickValue(Vec2::ZERO), mRightStickValue(Vec2::ZERO),
          mLeftTriggerValue(0.0f), mRightTriggerValue(0.0f)
    {
    }

    Controller::~Controller()
    {
    }

    bool Controller::GetButtonValue(SDL_GameControllerButton button) const
    {
        return mCurrentButtons[button];
    }

    ButtonState Controller::GetButtonState(SDL_GameControllerButton button) const
    {
        if (mPreviousButtons[button] == 0)
        {
            if (mCurrentButtons[button] == 0)
                return ButtonState::NONE;
            else
                return ButtonState::PRESS;
        }
        else
        {
            if (mCurrentButtons[button] == 0)
                return ButtonState::RELEASE;
            else
                return ButtonState::HOLD;
        }
    }

    float Controller::GetLeftTriggerValue() const
    {
        return mLeftTriggerValue;
    }

    float Controller::GetRightTriggerValue() const
    {
        return mRightTriggerValue;
    }

    const Vec2 &Controller::GetLeftStickValue() const
    {
        return mLeftStickValue;
    }

    const Vec2 &Controller::GetRightStickValue() const
    {
        return mRightStickValue;
    }

    bool Controller::IsConnected() const
    {
        return mIsConnected;
    }

    Input::Input()
        : mDevice(std::make_unique<InputDevice>())
    {
    }
    Input::~Input()
    {
    }

    const InputDevice *Input::GetDevice()
    {
        return mDevice.get();
    }

    void Input::Init()
    {
        mDevice->keyboard.mCurKeyState = SDL_GetKeyboardState(nullptr);
        mDevice->keyboard.mPreKeyState = new uint8_t[KEYCODE_NUM];
        memset(mDevice->keyboard.mPreKeyState, 0, KEYCODE_NUM);
    }

    void Input::PreUpdate()
    {
        memcpy_s(mDevice->keyboard.mPreKeyState, KEYCODE_NUM, mDevice->keyboard.mCurKeyState, KEYCODE_NUM);
        mDevice->mouse.mPreButtons = mDevice->mouse.mCurButtons;
        mDevice->mouse.mPrePos = mDevice->mouse.mCurPos;
        mDevice->mouse.mMouseScrollWheel = Vec2::ZERO;
    }

    void Input::PostUpdate()
    {
        Vec2 p = Vec2::ZERO;
        if (!mDevice->mouse.mIsRelative)
            mDevice->mouse.mCurButtons = SDL_GetMouseState((int32_t *)(&p.x), (int32_t *)(&p.y));
        else
            mDevice->mouse.mCurButtons = SDL_GetRelativeMouseState((int32_t *)(&p.x), (int32_t *)(&p.y));
        mDevice->mouse.mCurPos = p;
    }

    void Input::ProcessInput(SDL_Event event)
    {
        switch (event.type)
        {
        case SDL_MOUSEWHEEL:
            mDevice->mouse.mMouseScrollWheel = Vec2(event.wheel.x, static_cast<float>(event.wheel.y));
            break;
        default:
            break;
        }
    }
}