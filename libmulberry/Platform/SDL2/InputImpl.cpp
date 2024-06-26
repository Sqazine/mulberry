#include "InputImpl.h"
#include <memory>
#include <iostream>
#include "App.h"
#include "Platform/Input.h"
#include "Platform/Window.h"
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

    SDL2InputImpl::SDL2InputImpl()
    {
        mMouse = std::make_unique<SDL2Mouse>();
        mKeyboard = std::make_unique<SDL2Keyboard>();
    }
    SDL2InputImpl::~SDL2InputImpl()
    {
    }

    void SDL2InputImpl::Init()
    {
        ((SDL2Keyboard *)mKeyboard.get())->mCurKeyState = SDL_GetKeyboardState(nullptr);
        ((SDL2Keyboard *)mKeyboard.get())->mPreKeyState = new uint8_t[SDL_NUM_SCANCODES];
        memset(((SDL2Keyboard *)mKeyboard.get())->mPreKeyState, 0, SDL_NUM_SCANCODES);
    }

    void SDL2InputImpl::PreUpdate()
    {
        memcpy_s(((SDL2Keyboard *)mKeyboard.get())->mPreKeyState, SDL_NUM_SCANCODES, ((SDL2Keyboard *)mKeyboard.get())->mCurKeyState, SDL_NUM_SCANCODES);
        ((SDL2Mouse *)mMouse.get())->mPreButtons = ((SDL2Mouse *)mMouse.get())->mCurButtons;
        ((SDL2Mouse *)mMouse.get())->mPrePos = ((SDL2Mouse *)mMouse.get())->mCurPos;
        ((SDL2Mouse *)mMouse.get())->mMouseScrollWheel = Vec2::ZERO;

        ProcessEvent();
    }

    void SDL2InputImpl::PostUpdate()
    {
        Vec2 p = Vec2::ZERO;
        if (!((SDL2Mouse *)mMouse.get())->mIsRelative)
            ((SDL2Mouse *)mMouse.get())->mCurButtons = SDL_GetMouseState((int32_t *)(&p.x), (int32_t *)(&p.y));
        else
            ((SDL2Mouse *)mMouse.get())->mCurButtons = SDL_GetRelativeMouseState((int32_t *)(&p.x), (int32_t *)(&p.y));
        ((SDL2Mouse *)mMouse.get())->mCurPos = p;
    }

    void SDL2InputImpl::ProcessEvent()
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_MOUSEWHEEL:
                ((SDL2Mouse *)mMouse.get())->mMouseScrollWheel = Vec2(event.wheel.x, static_cast<float>(event.wheel.y));
                break;
            case SDL_QUIT:
                App::GetInstance().GetWindow()->SetEvent(Window::Event::CLOSE);
                break;
            case SDL_WINDOWEVENT:
            {
                switch (event.window.event)
                {
                case SDL_WINDOWEVENT_MINIMIZED:
                    App::GetInstance().GetWindow()->SetEvent(Window::Event::MIN);
                    break;
                case SDL_WINDOWEVENT_MAXIMIZED:
                    App::GetInstance().GetWindow()->SetEvent(Window::Event::MAX);
                    break;
                case SDL_WINDOWEVENT_CLOSE:
                    App::GetInstance().GetWindow()->SetEvent(Window::Event::CLOSE);
                    break;
                case SDL_WINDOWEVENT_RESIZED:
                    App::GetInstance().GetWindow()->SetEvent(Window::Event::RESIZE);
                    break;
                case SDL_WINDOWEVENT_RESTORED:
                    App::GetInstance().GetWindow()->SetEvent(Window::Event::RESTORE);
                    break;
                case SDL_WINDOWEVENT_MOVED:
                    App::GetInstance().GetWindow()->SetEvent(Window::Event::MOVE);
                    break;
                case SDL_WINDOWEVENT_ENTER:
                    App::GetInstance().GetWindow()->SetEvent(Window::Event::ENTER);
                    break;
                case SDL_WINDOWEVENT_LEAVE:
                    App::GetInstance().GetWindow()->SetEvent(Window::Event::LEAVE);
                    break;
                default:
                    break;
                }
            }
            default:
                break;
            }
        }
    }
}