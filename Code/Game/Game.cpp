/**
 *  @file       Game.cpp
 *  @brief      CApplication class implementation
 *
 *  @author     Mark L. Short
 *  @date       May 7, 2017
 *
 *
 */
#define WIN32_LEAN_AND_MEAN
#include "targetver.h"  // this needs to be the 1st header include
#include "CommonDef.h"

#include "Engine/Renderer/Renderer.h"
#include "Engine/Utility/TimeUtils.h"
#include "Engine/Utility/DebugUtils.h"

#include "Asteroid.h"
#include "Ship.h"
#include "Projectile.h"
#include "SoundManager.h"

#include "Game.h"

// the following are helper methods and
// are kind of hacky relying on dynamic_cast

bool IsShip(eng::CActor2* pActor) noexcept
{
    CShip* pShip = dynamic_cast<CShip*>(pActor);
    return (pShip != nullptr);
};

bool IsProjectile(eng::CActor2* pActor) noexcept
{
    CProjectile* pProj = dynamic_cast<CProjectile*>(pActor);
    return (pProj != nullptr);
};

bool IsAsteroid(eng::CActor2* pActor) noexcept
{
    CAsteroid* pAst = dynamic_cast<CAsteroid*>(pActor);
    return (pAst != nullptr);
};


//-----------------------------------------------------------------------------------------------
CGame::CGame( CSoundManager* pSoundManager )
    : m_pShip(nullptr),
      m_pSoundManager(pSoundManager),
      m_nAsteroidWaveSize(INITIAL_ASTEROIDS),
      m_rgActors()
{
    m_rgActors.reserve(MAX_ACTORS);
}

//-----------------------------------------------------------------------------------------------
CGame::~CGame()
{
   for ( auto pActor : m_rgActors )
    {
        if ( pActor )
            delete pActor;
    }
}

//-----------------------------------------------------------------------------------------------
void CGame::Render( void ) const
{
    eng::g_theRdr.SetClearColor(eng::RGBA_BLACK);
    eng::g_theRdr.ClearColorBuffer();

    for ( auto pActor : m_rgActors )
    {
        if (pActor)
            pActor->Render();
    }
};

//-----------------------------------------------------------------------------------------------
void CGame::Update( float fDeltaTime )
{
    for ( auto pActor : m_rgActors )
    {
        if (pActor)
        {
            pActor->Update(fDeltaTime);

            // Brute-force screen wrap implementation
            if (pActor->get_CenterX() < -OFFSET_FROM_WINDOWS_DESKTOP)
                pActor->set_CenterX( static_cast<float>(VIEW_RIGHT + OFFSET_FROM_WINDOWS_DESKTOP) );
            if (pActor->get_CenterX() > VIEW_RIGHT + OFFSET_FROM_WINDOWS_DESKTOP)
                pActor->set_CenterX( static_cast<float>(-OFFSET_FROM_WINDOWS_DESKTOP) );

            if (pActor->get_CenterY() < -OFFSET_FROM_WINDOWS_DESKTOP)
                pActor->set_CenterY( static_cast<float>(VIEW_TOP + OFFSET_FROM_WINDOWS_DESKTOP) );
            if (pActor->get_CenterY() > VIEW_TOP + OFFSET_FROM_WINDOWS_DESKTOP)
                pActor->set_CenterY( static_cast<float>(-OFFSET_FROM_WINDOWS_DESKTOP) );

            // using dynamic_cast for now
            CProjectile* pProj = dynamic_cast<CProjectile*>(pActor);

            if (pProj)
            {
                if (eng::util::GetCurrentTimeInSeconds() - pProj->get_SpawnTime() >= 2.0)
                {
                    pProj->set_Active(false); // mark for deletion
                }
            }
        }
    }

    std::vector<std::pair<eng::CActor2*, eng::CActor2*> > rgCollisions;

    if ( CheckForCollisions( rgCollisions ) ) // if we find collisions, resolve them
    {
        ResolveCollisions (rgCollisions );
    }

    if (DestroyInactiveActors()) // did we destroy any actors?
    {
        // check to see if we need to spawn the next asteroid wave
        if (( m_rgActors.size() == 0 ) || ( m_rgActors.size() == 1 && m_pShip ))
            SpawnAsteroidWave();
    }
};

//-----------------------------------------------------------------------------------------------
bool CGame::CheckForCollisions( std::vector<std::pair<eng::CActor2*, eng::CActor2*> >& rgCollisionsFound ) const
{
    bool bResult = false;
    for ( auto pActor1 : m_rgActors )
    {
        if (pActor1)
        {
            if ( IsShip(pActor1) || IsProjectile(pActor1) )
            {
                for ( auto pActor2 : m_rgActors )
                {
                    if ( IsAsteroid(pActor2) )
                    {
                        if (pActor1->IntersectsWith(*pActor2))
                        {
                            rgCollisionsFound.push_back(std::make_pair(pActor1, pActor2)); // note - may throw an exception
                            bResult = true;
                        }
                    }
                }
            }
        }
    }

    return bResult;
};

//-----------------------------------------------------------------------------------------------
void CGame::ResolveCollisions( const std::vector<std::pair<eng::CActor2*, eng::CActor2*> >& rgCollisions )
{
#ifdef _DEBUG
    eng::util::DebugTrace(_T("%d Collisions Found \n"), rgCollisions.size() );
#endif

    for ( auto pairActors : rgCollisions )
    {
        pairActors.first->set_Active(false);
        pairActors.second->set_Active(false);

        // if the ship is about to die, we need to clear the
        // class pointer now.
        CShip* pShip = dynamic_cast<CShip*>(pairActors.first);

        if (pShip)
        {
            m_pShip = nullptr;
            m_pSoundManager->Play(SND_EXPLOSION);
        }
        else
        {
            // must be a missile.
            m_pSoundManager->Play(SND_MISSILE_HIT);
        }

        CAsteroid* pAsteroid = dynamic_cast<CAsteroid*>(pairActors.second);
        if (pAsteroid)
        {
            if (pAsteroid->get_Type() == AST_LARGE)
            {
                eng::math::CVector2f vVelocity = pAsteroid->get_Velocity();

                RADIANS fTheta = eng::math::RangedRand(0.0f, static_cast<RADIANS>(eng::math::TWO_PI) );
                vVelocity.Rotate(fTheta);
                SpawnMediumAsteroid(pAsteroid->get_Center(), vVelocity, pAsteroid->get_AngularVelocity() );

                fTheta = eng::math::RangedRand(0.0f, static_cast<RADIANS>(eng::math::TWO_PI) );
                vVelocity.Rotate(fTheta);
                SpawnMediumAsteroid(pAsteroid->get_Center(), vVelocity, pAsteroid->get_AngularVelocity() );
            }
            if (pAsteroid->get_Type() == AST_MEDIUM)
            {
                eng::math::CVector2f vVelocity = pAsteroid->get_Velocity();

                RADIANS fTheta = eng::math::RangedRand(0.0f, static_cast<RADIANS>(eng::math::TWO_PI) );
                vVelocity.Rotate(fTheta);
                SpawnSmallAsteroid(pAsteroid->get_Center(), vVelocity, pAsteroid->get_AngularVelocity() );

                fTheta = eng::math::RangedRand(0.0f, static_cast<RADIANS>(eng::math::TWO_PI) );
                vVelocity.Rotate(fTheta);
                SpawnSmallAsteroid(pAsteroid->get_Center(), vVelocity, pAsteroid->get_AngularVelocity() );
            }
        }
    }
};

//-----------------------------------------------------------------------------------------------
bool CGame::DestroyInactiveActors(void)
{
    bool bReturn = false;
    if (m_rgActors.size() > 0)
    {
        for (size_t i = 0; i < m_rgActors.size(); i++)
        {
            if (m_rgActors[i]->IsActive() == false)
            {
                delete m_rgActors[i];
                m_rgActors[i] = nullptr;
                bReturn = true;
            }
        }

        auto itEnd = std::remove_if(m_rgActors.begin(), m_rgActors.end(), [](eng::CActor2* pActor)
        {
            return pActor == nullptr;
        });
        m_rgActors.erase(itEnd, m_rgActors.end());
    }
    return bReturn;
};

//-----------------------------------------------------------------------------------------------
void CGame::InitActors( void )
{
    SpawnShip();
    SpawnAsteroidWave();
}

//-----------------------------------------------------------------------------------------------
bool CGame::IsShipActive (void) const noexcept
{
    auto pShip = get_Ship ();
    return (pShip && pShip->IsActive ());
};

//-----------------------------------------------------------------------------------------------
void CGame::SpawnShip( void )
{
    if (m_pShip == nullptr)
    {
        m_pShip = new CShip( static_cast<float>(VIEW_RIGHT / 2.f), static_cast<float>(VIEW_TOP / 2.f) );
        m_rgActors.push_back(m_pShip); // note - may throw an exception
    }
};

//-----------------------------------------------------------------------------------------------
void CGame::SpawnAsteroidWave( void )
{
    for (size_t i = 0; i < m_nAsteroidWaveSize; i++)
    {
        SpawnLargeAsteroid();
    }
    // increment the Asteroid Wave Size for next wave
    m_nAsteroidWaveSize += ASTEROID_WAVE_DELTA;
}

//-----------------------------------------------------------------------------------------------
bool CGame::SpawnLargeAsteroid(void)
{
    bool bReturn = false;
    if (m_rgActors.size() < MAX_ACTORS) // make sure we have room
    {
        eng::math::CVector2f vCenter(-OFFSET_FROM_WINDOWS_DESKTOP,
                                     eng::math::RangedRand(static_cast<float>( OFFSET_FROM_WINDOWS_DESKTOP + 1 ),
                                     static_cast<float>( VIEW_TOP - OFFSET_FROM_WINDOWS_DESKTOP - 1 )));

        RADIANS fTheta = eng::math::RangedRand(0.0f, static_cast<RADIANS>( eng::math::TWO_PI ));
        eng::math::CVector2f vVelocity(k_fAsteroidSpeed * std::cos(fTheta),
                                       k_fAsteroidSpeed * std::sin(fTheta));

        float fAngularVelocity = eng::math::RangedRand(0.0f, 180.0f) - 90.0f;

        CLargeAsteroid* pLargeAsteroid = new CLargeAsteroid(vCenter, vVelocity, fAngularVelocity);
        if (pLargeAsteroid)
        {
            pLargeAsteroid->InitIrregularAsteroid(ASTEROID_VERTICES);

            m_rgActors.push_back(pLargeAsteroid); // note - may throw an exception
            bReturn = true;
        }
    }
    return bReturn;
}

//-----------------------------------------------------------------------------------------------
bool CGame::SpawnMediumAsteroid(const eng::math::CVector2f& vCenter, const eng::math::CVector2f& vVelocity, float fAngularVelocity)
{
    bool bReturn = false;

    if (m_rgActors.size() < MAX_ACTORS)
    {
        CMediumAsteroid* pMediumAsteroid = new CMediumAsteroid(vCenter, vVelocity, fAngularVelocity);
        if (pMediumAsteroid)
        {
            pMediumAsteroid->InitIrregularAsteroid(ASTEROID_VERTICES);

            m_rgActors.push_back(pMediumAsteroid); // note - may throw an exception
            bReturn = true;
        }
    }
    return bReturn;
}

//-----------------------------------------------------------------------------------------------
bool CGame::SpawnSmallAsteroid(const eng::math::CVector2f& vCenter, const eng::math::CVector2f& vVelocity, float fAngularVelocity)
{
    bool bReturn = false;

    if (m_rgActors.size() < MAX_ACTORS)
    {
        CSmallAsteroid* pSmallAsteroid = new CSmallAsteroid(vCenter, vVelocity, fAngularVelocity);
        if (pSmallAsteroid)
        {
            pSmallAsteroid->InitIrregularAsteroid(ASTEROID_VERTICES);

            m_rgActors.push_back(pSmallAsteroid); // note - may throw an exception
            bReturn = true;
        }
    }
    return bReturn;
}

//-----------------------------------------------------------------------------------------------
bool CGame::FireProjectile(void)
{
    bool bReturn = false;

    if (m_rgActors.size() < MAX_ACTORS)
    {
        const CShip* pShip = get_Ship();

        if (pShip && pShip->IsActive())
        {
#ifdef _DEBUG
            eng::util::DebugTrace(_T("[%s] ======================\n"), __FUNCTIONW__);
            eng::util::DebugTrace(_T("  Ship Direction: %6.2f \n"), pShip->get_Orientation());
#endif
            float fX = eng::math::CalcXComponent(pShip->get_Orientation());
            float fY = eng::math::CalcYComponent(pShip->get_Orientation());

            eng::math::CVector2f vVelocity(k_fProjectileSpeed * fX, k_fProjectileSpeed * fY);
#ifdef _DEBUG
            eng::util::DebugTrace(_T("  Proj. Velocity: %6.2f, %6.2f \n"), vVelocity.X, vVelocity.Y);
#endif
            // offset it by 25.f to put it at the tip of the ship
            /// @todo fix hard-coded 25.f
            eng::math::CVector2f vProjCenter(pShip->get_CenterX() + ( 25.f * fX ),
                                             pShip->get_CenterY() + ( 25.f * fY ));

            CProjectile* pProj = new CProjectile(vProjCenter,
                                                 vVelocity,
                                                 static_cast<float>( eng::util::GetCurrentTimeInSeconds() ));


            if (pProj)
            {
                m_rgActors.push_back(pProj); // note - may throw an exception
                bReturn = true;
            }
        }
    }
    return bReturn;
};

//-----------------------------------------------------------------------------------------------
bool CGame::DestroyRandomAsteroid(void)
{
    bool   bReturn    = false;
    size_t nActors    = m_rgActors.size();

    if (nActors == 2)
    {
        auto pAsteroidToDestory = m_rgActors[1];
        m_rgActors.pop_back();

        if (pAsteroidToDestory)
        {
            delete pAsteroidToDestory;
            bReturn = true;
        }
    }
    else if (nActors > 2)
    {
        auto nRandomActor = eng::math::RangedRand(static_cast<size_t>(1), nActors - 1);

        auto pActor = m_rgActors[nActors - 1];
        m_rgActors.pop_back();

        auto pAsteroidToDestroy  = m_rgActors[nRandomActor];
        m_rgActors[nRandomActor] = pActor;

        if (pAsteroidToDestroy)
        {
            delete pAsteroidToDestroy;
            bReturn = true;
        }
    }
    return bReturn;
}

