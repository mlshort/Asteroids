/**
 *  @file       Keyboard.cpp
 *  @brief      CKeyboard class implementation
 *
 *  @author     Mark L. Short
 *  @date       May 7, 2017
 *
 *
 *  <b>Cite:</b>  Microsoft DirectX Toolkit
 *
 */

#define WIN32_LEAN_AND_MEAN
#include "targetver.h"  // this needs to be the 1st header included

#include <Windows.h>
#include <stdint.h>
#include <memory>

#include "Keyboard.h"

// Generic helper functions
bool SetKeyDownState(int iKey, KeyboardState& state);
bool SetKeyUpState  (int iKey, KeyboardState& state);

//-----------------------------------------------------------------------------------------------
bool  KeyboardState::IsKeyStateSet(Keys key) const noexcept
{
    bool bRetVal = false;
    // some basic sanity checking
    if (key >= Keys::None && key <= Keys::OemClear)
    {
        auto pState = reinterpret_cast<const uint32_t*>( this );
        auto iKey   = static_cast<int>(key);
        unsigned int nBitFlag = 1u << ( iKey & 0x1f );
        bRetVal = ( pState[( iKey >> 5 )] & nBitFlag ) != 0;
    }
    return bRetVal;
}

//-----------------------------------------------------------------------------------------------
CKeyboard::CKeyboard() noexcept
    : m_State(),
      m_StateTracker(),
      m_pfHandler(nullptr)
{
};

//-----------------------------------------------------------------------------------------------
void CKeyboard::InitKeyStates(void) noexcept
{
    memset(&m_State, 0, sizeof(KeyboardState));
    m_StateTracker.InitKeyStates();
}

//-----------------------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------------------
void   CKeyboard::OnKeyUp  (int iKey)
{
    if (SetKeyUpState(iKey, m_State) && m_pfHandler)
        m_pfHandler(iKey, FALSE);
};

//-----------------------------------------------------------------------------------------------
void   CKeyboard::OnKeyDown(int iKey)
{
    if (SetKeyDownState(iKey, m_State) && m_pfHandler)
        m_pfHandler(iKey, TRUE);
};

//-----------------------------------------------------------------------------------------------
void CKeyboard::SetHandler(KEYBOARD_HANDLER pfHandler) noexcept
{
    m_pfHandler = pfHandler;
};

//-----------------------------------------------------------------------------------------------
void CKeyboard::ProcessMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{

    bool bDown = false;

    switch (uMsg)
    {
    case WM_ACTIVATEAPP:
        InitKeyStates();
        return;

    case WM_KEYDOWN:
    case WM_SYSKEYDOWN:
        bDown = true;
        break;

    case WM_KEYUP:
    case WM_SYSKEYUP:
        break;

    default:
        return;
    }

    int iVK = static_cast<int>( wParam );
    switch (iVK)
    {
    case VK_SHIFT:
        iVK = ::MapVirtualKey((lParam & 0x00ff0000) >> 16, MAPVK_VSC_TO_VK_EX);
        if ( !bDown )
        {
            // Workaround to ensure left vs. right shift get cleared when both were pressed at same time
            OnKeyUp(VK_LSHIFT);
            OnKeyUp(VK_RSHIFT);
        }
        break;

    case VK_CONTROL:
        iVK = (lParam & 0x01000000) ? VK_RCONTROL : VK_LCONTROL;
        break;

    case VK_MENU:
        iVK = (lParam & 0x01000000) ? VK_RMENU : VK_LMENU;
        break;
    }

    if (bDown)
    {
        OnKeyDown(iVK);
    }
    else
    {
        OnKeyUp(iVK);
    }
}

//======================================================================================
// KeyboardStateTracker
//======================================================================================

void CKeyboard::CStateTracker::Update( const KeyboardState& state )
{
    auto pCurr     = reinterpret_cast<const uint32_t*>(&state);
    auto pPrev     = reinterpret_cast<const uint32_t*>(&m_stLast);
    auto pReleased = reinterpret_cast<uint32_t*>(&m_stReleased);
    auto pPressed  = reinterpret_cast<uint32_t*>(&m_stPressed);
    for (size_t j = 0; j < (sizeof(KeyboardState) / sizeof(uint32_t)); ++j)
    {
        *pPressed  = *pCurr & ~(*pPrev);
        *pReleased = ~(*pCurr) & *pPrev;

        ++pCurr;
        ++pPrev;
        ++pReleased;
        ++pPressed;
    }

    m_stLast = state;
}

//-----------------------------------------------------------------------------------------------
void CKeyboard::CStateTracker::InitKeyStates(void) noexcept
{
    static_assert(std::is_standard_layout<CKeyboard::CStateTracker>::value,
                  "is_standard_layout failed for CStateTracer!!!");

    memset(this, 0, sizeof(CStateTracker));
};

//-----------------------------------------------------------------------------------------------
bool  CKeyboard::CStateTracker::IsKeyPressed(Keys key) const noexcept
{
    return m_stPressed.IsKeyStateSet(key);
};

//-----------------------------------------------------------------------------------------------
bool  CKeyboard::CStateTracker::IsKeyReleased(Keys key) const noexcept
{
    return m_stReleased.IsKeyStateSet(key);
};

bool  CKeyboard::CStateTracker::IsKeyLast(Keys key) const noexcept
{
    return m_stLast.IsKeyStateSet(key);
};

//-----------------------------------------------------------------------------------------------
bool SetKeyDownState(int iKey, KeyboardState& state)
{
    bool bRetVal = false;
    if (( iKey >= 0 ) && ( iKey <= VK_OEM_CLEAR))
    {
        auto pState = reinterpret_cast<uint32_t*>( &state );
        unsigned int nBitFlag = 1u << ( iKey & 0x1f );  // 00011111
        pState[( iKey >> 5 )] |= nBitFlag;
        bRetVal = true;
    }
    return bRetVal;
};

//-----------------------------------------------------------------------------------------------
bool SetKeyUpState(int iKey, KeyboardState& state)
{
    bool bRetVal = false;
    if (( iKey >= 0 ) && ( iKey <= VK_OEM_CLEAR))
    {
        auto pState = reinterpret_cast<uint32_t*>( &state );
        unsigned int nBitFlag = 1u << ( iKey & 0x1f );
        pState[( iKey >> 5 )] &= ~nBitFlag;
        bRetVal = true;
    }

    return bRetVal;
};

