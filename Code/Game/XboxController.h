/**
 *  @file       XBoxController.h
 *  @brief      CXBoxController class interface
 *
 *  @author     Mark L. Short
 *  @date       May 7, 2017
 *
 *
 */

#pragma once

#if !defined(__XBOX_CONTROLLER_H__)
#define __XBOX_CONTROLLER_H__

#include <Xinput.h>

class CXboxController
{
public:
    // left public for now....
    DWORD        m_dwController;
    DWORD        m_dwResult;
    WORD         m_wLeftThumbDeadZone;
    WORD         m_wRightThumbDeadZone;
    XINPUT_STATE m_stInput;
    XINPUT_STATE m_stLast;
    bool         m_bConnected;

    explicit CXboxController(DWORD dwController = 0, 
                             WORD wLeftThumbDZ  = XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE, 
                             WORD wRightThumbDZ = XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) noexcept;
    /// Default destructor
    ~CXboxController() noexcept;

    bool  UpdateControllerState(void);
    
    bool  IsThumbL_Pressed     (void) const noexcept;

    bool  IsThumbR_Pressed     (void) const noexcept;

    float CalcThumbL_Magnitude (void) const noexcept;

    float CalcThumbR_Magnitude (void) const noexcept;

    inline bool IsConnected(void) const noexcept
    { return m_bConnected; };

    inline const XINPUT_STATE& get_State(void) const noexcept
    { return m_stInput; };

    inline bool get_DPadUp(void) const noexcept
    { return (m_stInput.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP) != 0; };

    inline bool get_DPadDown(void) const noexcept
    { return (m_stInput.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN) != 0; };

    inline bool get_DPadLeft(void) const noexcept
    { return (m_stInput.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT) != 0; };
    
    inline bool get_DPadRight(void) const noexcept
    { return (m_stInput.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) != 0; };
    
    inline bool get_Start(void) const noexcept
    { return (m_stInput.Gamepad.wButtons & XINPUT_GAMEPAD_START) != 0; };

    inline bool get_Back(void) const noexcept
    { return (m_stInput.Gamepad.wButtons & XINPUT_GAMEPAD_BACK) != 0; };

    inline bool get_LeftThumb(void) const noexcept
    { return (m_stInput.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB) != 0; };

    inline bool get_RightThumb(void) const noexcept
    { return (m_stInput.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB) != 0; };

    inline bool get_LeftShoulder(void) const noexcept
    { return (m_stInput.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) != 0; };

    inline bool get_RightShoulder(void) const noexcept
    { return (m_stInput.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) != 0; };

/**
   @todo the rest of the button accessors need the following implementation
 */
    inline bool get_A(void) const noexcept
    { return (((m_stInput.Gamepad.wButtons & XINPUT_GAMEPAD_A) != 0) &&
              ((m_stLast.Gamepad.wButtons & XINPUT_GAMEPAD_A) == 0) ); };

    inline bool get_B(void) const noexcept
    { return (m_stInput.Gamepad.wButtons & XINPUT_GAMEPAD_B) != 0; };

    inline bool get_X(void) const noexcept
    { return (m_stInput.Gamepad.wButtons & XINPUT_GAMEPAD_X) != 0; };

    inline bool get_Y(void) const noexcept
    { return (m_stInput.Gamepad.wButtons & XINPUT_GAMEPAD_Y) != 0; };

    inline BYTE get_LeftTrigger(void) const noexcept
    { return m_stInput.Gamepad.bLeftTrigger; };

    inline BYTE get_RightTrigger(void) const noexcept
    { return m_stInput.Gamepad.bRightTrigger; };

    inline SHORT get_ThumbLX(void) const noexcept
    { return m_stInput.Gamepad.sThumbLX; };

    inline SHORT get_ThumbLY(void) const noexcept
    { return m_stInput.Gamepad.sThumbLY; };

    inline SHORT get_ThumbRX(void) const noexcept
    { return m_stInput.Gamepad.sThumbRX; };

    inline SHORT get_ThumbRY(void) const noexcept
    { return m_stInput.Gamepad.sThumbRY; };


};

#endif
