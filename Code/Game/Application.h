/**
 *  @file       Application.h
 *  @brief      CApplication class interface
 *
 *  @author     Mark L. Short
 *  @date       May 7, 2017
 *
 *
 */

#pragma once

#if !defined(__APPLICATION_H__)
#define __APPLICATION_H__

#ifndef _INC_TCHAR
    #include <tchar.h>
#endif 

#ifndef __KEYBOARD_H__
    #include "Keyboard.h"
#endif

#ifndef __XBOX_CONTROLLER_H__
    #include "XboxController.h"
#endif

#include "CommonDef.h"
// forward declaration
class CGame;
class CSoundManager;

class CApplication
{
    CGame*                  m_pGame;
    CSoundManager*          m_pSoundManager;
    CKeyboard               m_Keyboard;
    HINSTANCE               m_hInstance;
    HWND                    m_hMainWnd;
    HDC                     m_hdcDisplay;
    TCHAR*                  m_pszAppName;
    int                     m_iMainWinWidth;
    int                     m_iMainWinHeight;

    static CXboxController  s_rgControllers[MAX_CONTROLLERS];

public: 
    /// Default constructor
    constexpr CApplication() noexcept;
    /// Default destructor
    ~CApplication() noexcept;

    void Initialize ( HINSTANCE hInstance );

    void Shutdown   ( void ) noexcept;

    void RunFrame   ( void );
    void Render     ( void );
    void Update     ( float fDeltaTime );

    bool PlaySound  ( int iIndex ) noexcept;
    bool StopSound  ( int iIndex ) noexcept;

    inline bool IsKeyPressed         ( Keys key ) const noexcept
    { return m_Keyboard.IsKeyPressed(key); };

    inline bool WasKeyJustPressed    ( Keys key ) const noexcept
    { return m_Keyboard.WasKeyJustPressed(key); };

    inline void UpdateKeyboardStates ( void ) noexcept
    { m_Keyboard.UpdateStates(); };

    inline const KeyboardState& GetKeyboardState(void) const noexcept
    { return m_Keyboard.GetState(); };

    inline bool IsController_APressed(size_t nController = 0) const noexcept
    { if (nController < _countof(CApplication::s_rgControllers))
         return CApplication::s_rgControllers[nController].get_A();
      else
         return false; };

    inline bool IsController_StartPressed(size_t nController = 0) const noexcept
    { if (nController < _countof(CApplication::s_rgControllers))
         return CApplication::s_rgControllers[nController].get_Start();
      else
         return false; };

    inline bool IsController_DPadLeftPressed(size_t nController = 0) const noexcept
    { if (nController < _countof(CApplication::s_rgControllers))
         return CApplication::s_rgControllers[nController].get_DPadLeft();
      else
         return false; };

    inline bool IsController_DPadRightPressed(size_t nController = 0) const noexcept
    { if (nController < _countof(CApplication::s_rgControllers))
         return CApplication::s_rgControllers[nController].get_DPadRight();
      else
         return false; };

    inline bool IsController_DPadUpPressed(size_t nController = 0) const noexcept
    { if (nController < _countof(CApplication::s_rgControllers))
         return CApplication::s_rgControllers[nController].get_DPadUp();
      else
         return false; };

    inline bool IsController_ThumbLPressed(size_t nController = 0) const noexcept
    { if (nController < _countof(CApplication::s_rgControllers))
         return CApplication::s_rgControllers[nController].IsThumbL_Pressed();
      else
         return false; };

    inline bool IsController_ThumbRPressed(size_t nController = 0) const noexcept
    { if (nController < _countof(CApplication::s_rgControllers))
         return CApplication::s_rgControllers[nController].IsThumbR_Pressed();
      else
         return false; };

    inline short GetController_ThumbLX(size_t nController = 0) const noexcept
    { if (nController < _countof(CApplication::s_rgControllers))
         return CApplication::s_rgControllers[nController].get_ThumbLX();
      else
         return 0; };

    inline short GetController_ThumbLY(size_t nController = 0) const noexcept
    { if (nController < _countof(CApplication::s_rgControllers))
         return CApplication::s_rgControllers[nController].get_ThumbLY();
      else
         return 0; };

    inline float CalcController_ThumbLMagnitude(size_t nController = 0) const noexcept
    { if (nController < _countof(CApplication::s_rgControllers))
         return CApplication::s_rgControllers[nController].CalcThumbL_Magnitude();
      else
          return 0.f; };

    inline float CalcController_ThumbRMagnitude(size_t nController = 0) const noexcept
    { if (nController < _countof(CApplication::s_rgControllers))
         return CApplication::s_rgControllers[nController].CalcThumbR_Magnitude();
      else
          return 0.f; };

    static LRESULT CALLBACK MainWndProc    ( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );
    static void CALLBACK    KeyboardHandler( UINT nKey, BOOL bKeyPressed );

private:
    void    CreateOpenGLWindow      ( void ) noexcept;
    void    RegisterWndClass        ( void ) noexcept;

    void    OnSize                  ( void );
    void    ProcessKeyboardMsg      ( UINT uMsg, WPARAM wParam, LPARAM lParam );
    void    UpdateControllerStates  ( void );

    /// Copy constructor
    CApplication(const CApplication& o) = delete;
    /// Move constructor
    CApplication(const CApplication&& o) = delete;
    /// Assignment operator
    CApplication& operator=(const CApplication& rhs) = delete;
};

//-----------------------------------------------------------------------------------------------
constexpr CApplication::CApplication() noexcept
  : m_pGame(nullptr),
    m_pSoundManager(nullptr),
    m_Keyboard(),
    m_hInstance(nullptr),
    m_hMainWnd(nullptr),
    m_hdcDisplay(nullptr),
    m_pszAppName(_T("Asteroids")),
    m_iMainWinWidth(WINDOW_PHYSICAL_WIDTH),
    m_iMainWinHeight(WINDOW_PHYSICAL_HEIGHT)
{
};

_declspec(selectany) CApplication g_theApp;

#endif

