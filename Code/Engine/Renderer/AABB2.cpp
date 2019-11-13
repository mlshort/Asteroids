/**
 *  @file       AABB2.cpp
 *  @brief      CAABB2 class implementation
 *
 *  @author     Mark L. Short
 *  @date       May 7, 2017
 *
 *
 */

#define WIN32_LEAN_AND_MEAN
#include "targetver.h"  // this needs to be the 1st header included
#include <limits>

#include "AABB2.h"

namespace eng
{

constexpr CAABB2::CAABB2() noexcept
    : m_vMin(0.0, 0.0),
      m_vMax(std::numeric_limits<float>::max(), std::numeric_limits<float>::max() )
{
};

constexpr CAABB2::CAABB2(const CAABB2& o) noexcept
    : m_vMin( o.m_vMin ),
      m_vMax( o.m_vMax )
{
};

constexpr CAABB2::CAABB2(const math::CVector2f& vMin, const math::CVector2f& vMax) noexcept
    : m_vMin( vMin ),
      m_vMax( vMax )
{
};

constexpr CAABB2::CAABB2(const math::CVector2i& vMin, const math::CVector2i& vMax) noexcept
    : m_vMin(static_cast<float>(vMin.X), static_cast<float>(vMin.Y)),
      m_vMax(static_cast<float>(vMax.X), static_cast<float>(vMax.Y))
{
};

constexpr CAABB2::CAABB2(const math::CVector2f& vMin, float fWidth, float fHeight) noexcept
    : m_vMin(vMin),
      m_vMax(vMin.X + fWidth, vMin.Y + fHeight)
{
};

constexpr CAABB2::CAABB2(const math::CVector2i& vMin, int iWidth, int iHeight) noexcept
    : m_vMin(static_cast<float>(vMin.X), static_cast<float>(vMin.Y)),
      m_vMax(static_cast<float>(vMin.X + iWidth), static_cast<float>(vMin.Y + iHeight))
{
};


}
