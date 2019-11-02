/**
 *  @file       AABB2.h
 *  @brief      CAABB2 class interface
 *
 *  @author     Mark L. Short
 *  @date       May 7, 2017
 *
 */

#pragma once

#if !defined(__AABB2_H__)
#define __AABB2_H__

#ifndef __VECTOR2_H__
    #include "Engine/Math/Vector2.h"
#endif


namespace eng
{

class CAABB2
{
    math::CVector2f m_vMin;
    math::CVector2f m_vMax;
public:
    /// Default constructor
    constexpr CAABB2() noexcept;
    /// Copy constructor
    constexpr CAABB2(const CAABB2& o) noexcept;
    /// Conversion constructor
    explicit constexpr CAABB2(const math::CVector2f& vMin, const math::CVector2f& vMax) noexcept;
    /// Conversion constructor
    explicit constexpr CAABB2(const math::CVector2i& vMin, const math::CVector2i& vMax) noexcept;
    /// Conversion constructor
    explicit constexpr CAABB2(const math::CVector2f& vMin, float fWidth, float fHeight) noexcept;
    /// Conversion constructor
    explicit constexpr CAABB2(const math::CVector2i& vMin, int iWidth, int iHeight) noexcept;
    /// Default destructor
    ~CAABB2() noexcept;

    constexpr const math::CVector2f& get_Min   (void) const noexcept;
    constexpr const math::CVector2f& get_Max   (void) const noexcept;
    constexpr math::CVector2f        CalcCenter(void) const noexcept;
};

 constexpr const math::CVector2f& 
 CAABB2::get_Min(void) const noexcept
 { return m_vMin; };

 constexpr const math::CVector2f& 
 CAABB2::get_Max(void) const noexcept
 { return m_vMax; };

 constexpr math::CVector2f
CAABB2::CalcCenter(void) const noexcept
 { return math::CVector2f( (m_vMin.X + m_vMax.X) / 2, (m_vMin.Y + m_vMax.Y) / 2); };

} // namespace eng

#endif

