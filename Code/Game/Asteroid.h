/**
 *  @file       Asteroid.h
 *  @brief      CAsteroid class interface
 *
 *  @author     Mark L. Short
 *  @date       May 7, 2017
 *
 *
 */

#pragma once

#if !defined(__ASTEROID_H__)
#define __ASTEROID_H__

#ifndef __ACTOR2_H__
    #include "Engine/Core/Actor2.h"
#endif

#ifndef _VECTOR_
    #include <vector>
#endif

enum ASTEROID_TYPE 
{ 
  AST_SMALL, 
  AST_MEDIUM, 
  AST_LARGE,
  AST_INVALID
};

class CAsteroid :
    public eng::CActor2
{
    ASTEROID_TYPE                     m_Type;
    float                             m_fAngularVelocity;   // in degrees per time segment
    DEGREES                           m_degOrientation;     // in degrees
    std::vector<eng::math::CVector2f> m_rgVertices;

public:
    /// Default Constructor
    CAsteroid(ASTEROID_TYPE type = AST_INVALID) noexcept;
    /// Copy Constructor
    CAsteroid(const CAsteroid& o);
    /// Move Constructor
    CAsteroid(CAsteroid&& o) noexcept;
    /// Conversion Constructor
    explicit CAsteroid(ASTEROID_TYPE type, const eng::math::CVector2f& vCenter, float fRadius, 
                       const eng::math::CVector2f& vVel, float fAngularVelocity = 0.0) noexcept;
    /// Default Destructor
    virtual ~CAsteroid() noexcept;

    inline void              set_AngularVelocity  (float fVelocity) noexcept
    { m_fAngularVelocity = fVelocity; };

    constexpr ASTEROID_TYPE  get_Type             (void) const noexcept
    { return m_Type; };

    constexpr float          get_AngularVelocity  (void) const noexcept
    { return m_fAngularVelocity; };

    constexpr DEGREES        get_Orientation      (void) const noexcept
    { return m_degOrientation; };

    inline void              incr_Orientation     (DEGREES degDelta) noexcept
    { m_degOrientation += degDelta; };


    void           InitIrregularAsteroid(size_t nNumVertices) noexcept;

// IRenderable 
    void   Render               (void) const override;
    void   Update               (float fDeltaTime) override;

private:
    size_t         AddVertex            (const eng::math::CVector2f& vNewVertex) noexcept;

};

class CLargeAsteroid : public CAsteroid
{
public:
    /// Default Constructor
    CLargeAsteroid() noexcept;
    /// Conversion Constructor
    explicit CLargeAsteroid(const eng::math::CVector2f& vCenter, const eng::math::CVector2f& vVel, float fAngularVelocity = 0.0) noexcept;
    /// Default Destructor
    virtual ~CLargeAsteroid () = default;
};

class CMediumAsteroid : public CAsteroid
{
public:
    /// Default Constructor
    CMediumAsteroid() noexcept;
    /// Conversion Constructor
    explicit CMediumAsteroid(const eng::math::CVector2f& vCenter, const eng::math::CVector2f& vVel, float fAngularVelocity = 0.0) noexcept;
    /// Default Destructor
    virtual ~CMediumAsteroid () = default;
};

class CSmallAsteroid : public CAsteroid
{
public:
    /// Default Constructor
    CSmallAsteroid () noexcept;
    /// Conversion Constructor
    explicit CSmallAsteroid (const eng::math::CVector2f& vCenter, const eng::math::CVector2f& vVel, float fAngularVelocity = 0.0) noexcept;
    /// Default Destructor
    virtual ~CSmallAsteroid () = default;
};



#endif