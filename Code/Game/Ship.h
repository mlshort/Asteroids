/**
 *  @file       Ship.h
 *  @brief      CShip class interface
 *
 *  @author     Mark L. Short
 *  @date       May 7, 2017
 *
 *
 */

#pragma once

#if !defined(__SHIP_H__)
#define __SHIP_H__

#ifndef __ACTOR2_H__
    #include "Engine/Core/Actor2.h"
#endif


class CShip :
    public eng::CActor2
{
    DEGREES m_degOrientation;
public:
    /// Default Constructor
    constexpr CShip() noexcept;
    /// Copy Constructor
    constexpr CShip(const CShip& o) noexcept;
    /// Conversion Constructor
    constexpr explicit CShip(const eng::math::CVector2f& vCenter, const eng::math::CVector2f& vVel) noexcept;
    /// Conversion Constructor
    constexpr explicit CShip(float fCenterX, float fCenterY, float fDeltaX = 0.0, float fDeltaY = 0.0) noexcept;
    /// Default Destructor
    virtual ~CShip() noexcept = default;

/**
  *  @brief returns the ship orientation in degrees
  */
    constexpr DEGREES  get_Orientation( void ) const noexcept
    { return m_degOrientation; };

// IRenderable  
    void              Render         ( void ) const noexcept override;
    void              Update         ( float fDeltaTime ) noexcept override;

private:
    void               ThrustForward  ( float fDeltaTime, float fThrust ) noexcept;
    void               Move           ( float fDeltaTime ) noexcept;
    void               Turn           ( float fDeltaTime ) noexcept;
};


//-----------------------------------------------------------------------------------------------
constexpr CShip::CShip () noexcept
    : eng::CActor2 (),
      m_degOrientation ()
{
};

//-----------------------------------------------------------------------------------------------
constexpr CShip::CShip (const CShip& o) noexcept
    : eng::CActor2 (o),
      m_degOrientation (o.m_degOrientation)
{
};

//-----------------------------------------------------------------------------------------------
constexpr CShip::CShip (const eng::math::CVector2f& vPos, const eng::math::CVector2f& vVel) noexcept
    : eng::CActor2 (vPos, k_ShipRadius, vVel),
      m_degOrientation ()
{
};

//-----------------------------------------------------------------------------------------------
constexpr CShip::CShip (float fPosX, float fPosY, float fDeltaX, float fDeltaY) noexcept
    : eng::CActor2 (fPosX, fPosY, k_ShipRadius, fDeltaX, fDeltaY),
      m_degOrientation ()
{
};


#endif

