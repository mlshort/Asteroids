/**
 *  @file       XboxController.cpp
 *  @brief      CXboxController class implementation
 *
 *  @author     Mark L. Short
 *  @date       May 7, 2017
 *
 *
 *  <b>Cite:<\b>
 */

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include "targetver.h"  // this needs to be the 1st header included
#include <Windows.h>
#include <cmath>
#include <limits>

#include "XboxController.h"

#pragma comment( lib, "Xinput9_1_0" ) // We need to explicitly use XInput v9.1.0, as newer (1_4+) versions do not run under Windows 7 or before

//-----------------------------------------------------------------------------------------------
CXboxController::CXboxController(DWORD dwController /* = 0 */,
                                 WORD wLeftThumbDZ,
                                 WORD wRightThumbDZ) noexcept
    : m_dwController(dwController),
      m_dwResult(0),
      m_wLeftThumbDeadZone (wLeftThumbDZ),
      m_wRightThumbDeadZone(wRightThumbDZ),
      m_bConnected(false)
{
    memset(&m_stInput, 0, sizeof(m_stInput));
    memset(&m_stLast, 0, sizeof(m_stLast));
}

//-----------------------------------------------------------------------------------------------
CXboxController::~CXboxController()
{
}

//-----------------------------------------------------------------------------------------------
bool CXboxController::UpdateControllerState(void)
{
     m_stLast   = m_stInput; 
     m_dwResult = XInputGetState( m_dwController, &m_stInput );

     if (m_dwResult == ERROR_SUCCESS)
         m_bConnected = true;
     else
         m_bConnected = false;

     return m_bConnected;
};

//-----------------------------------------------------------------------------------------------
bool CXboxController::IsThumbL_Pressed(void) const noexcept
{
    float fLX          = get_ThumbLX();
    float fLY          = get_ThumbLY();
    float fMagnitudeSq = fLX * fLX + fLY * fLY;

    return (fMagnitudeSq > (m_wLeftThumbDeadZone * m_wLeftThumbDeadZone) );
};

//-----------------------------------------------------------------------------------------------
bool CXboxController::IsThumbR_Pressed(void) const noexcept
{
    float fLX          = get_ThumbRX();
    float fLY          = get_ThumbRY();
    float fMagnitudeSq = fLX * fLX + fLY * fLY;

    return (fMagnitudeSq > (m_wRightThumbDeadZone * m_wRightThumbDeadZone) );
};


//-----------------------------------------------------------------------------------------------
float CXboxController::CalcThumbL_Magnitude(void) const noexcept
{
    float fLX        = get_ThumbLX();
    float fLY        = get_ThumbLY();
    float fMagnitude = std::sqrt(fLX * fLX + fLY * fLY);

    if (fMagnitude > m_wLeftThumbDeadZone)
    {
        if (fMagnitude > std::numeric_limits<SHORT>::max())
            fMagnitude = std::numeric_limits<SHORT>::max();

        fMagnitude -= m_wLeftThumbDeadZone;
        // normalize the result with respect to its expected range
        return fMagnitude / ( std::numeric_limits<SHORT>::max() - m_wLeftThumbDeadZone );
    }
    else
    {
        return 0.0f;
    }
};

//-----------------------------------------------------------------------------------------------
float CXboxController::CalcThumbR_Magnitude(void) const noexcept
{
    float fLX        = get_ThumbRX();
    float fLY        = get_ThumbRY();
    float fMagnitude = std::sqrt(fLX * fLX + fLY * fLY);

    if (fMagnitude > m_wRightThumbDeadZone)
    {
        if (fMagnitude > std::numeric_limits<SHORT>::max())
            fMagnitude = std::numeric_limits<SHORT>::max();

        fMagnitude -= m_wRightThumbDeadZone;
        // normalize the result with respect to its expected range
        return fMagnitude / ( std::numeric_limits<SHORT>::max() - m_wRightThumbDeadZone );
    }
    else
    {
        return 0.0f;
    }
};