#include "SDL2Input.h"
#include <memory>
namespace mulberry
{
    SDL2Keyboard::SDL2Keyboard()
    {
    }
    SDL2Keyboard::~SDL2Keyboard()
    {
    }
    bool SDL2Keyboard::GetKeyValue(KeyCode keyCode) const
    {
        return mCurKeyState[keyCode] == 1 ? true : false;
    }

    ButtonState SDL2Keyboard::GetKeyState(KeyCode keyCode) const
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

    SDL2Mouse::SDL2Mouse()
        : mCurPos(Vec2::ZERO), mPrePos(Vec2::ZERO), mMouseScrollWheel(Vec2::ZERO), mCurButtons(0), mPreButtons(0)
    {
    }
    SDL2Mouse::~SDL2Mouse()
    {
    }
    bool SDL2Mouse::GetButtonValue(int32_t button) const
    {
        return (mCurButtons & SDL_BUTTON(button)) == 1;
    }

    ButtonState SDL2Mouse::GetButtonState(int32_t button) const
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

    Vec2 SDL2Mouse::GetMousePos() const
    {
        return mCurPos;
    }

    Vec2 SDL2Mouse::GetReleativeMove() const
    {
        return mCurPos - mPrePos;
    }

    Vec2 SDL2Mouse::GetMouseScrollWheel() const
    {
        return mMouseScrollWheel;
    }

    void SDL2Mouse::SetReleativeMode(bool isActive)
    {
        mIsRelative = isActive;
        if (isActive)
            SDL_SetRelativeMouseMode(SDL_TRUE);
        else
            SDL_SetRelativeMouseMode(SDL_FALSE);
    }

    bool SDL2Mouse::IsReleativeMode() const
    {
        return mIsRelative;
    }

    SDL2Controller::SDL2Controller()
        : mIsConnected(false),
          mLeftStickValue(Vec2::ZERO), mRightStickValue(Vec2::ZERO),
          mLeftTriggerValue(0.0f), mRightTriggerValue(0.0f)
    {
    }

    SDL2Controller::~SDL2Controller()
    {
    }

    bool SDL2Controller::GetButtonValue(SDL_GameControllerButton button) const
    {
        return mCurrentButtons[button];
    }

    ButtonState SDL2Controller::GetButtonState(SDL_GameControllerButton button) const
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

    float SDL2Controller::GetLeftTriggerValue() const
    {
        return mLeftTriggerValue;
    }

    float SDL2Controller::GetRightTriggerValue() const
    {
        return mRightTriggerValue;
    }

    const Vec2 & SDL2Controller::GetLeftStickValue() const
    {
        return mLeftStickValue;
    }

    const Vec2 & SDL2Controller::GetRightStickValue() const
    {
        return mRightStickValue;
    }

    bool SDL2Controller::IsConnected() const
    {
        return mIsConnected;
    }

    SDL2Input::SDL2Input()
        : mDevice(std::make_unique<InputDevice>())
    {
    }
    SDL2Input::~SDL2Input()
    {
    }

    const InputDevice *SDL2Input::GetDevice()
    {
        return mDevice.get();
    }

    void SDL2Input::Init()
    {
        mDevice->keyboard.mCurKeyState = SDL_GetKeyboardState(nullptr);
        mDevice->keyboard.mPreKeyState = new uint8_t[SDL_NUM_SCANCODES];
        memset(mDevice->keyboard.mPreKeyState, 0, SDL_NUM_SCANCODES);
    }

    void SDL2Input::PreUpdate()
    {
        memcpy_s(mDevice->keyboard.mPreKeyState, SDL_NUM_SCANCODES, mDevice->keyboard.mCurKeyState, SDL_NUM_SCANCODES);
        mDevice->mouse.mPreButtons = mDevice->mouse.mCurButtons;
        mDevice->mouse.mPrePos = mDevice->mouse.mCurPos;
        mDevice->mouse.mMouseScrollWheel = Vec2::ZERO;
    }

    void SDL2Input::PostUpdate()
    {
        Vec2 p = Vec2::ZERO;
        if (!mDevice->mouse.mIsRelative)
            mDevice->mouse.mCurButtons = SDL_GetMouseState((int32_t *)(&p.x), (int32_t *)(&p.y));
        else
            mDevice->mouse.mCurButtons = SDL_GetRelativeMouseState((int32_t *)(&p.x), (int32_t *)(&p.y));
        mDevice->mouse.mCurPos = p;
    }

    void SDL2Input::ProcessEvent()
    {
        SDL_PollEvent(&mCurEvent);
        switch (mCurEvent.type)
        {
        case SDL_MOUSEWHEEL:
            mDevice->mouse.mMouseScrollWheel = Vec2(event.wheel.x, static_cast<float>(event.wheel.y));
            break;
        default:
            break;
        }
    }

    SDL_Event SDL2Input::GetCurEvent() const
    {
        return mCurEvent;
    }
}