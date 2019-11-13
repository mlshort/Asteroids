/**
 *  @file       Projectile.h
 *  @brief      CProjectile class interface
 *
 *  @author     Mark L. Short
 *  @date       May 7, 2017
 *
 *
 */

#pragma once

#if !defined(__PROJECTILE_H__)
#define __PROJECTILE_H__

#ifndef __ACTOR2_H__
    #include "Engine/Core/Actor2.h"
#endif


class CProjectile :
    public eng::CActor2
{
    float m_fSpawnTime;

public:
    /// Default Constructor
    constexpr CProjectile( float fSpawnTime = 0.0 ) noexcept;
    /// Copy Constructor
    constexpr CProjectile( const CProjectile& o ) noexcept;
    /// Conversion Constructor
    constexpr explicit CProjectile(const eng::math::CVector2f& vCenter, const eng::math::CVector2f& vVel, float fSpawnTime = 0.0) noexcept;
    /// Conversion Constructor
    constexpr explicit CProjectile(float fCenterX, float fCenterY, float fDeltaX, float fDeltaY, float fSpawnTime = 0.0) noexcept;
    /// Default Destructor
    virtual ~CProjectile() noexcept;

    inline void     set_SpawnTime( float fTime ) noexcept
    { m_fSpawnTime = fTime; };

    constexpr float get_SpawnTime( void ) const noexcept
    { return m_fSpawnTime; };


// IRenderable 
    void Render       ( void ) const override;
    void Update       ( float fDeltaTime ) override;

private:
    void         Move         ( float fDeltaTime ) noexcept;
};

//-----------------------------------------------------------------------------------------------
constexpr 
CProjectile::CProjectile (float fSpawnTime /* = 0.0 */) noexcept
    : eng::CActor2 (),
      m_fSpawnTime (fSpawnTime)
{
};

//-----------------------------------------------------------------------------------------------
constexpr 
CProjectile::CProjectile (const CProjectile& o) noexcept
    : eng::CActor2 (o),
      m_fSpawnTime (o.m_fSpawnTime)
{
};

//-----------------------------------------------------------------------------------------------
constexpr 
CProjectile::CProjectile (const eng::math::CVector2f& vCenter, const eng::math::CVector2f& vVel, float fSpawnTime) noexcept
    : eng::CActor2 (vCenter, k_fProjectileRadius, vVel),
      m_fSpawnTime (fSpawnTime)
{
};

//-----------------------------------------------------------------------------------------------
constexpr 
CProjectile::CProjectile (float fCenterX, float fCenterY, float fDeltaX, float fDeltaY, float fSpawnTime) noexcept
    : eng::CActor2 (fCenterX, fCenterY, k_fProjectileRadius, fDeltaX, fDeltaY),
      m_fSpawnTime (fSpawnTime)
{
};
#endif

