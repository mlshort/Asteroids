/**
 *  @file       Projectile.cpp
 *  @brief      CProjectile class implementation
 *
 *  @author     Mark L. Short
 *  @date       May 7, 2017
 *
 *
 */

#define WIN32_LEAN_AND_MEAN
#include "targetver.h"  // this needs to be the 1st header included
#include "CommonDef.h"

#include <Windows.h>
#include "Engine/Renderer/Renderer.h"

#include "Projectile.h"




//-----------------------------------------------------------------------------------------------
CProjectile::~CProjectile()
{
};

//-----------------------------------------------------------------------------------------------
void CProjectile::Render(void) const
{
    if (IsActive())
       eng::g_theRdr.DrawPoint( get_Center(), eng::RGBA_RED, k_fProjectileRadius * 2);
};

//-----------------------------------------------------------------------------------------------
void CProjectile::Update(float fDeltaTime)
{
    Move (fDeltaTime);
};

//-----------------------------------------------------------------------------------------------
void CProjectile::Move( float fDeltaTime ) noexcept
{
    incr_Center ( get_Velocity() * fDeltaTime );
};
