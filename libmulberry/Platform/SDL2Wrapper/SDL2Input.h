#pragma once
#include <vector>
#include <SDL2/SDL.h>
#include <memory>
#include "Vec2.h"
#include "Platform/Input.h"
namespace mulberry
{
   
    class SDL2Keyboard
    {
    public:
        SDL2Keyboard();
        ~SDL2Keyboard();
        bool GetKeyValue(KeyCode keyCode) const;
        ButtonState GetKeyState(KeyCode keyCode) const;

    private:
        friend class SDL2Input;
        const uint8_t *mCurKeyState;
        uint8_t *mPreKeyState;
    };

    class SDL2Mouse
    {
    public:
        SDL2Mouse();
        ~SDL2Mouse();
        bool GetButtonValue(int32_t button) const;
        ButtonState GetButtonState(int32_t button) const;
        Vec2 GetMousePos() const;
        Vec2 GetReleativeMove() const;
        Vec2 GetMouseScrollWheel() const;

        void SetReleativeMode(bool isActive);
        bool IsReleativeMode() const;

    private:
        friend class SDL2Input;

        bool mIsRelative;
        Vec2 mCurPos;
        Vec2 mPrePos;
        Vec2 mMouseScrollWheel;
        uint32_t mCurButtons;
        uint32_t mPreButtons;
    };

    class SDL2Controller
    {
    public:
        SDL2Controller();
        ~SDL2Controller();

        bool GetButtonValue(SDL_GameControllerButton button) const;

        ButtonState GetButtonState(SDL_GameControllerButton button) const;

        float GetLeftTriggerValue() const;
        float GetRightTriggerValue() const;

        const Vec2 &GetLeftStickValue() const;
        const Vec2 &GetRightStickValue() const;

        bool IsConnected() const;

    private:
        friend class SDL2Input;
        uint8_t mCurrentButtons[SDL_CONTROLLER_BUTTON_MAX];
        uint8_t mPreviousButtons[SDL_CONTROLLER_BUTTON_MAX];
        bool mIsConnected;

        float mLeftTriggerValue;
        float mRightTriggerValue;

        Vec2 mLeftStickValue;
        Vec2 mRightStickValue;
    };

    class SDL2Input
    {
    public:
        SDL2Input();
        ~SDL2Input();
        const InputDevice *GetDevice();

        void Init();
        void PreUpdate();
        void PostUpdate();
        void ProcessEvent();

        SDL_Event GetCurEvent() const;        

    private:
        SDL_Event mCurEvent;
        std::unique_ptr<InputDevice> mDevice;
    };
}