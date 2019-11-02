/**
 *  @file       Actor2.h
 *  @brief      CActor2 class interface
 *
 *  @author     Mark L. Short
 *  @date       May 7, 2017
 *
 *
 */
#pragma once

#if !defined(__ACTOR2_H__)
#define __ACTOR2_H__

#ifndef __IRENDERABLE_H__
    #include "Engine/Core/IRenderable.h"
#endif

#ifndef __VECTOR2_H__
    #include "Engine/Math/Vector2.h"
#endif

namespace eng
{

/*
   This form of _declspec can be applied to any class declaration, but should 
   only be applied to pure interface classes, that is classes that will never 
   be instantiated on their own. The _declspec stops the compiler from 
   generating code to initialize the vfptr in the constructor(s) and 
   destructor of the class. In many cases, this removes the only references 
   to the vtable that are associated with the class and, thus, the linker will 
   remove it. Using this form of _declspec can result in a significant 
   reduction in code size.
*/

class __declspec(novtable) CActor2 
    : public IRenderable
{
    bool                  m_bActive;
    math::CVector2f       m_vCenter;     //< Center
    math::CVector2f       m_vVelocity;   //< Linear Velocity
    float                 m_fRadius;     //< Collision Radius

public:
    /// Default Constructor
    constexpr CActor2() noexcept;
    /// Copy Constructor
    constexpr CActor2(const CActor2& o) noexcept;
    /// Conversion Constructor
    constexpr explicit CActor2(const math::CVector2f& vCenter, float fRadius, const math::CVector2f& vVel) noexcept;
    /// Conversion Constructor
    constexpr explicit CActor2(float fCenterX, float fCenterY, float fRadius, float fDeltaX = 0.0, float fDeltaY = 0.0) noexcept;
    /// Default Destructor
    virtual ~CActor2() = default;

    inline    void                        set_Center  (const math::CVector2f& vSet) noexcept;
    constexpr const math::CVector2f&      get_Center  (void) const noexcept;
    inline    void                       incr_Center  (const math::CVector2f& vDelta) noexcept;

    inline    void                        set_CenterX (float fSet) noexcept;
    constexpr float                       get_CenterX (void) const noexcept;

    inline    void                        set_CenterY (float fSet) noexcept;
    constexpr float                       get_CenterY (void) const noexcept;

    inline    void                        set_Velocity(const math::CVector2f& vSet) noexcept;
    constexpr const math::CVector2f&      get_Velocity(void) const noexcept;
    inline    void                       incr_Velocity(const math::CVector2f& vDelta) noexcept;

    inline    void                        set_Radius  (float fSet) noexcept;
    constexpr float                       get_Radius  (void) const noexcept;

    inline    void                        set_Active  (bool bSet = true) noexcept;
    constexpr bool                        IsActive    (void) const noexcept;


    bool                                IntersectsWith(const CActor2& o) const noexcept;

};

//-----------------------------------------------------------------------------------------------
constexpr 
CActor2::CActor2 () noexcept
    : m_bActive   (true),
      m_vCenter   (),
      m_vVelocity (),
      m_fRadius   ()
{
};

//-----------------------------------------------------------------------------------------------
constexpr 
CActor2::CActor2 (const CActor2& o) noexcept
    : m_bActive   (o.m_bActive),
      m_vCenter   (o.m_vCenter),
      m_vVelocity (o.m_vVelocity),
      m_fRadius   (o.m_fRadius)
{
};

//-----------------------------------------------------------------------------------------------
constexpr 
CActor2::CActor2 (const math::CVector2f& vCenter, float fRadius, const math::CVector2f& vVel) noexcept
    : m_bActive   (true),
      m_vCenter   (vCenter),
      m_vVelocity (vVel),
      m_fRadius   (fRadius)
{
};

//-----------------------------------------------------------------------------------------------
constexpr 
CActor2::CActor2 (float fCenterX, float fCenterY, float fRadius,
                  float fDeltaX /* = 0.0 */, float fDeltaY /* = 0.0 */) noexcept
    : m_bActive   (true),
      m_vCenter   (fCenterX, fCenterY),
      m_vVelocity (fDeltaX, fDeltaY),
      m_fRadius   (fRadius)
{
};

constexpr const math::CVector2f& 
CActor2::get_Center (void) const noexcept
{ return m_vCenter; };

void
CActor2::set_Center (const math::CVector2f& vSet) noexcept
{ m_vCenter = vSet; };

void
CActor2::incr_Center (const math::CVector2f& vDelta) noexcept
{ m_vCenter += vDelta; };

void
CActor2::set_CenterX(float fSet) noexcept
{ m_vCenter.X = fSet; };

constexpr float
CActor2::get_CenterX(void) const noexcept
{ return m_vCenter.X; };

void
CActor2::set_CenterY(float fSet) noexcept
{ m_vCenter.Y = fSet; };

constexpr float
CActor2::get_CenterY(void) const noexcept
{ return m_vCenter.Y; };

void
CActor2::set_Velocity(const math::CVector2f& vSet) noexcept
{ m_vVelocity = vSet; };

constexpr const math::CVector2f&
CActor2::get_Velocity(void) const noexcept
{ return m_vVelocity; };

void
CActor2::incr_Velocity(const math::CVector2f& vDelta) noexcept
{ m_vVelocity += vDelta; };

void
CActor2::set_Radius  (float fSet) noexcept
{ m_fRadius = fSet; };

constexpr float
CActor2::get_Radius  (void) const noexcept
{ return m_fRadius; };

constexpr bool
CActor2::IsActive    (void) const noexcept
{ return m_bActive; };

void
CActor2::set_Active  (bool bSet /*= true*/) noexcept
{ m_bActive = bSet; };

} // namespace eng

#endif

