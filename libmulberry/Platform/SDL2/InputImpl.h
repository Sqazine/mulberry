#pragma once
#include <vector>
#include <SDL2/SDL.h>
#include <memory>
#include "Vec2.h"
#include "Platform/Input.h"

namespace mulberry
{

    class SDL2Keyboard : public Keyboard
    {
    public:
        SDL2Keyboard();
        ~SDL2Keyboard() override;
        bool GetKeyValue(KeyCode keyCode) const override;
        ButtonState GetKeyState(KeyCode keyCode) const override;

    private:
        friend class SDL2InputImpl;
        const uint8_t *mCurKeyState;
        uint8_t *mPreKeyState;
    };

    class SDL2Mouse : public Mouse
    {
    public:
        SDL2Mouse();
        ~SDL2Mouse() override;
        bool GetButtonValue(int32_t button) const override;
        ButtonState GetButtonState(int32_t button) const override;
        Vec2 GetMousePos() const override;
        Vec2 GetReleativeMove() const override;
        Vec2 GetMouseScrollWheel() const override;

        void SetReleativeMode(bool isActive) override;
        bool IsReleativeMode() const override;

    private:
        friend class SDL2InputImpl;

        bool mIsRelative;
        Vec2 mCurPos;
        Vec2 mPrePos;
        Vec2 mMouseScrollWheel;
        uint32_t mCurButtons;
        uint32_t mPreButtons;
    };

    class SDL2Controller:public Controller
    {
    public:
        SDL2Controller();
        ~SDL2Controller() override;

        bool GetButtonValue(ControllerButton button) const override;

        ButtonState GetButtonState(ControllerButton button) const override;

        float GetLeftTriggerValue() const override;
        float GetRightTriggerValue() const override;

        const Vec2 &GetLeftStickValue() const override;
        const Vec2 &GetRightStickValue() const override;

        bool IsConnected() const override;

    private:
        friend class SDL2InputImpl;
        uint8_t mCurrentButtons[SDL_CONTROLLER_BUTTON_MAX];
        uint8_t mPreviousButtons[SDL_CONTROLLER_BUTTON_MAX];
        bool mIsConnected;

        float mLeftTriggerValue;
        float mRightTriggerValue;

        Vec2 mLeftStickValue;
        Vec2 mRightStickValue;
    };

    class SDL2InputImpl : public Input
    {
    public:
        SDL2InputImpl();
        ~SDL2InputImpl() override;

        void Init() override;
        void PreUpdate() override;
        void PostUpdate() override;
    private:
        void ProcessEvent();

    };
}