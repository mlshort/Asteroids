/**
 *  @file       Asteroid.cpp
 *  @brief      CAsteroid class implementation
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

#include "Asteroid.h"

const eng::ColorRGBA k_clrAsteroidDefault = eng::RGBA_WHITE;

//-----------------------------------------------------------------------------------------------
CAsteroid::CAsteroid(ASTEROID_TYPE type) noexcept
    : eng::CActor2(),
      m_Type(type),
      m_fAngularVelocity(0.0),
      m_degOrientation(0.0),
      m_rgVertices()
{
};

//-----------------------------------------------------------------------------------------------
CAsteroid::CAsteroid(const CAsteroid& o)
    : eng::CActor2(o),
      m_Type(o.m_Type),
      m_fAngularVelocity(o.m_fAngularVelocity),
      m_degOrientation(o.m_degOrientation),
      m_rgVertices(o.m_rgVertices)
{
};

//-----------------------------------------------------------------------------------------------
CAsteroid::CAsteroid(CAsteroid&& o) noexcept
    : eng::CActor2(o),
      m_Type(o.m_Type),
      m_fAngularVelocity(o.m_fAngularVelocity),
      m_degOrientation(o.m_degOrientation),
      m_rgVertices(o.m_rgVertices)
{
};
//-----------------------------------------------------------------------------------------------
CAsteroid::CAsteroid(ASTEROID_TYPE type, const eng::math::CVector2f& vCenter, float fRadius, 
                     const eng::math::CVector2f& vVel, float fAngularVelocity) noexcept
    : eng::CActor2(vCenter, fRadius, vVel),
      m_Type(type),
      m_fAngularVelocity(fAngularVelocity),
      m_degOrientation(0.0),
      m_rgVertices()
{ 
};

//-----------------------------------------------------------------------------------------------
CAsteroid::~CAsteroid()
{
};

//-----------------------------------------------------------------------------------------------
size_t CAsteroid::AddVertex(const eng::math::CVector2f& vNewVertex) noexcept
{
    m_rgVertices.push_back(vNewVertex); // note - may throw an exception
    return m_rgVertices.size();
};

//-----------------------------------------------------------------------------------------------
void CAsteroid::Render(void) const
{
    if (IsActive())
    {
        eng::g_theRdr.SetLineWidth(k_fAsteroidLineWidth);
        eng::g_theRdr.SetColor(k_clrAsteroidDefault);

        eng::g_theRdr.PushView();

        eng::g_theRdr.TranslateView(get_Center());
        eng::g_theRdr.DrawPolygon(m_rgVertices, get_Orientation());

        eng::g_theRdr.PopView();
    }
};

//-----------------------------------------------------------------------------------------------
void CAsteroid::Update(float fDeltaTime)
{
    incr_Center     (get_Velocity() * fDeltaTime);
    incr_Orientation(get_AngularVelocity() * fDeltaTime);
};

//-----------------------------------------------------------------------------------------------
void CAsteroid::InitIrregularAsteroid(size_t nNumVertices) noexcept
{
    const float   fDeltaRadius      = get_Radius() / 3.f; // used to generate a random radius
    const RADIANS fRadiansPerVertex = static_cast<float>(eng::math::RADIANS_PER_CIRCLE / nNumVertices);

    for (RADIANS fRadians = 0.0; fRadians < eng::math::RADIANS_PER_CIRCLE; fRadians += fRadiansPerVertex)
    {
        float fVertexRadius = static_cast<float>( eng::math::RangedRand(get_Radius() - fDeltaRadius, get_Radius() + fDeltaRadius) );
        float x = /* get_Center().X + */ ( fVertexRadius * std::cos(fRadians) );
        float y = /* get_Center().Y + */ ( fVertexRadius * std::sin(fRadians) );
        AddVertex( eng::math::CVector2f( x, y) );
    }
};




//-----------------------------------------------------------------------------------------------
CSmallAsteroid::CSmallAsteroid (const eng::math::CVector2f& vCenter, const eng::math::CVector2f& vVel, float fAngularVelocity) noexcept
    : CAsteroid (AST_SMALL, vCenter, k_fAsteroidRadiusSmall, vVel, fAngularVelocity)
{
};

//-----------------------------------------------------------------------------------------------
CMediumAsteroid::CMediumAsteroid (const eng::math::CVector2f& vCenter, const eng::math::CVector2f& vVel, float fAngularVelocity) noexcept
    : CAsteroid (AST_MEDIUM, vCenter, k_fAsteroidRadiusMedium, vVel, fAngularVelocity)
{
};

//-----------------------------------------------------------------------------------------------
CLargeAsteroid::CLargeAsteroid (const eng::math::CVector2f& vCenter, const eng::math::CVector2f& vVel, float fAngularVelocity) noexcept
    : CAsteroid (AST_LARGE, vCenter, k_fAsteroidRadiusLarge, vVel, fAngularVelocity)
{
};

