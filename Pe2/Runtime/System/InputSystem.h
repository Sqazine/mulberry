#pragma once
#include <vector>
#include <SDL2/SDL.h>
#include <memory>
#include "Math/Vec2.h"

enum class ButtonState
{
    NONE,
    PRESS,
    RELEASE,
    HOLD
};

class KeyboardState
{
public:
    KeyboardState();
    ~KeyboardState();
    bool GetKeyValue(SDL_Scancode keyCode) const;
    ButtonState GetKeyState(SDL_Scancode keyCode) const;

private:
    friend class InputSystem;
    const uint8_t *m_CurKeyState;
    uint8_t *m_PreKeyState;
};

class MouseState
{
public:
    MouseState();
    ~MouseState();
    bool GetButtonValue(int button) const;
    ButtonState GetButtonState(int button) const;
    Vec2 GetMousePos() const;
    Vec2 GetReleativeMove() const;
    Vec2 GetMouseScrollWheel() const;

    void SetReleativeMode(bool isActive);
    bool IsReleativeMode() const;

private:
    friend class InputSystem;
    bool m_IsRelative;
    Vec2 m_CurPos;
    Vec2 m_PrePos;
    Vec2 m_MouseScrollWheel;
    uint32_t m_CurButtons;
    uint32_t m_PreButtons;
};

class ControllerState
{
public:
    ControllerState();
    ~ControllerState();


    bool GetButtonValue(SDL_GameControllerButton button) const;

    enum class ButtonState GetButtonState(SDL_GameControllerButton button) const;

    float GetLeftTriggerValue() const;
    float GetRightTriggerValue() const;

    const  Vec2 &GetLeftStickValue() const;
    const  Vec2 &GetRightStickValue() const;

    bool IsConnected() const;

private:
    friend class InputSystem;
    uint8_t m_CurrentButtons[SDL_CONTROLLER_BUTTON_MAX];
    uint8_t m_PreviousButtons[SDL_CONTROLLER_BUTTON_MAX];
    bool m_IsConnected;

    float m_LeftTriggerValue;
    float m_RightTriggerValue;

    Vec2 m_LeftStickValue;
    Vec2 m_RightStickValue;
};

class InputSystem
{
public:
    InputSystem();
    ~InputSystem();
    void PreUpdate();
    void PostUpdate();
    void ProcessInput(SDL_Event event);
    const KeyboardState *GetKeyboard() const;
    const MouseState *GetMouse() const;
    const ControllerState* GetControllerState(uint32_t idx) const;
private:
    std::unique_ptr<KeyboardState> m_KeyboardState;
    std::unique_ptr<MouseState> m_MouseState;
    std::vector<std::unique_ptr<MouseState>> m_ControllerStates; 
};