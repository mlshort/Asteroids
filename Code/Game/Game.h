/**
 *  @file       Game.h
 *  @brief      CGame class interface
 *
 *  @author     Mark L. Short
 *  @date       May 7, 2017
 *
 *
 */

#pragma once

#if !defined(__GAME_H__)
#define __GAME_H__

#ifndef _VECTOR_
    #include <vector>
#endif

#ifndef __VECTOR2_H__
    #include "Engine/Math/Vector2.h"
#endif

// forward declaration
namespace eng
{
class CActor2;
}

class CShip;
class CSoundManager;

class CGame
{
    CShip*                           m_pShip;
    CSoundManager*                   m_pSoundManager;
    size_t                           m_nAsteroidWaveSize;
    std::vector<eng::CActor2*>       m_rgActors;

public:
    /// Initialization constructor
    CGame( CSoundManager* pSndManager );
    /// Default destructor
    ~CGame() noexcept;

    void Render                 ( void ) const;
    void Update                 ( float fDeltaTime );

    void InitActors             ( void );
    bool IsShipActive           ( void ) const noexcept;
    void SpawnShip              ( void );
    void SpawnAsteroidWave      ( void );
    bool SpawnLargeAsteroid     ( void );
    bool FireProjectile         ( void );
    bool DestroyRandomAsteroid  ( void );

private:
    bool CheckForCollisions     ( std::vector<std::pair<eng::CActor2*, eng::CActor2*> >& rgCollisions ) const;
    void ResolveCollisions      ( const std::vector<std::pair<eng::CActor2*, eng::CActor2*> >& rgCollisions );
    bool DestroyInactiveActors  ( void );

    bool SpawnMediumAsteroid    ( const eng::math::CVector2f& vCenter, const eng::math::CVector2f& vVelocity, float fAngularVelocity );
    bool SpawnSmallAsteroid     ( const eng::math::CVector2f& vCenter, const eng::math::CVector2f& vVelocity, float fAngularVelocity );

    constexpr const CShip*  get_Ship  ( void ) const noexcept;

    /// Copy constructor
    CGame( const CGame& ) = delete;
    /// Assignment operator
    CGame& operator = ( const CGame& ) = delete;
};

constexpr const CShip* 
CGame::get_Ship (void) const noexcept
{
    return m_pShip;
};

#endif