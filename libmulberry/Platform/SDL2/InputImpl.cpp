#include "InputImpl.h"
#include <memory>
#include "Platform/Input.h"
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
        return mCurKeyState[(uint8_t)keyCode] == 1 ? true : false;
    }

    ButtonState SDL2Keyboard::GetKeyState(KeyCode keyCode) const
    {
        if (mPreKeyState[(uint8_t)keyCode] == 0)
        {
            if (mCurKeyState[(uint8_t)keyCode] == 0)
                return ButtonState::NONE;
            else
                return ButtonState::PRESS;
        }
        else
        {
            if (mCurKeyState[(uint8_t)keyCode] == 0)
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

    bool SDL2Controller::GetButtonValue(ControllerButton button) const
    {
        return mCurrentButtons[button];
    }

    ButtonState SDL2Controller::GetButtonState(ControllerButton button) const
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

    const Vec2 &SDL2Controller::GetLeftStickValue() const
    {
        return mLeftStickValue;
    }

    const Vec2 &SDL2Controller::GetRightStickValue() const
    {
        return mRightStickValue;
    }

    bool SDL2Controller::IsConnected() const
    {
        return mIsConnected;
    }

    InputImpl::InputImpl() 
    : mIsWindowCLoseButtonClick(false)
    {
        mDevice.mouse = std::make_unique<SDL2Mouse>();
        mDevice.keyboard = std::make_unique<SDL2Keyboard>();
    }
    InputImpl::~InputImpl()
    {
    }

    void InputImpl::Init()
    {
        ((SDL2Keyboard *)mDevice.keyboard.get())->mCurKeyState = SDL_GetKeyboardState(nullptr);
        ((SDL2Keyboard *)mDevice.keyboard.get())->mPreKeyState = new uint8_t[SDL_NUM_SCANCODES];
        memset(((SDL2Keyboard *)mDevice.keyboard.get())->mPreKeyState, 0, SDL_NUM_SCANCODES);
    }

    void InputImpl::PreUpdate()
    {
        memcpy_s(((SDL2Keyboard *)mDevice.keyboard.get())->mPreKeyState, SDL_NUM_SCANCODES, ((SDL2Keyboard *)mDevice.keyboard.get())->mCurKeyState, SDL_NUM_SCANCODES);
        ((SDL2Mouse *)mDevice.mouse.get())->mPreButtons = ((SDL2Mouse *)mDevice.mouse.get())->mCurButtons;
        ((SDL2Mouse *)mDevice.mouse.get())->mPrePos = ((SDL2Mouse *)mDevice.mouse.get())->mCurPos;
        ((SDL2Mouse *)mDevice.mouse.get())->mMouseScrollWheel = Vec2::ZERO;
    }

    void InputImpl::PostUpdate()
    {
        Vec2 p = Vec2::ZERO;
        if (!((SDL2Mouse *)mDevice.mouse.get())->mIsRelative)
            ((SDL2Mouse *)mDevice.mouse.get())->mCurButtons = SDL_GetMouseState((int32_t *)(&p.x), (int32_t *)(&p.y));
        else
            ((SDL2Mouse *)mDevice.mouse.get())->mCurButtons = SDL_GetRelativeMouseState((int32_t *)(&p.x), (int32_t *)(&p.y));
        ((SDL2Mouse *)mDevice.mouse.get())->mCurPos = p;

        ProcessEvent();
    }

    void InputImpl::ProcessEvent()
    {
        SDL_Event event;
        SDL_PollEvent(&event);
        switch (event.type)
        {
        case SDL_MOUSEWHEEL:
            ((SDL2Mouse *)mDevice.mouse.get())->mMouseScrollWheel = Vec2(event.wheel.x, static_cast<float>(event.wheel.y));
            break;
        case SDL_QUIT:
            mIsWindowCLoseButtonClick = true;
            break;
        default:
            break;
        }
    }

    bool InputImpl::IsWindowCloseButtonClick()
    {
        return mIsWindowCLoseButtonClick;
    }
}