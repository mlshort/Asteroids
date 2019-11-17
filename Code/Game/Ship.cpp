/**
 *  @file       Ship.cpp
 *  @brief      CShip class implementation
 *
 *  @author     Mark L. Short
 *  @date       May 7, 2017
 *
 *
 *  <b>Cite:<\b>
 */

#define WIN32_LEAN_AND_MEAN
#include "targetver.h"  // this needs to be the 1st header included
#include "CommonDef.h"

#include <Windows.h>
#include "Engine/Renderer/Renderer.h"
#include "Engine/Utility/DebugUtils.h"

#include "SoundList.h"
#include "Application.h"
#include "Ship.h"


const eng::ColorRGBA k_clrShipDefault = eng::RGBA_CYAN;


//-----------------------------------------------------------------------------------------------
void CShip::Render(void) const noexcept
{
    eng::g_theRdr.SetLineWidth( k_fShipLineWidth );
    eng::g_theRdr.SetColor( k_clrShipDefault );

    eng::g_theRdr.PushView();

    eng::g_theRdr.TranslateView( get_Center() );
    eng::g_theRdr.RotateView( get_Orientation() );

    eng::g_theRdr.DrawLine( eng::math::CVector2f(-12.5f,  12.5f), eng::math::CVector2f( 25.f,    0.f) );
    eng::g_theRdr.DrawLine( eng::math::CVector2f( 25.f,    0.f),  eng::math::CVector2f(-12.5f, -12.5f) );
    eng::g_theRdr.DrawLine( eng::math::CVector2f( 25.f,    0.f),  eng::math::CVector2f( -6.25f,-10.f) );
    eng::g_theRdr.DrawLine( eng::math::CVector2f( -6.25f,-10.f),  eng::math::CVector2f( -6.25f, 10.f) );

    const KeyboardState& kbState = g_theApp.GetKeyboardState();
    // draw engine exhaust
    if (kbState.IsKeyStateSet(Keys::W) || kbState.IsKeyStateSet(Keys::Up) ||
        g_theApp.IsController_DPadUpPressed() || g_theApp.IsController_ThumbLPressed() )
    {
        eng::g_theRdr.SetColor( eng::RGBA_RED );

        eng::g_theRdr.DrawLine( eng::math::CVector2f( -12.5f, 0.f),  eng::math::CVector2f( -6.25f, 10.f) );
        eng::g_theRdr.DrawLine( eng::math::CVector2f( -12.5f, 0.f),  eng::math::CVector2f( -6.25f,-10.f) );
    }

    // draw an orientation overlay (for debugging purposes)
    if (kbState.IsKeyStateSet(Keys::T))
    {
        eng::g_theRdr.SetLineWidth( 0.5f );
        eng::g_theRdr.SetColor( eng::RGBA_WHITE );
        eng::g_theRdr.DrawLine( eng::math::CVector2f(-50.f,  0.f), eng::math::CVector2f( 50.f,  0.f) );
        eng::g_theRdr.DrawLine( eng::math::CVector2f(  0.f,-50.f), eng::math::CVector2f(  0.f, 50.f) );
    }

    eng::g_theRdr.PopView();
};

//-----------------------------------------------------------------------------------------------
void CShip::Update(float fDeltaTime) noexcept
{
    const KeyboardState& kbState = g_theApp.GetKeyboardState();
    bool bThrusting = false;

    if (kbState.IsKeyStateSet(Keys::W) || kbState.IsKeyStateSet(Keys::Up) || g_theApp.IsController_DPadUpPressed())
    {
        ThrustForward(fDeltaTime, k_fShipThrust);
        bThrusting = true;
    }
    else
    {
        float fMagnitude = g_theApp.CalcController_ThumbLMagnitude();
        if (fMagnitude)
        {
            ThrustForward(fDeltaTime, k_fShipThrust * fMagnitude);
            bThrusting = true;
        }
    }

    if (bThrusting)
    {
        g_theApp.PlaySound(SND_ENGINE);
    }
    else
    {
        g_theApp.StopSound(SND_ENGINE);
    }

    Move(fDeltaTime);
    Turn(fDeltaTime);
};

//-----------------------------------------------------------------------------------------------
void CShip::ThrustForward( float fDeltaTime, float fThrust ) noexcept
{
    eng::math::CVector2f vForward(eng::math::CalcXComponent(get_Orientation()),
                                  eng::math::CalcYComponent(get_Orientation()));

    vForward *= ( fThrust * fDeltaTime );

    incr_Velocity(vForward);
}

//-----------------------------------------------------------------------------------------------
void CShip::Move( float fDeltaTime ) noexcept
{
    incr_Center ( get_Velocity() * fDeltaTime );
}

//-----------------------------------------------------------------------------------------------
void CShip::Turn( float fDeltaTime ) noexcept
{
    const float fLX = g_theApp.GetController_ThumbLX();
    const float fLY = g_theApp.GetController_ThumbLY();

    if (fLX || fLY)
    {
        m_degOrientation = eng::math::RadiansToDegrees( std::atan2( fLY, fLX ) );
#ifdef _DEBUG
        eng::util::DebugTrace(_T("[%s] Direction:%6.2f ThumbX:%6.2f ThumbY:%6.2f \n"), __FUNCTIONW__, m_degOrientation, fLX, fLY );
#endif
    }
    else
    {
        // 1.0 means "turn counter-clockwise" (positive direction), -1.0 means "turn clockwise" (negative direction)
        float turnDirection = 0.f; 

        const KeyboardState& kbState = g_theApp.GetKeyboardState();


        if (kbState.IsKeyStateSet(Keys::A) || kbState.IsKeyStateSet(Keys::Left)  || g_theApp.IsController_DPadLeftPressed())
            turnDirection += 1.f;
        if (kbState.IsKeyStateSet(Keys::D) || kbState.IsKeyStateSet(Keys::Right) || g_theApp.IsController_DPadRightPressed())
            turnDirection += -1.f;

        float degreesToTurnThisFrame = k_fShipTurnRate * fDeltaTime;
        degreesToTurnThisFrame *= turnDirection; // May be zero if not turning
        m_degOrientation += degreesToTurnThisFrame;
    }
}
