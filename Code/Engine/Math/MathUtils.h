/**
 *  @file       MathUtils.h
 *  @brief      Math utility method declarations
 *
 *  @author     Mark L. Short
 *  @date       May 7, 2017
 *
 *
 */

#pragma once

#if !defined(__MATH_UTILS_H__)
#define __MATH_UTILS_H__

#ifndef _CSTDLIB_
    #include <cstdlib>
#endif

#ifndef _CMATH_
    #include <cmath>
#endif

#ifndef _ALGORITHM_
    #include <algorithm>
#endif

namespace eng
{
namespace math
{

// Note:
// 1 Radian = (180 / PI ) degrees

constexpr const double PI                 = static_cast<double>(3.1415926535897932384626433832795);
constexpr const double TWO_PI             = static_cast<double>(2.0 * math::PI);
constexpr const double DEGREES_PER_RADIAN = static_cast<double>(180.0 / math::PI); // effectively the same as ( 360 / 2 PI )
constexpr const double RADIANS_PER_DEGREE = static_cast<double>(math::PI / 180.0);
constexpr const double RADIANS_PER_CIRCLE = static_cast<double>(360.0 / math::DEGREES_PER_RADIAN);  // 2 PI


/**
 *
 * @brief a 'constexpr' version of the std::abs function
 *
 * @param [in] Arg
 *
 * @retval _Ty  absolute value of Arg
 *
 * @note  The behavior is undefined if the result cannot be represented by the return type. 
 *
 */
template <class _Ty>
constexpr _Ty Abs(const _Ty Arg) noexcept
{
    static_assert(std::is_arithmetic<_Ty>::value,
                  "invalid arithmetic template type for Abs<_Ty>");

    return Arg >= _Ty() ? Arg : -Arg;
};

/**
 *  @brief a 'constexpr' convenience function that returns the delta
 *
 *  @param [in] Arg1
 *  @param [in] Arg2
 *
 *  @retval _Ty  containing the value Arg1 - Arg2
 *
 *  @note seemingly obvious and unnecessary template function, but it is used to
 *        make various constexpr template functions a bit easier to code and read
 *
 */
template <class _Ty>
constexpr _Ty Delta(const _Ty& Arg1, const _Ty& Arg2) noexcept
{
    return (Arg1 - Arg2);
};

template <class _Ty>
constexpr _Ty AbsDelta(const _Ty& Arg1, const _Ty& Arg2) noexcept
{
    return (math::Abs(Arg1 - Arg2));
};

template <class _Ty>
constexpr _Ty CalcDistanceSquared(const _Ty& xPt1, const _Ty& yPt1, const _Ty& xPt2, const _Ty& yPt2) noexcept
{
    return ((math::Delta(xPt1, xPt2) * math::Delta(xPt1, xPt2)) +
            (math::Delta(yPt1, yPt2) * math::Delta(yPt1, yPt2)));
};

template <class _Ty>
constexpr _Ty CalcDistance(const _Ty& xPt1, const _Ty& yPt1, const _Ty& xPt2, const _Ty& yPt2) noexcept
{
    return static_cast<_Ty>(std::sqrt(math::CalcDistanceSquared(xPt1, yPt1, xPt2, yPt2)));
};

template <class _Ty>
constexpr _Ty RadiansToDegrees(const _Ty& fRadians) noexcept
{
    return static_cast<_Ty>(fRadians * math::DEGREES_PER_RADIAN);
};

template <class _Ty>
constexpr _Ty DegreesToRadians(const _Ty& fDegrees) noexcept
{
    return static_cast<_Ty>(fDegrees * math::RADIANS_PER_DEGREE);
};

/**
 *
 * @TODO - change from rand()
 *
 */
template <class _Ty>
inline _Ty RangedRand( const _Ty& fRangeMin, const _Ty& fRangeMax )
{
   // Generate random numbers in the half-closed interval
   // [fRangeMin, fRangeMax). In other words,
   // fRangeMin <= random number < fRangeMax

   return static_cast<_Ty>(static_cast<_Ty>(std::rand()) /
                           static_cast<_Ty>(RAND_MAX + 1) * (fRangeMax - fRangeMin) + fRangeMin);
};


template <class _Ty>
constexpr _Ty Clamp( const _Ty& fValue, const _Ty& fMin, const _Ty& fMax )
{
    return std::max(fMin, std::min(fMax, fValue));
};

template <class _Ty>
inline _Ty CalcXComponent(const _Ty& fDegrees) noexcept
{
    return std::cos(DegreesToRadians(fDegrees));
};

template <class _Ty>
inline _Ty CalcYComponent(const _Ty& fDegrees) noexcept
{
    return std::sin(DegreesToRadians(fDegrees));
};

/**
 *  @retval _Ty containing the angle (in Radians) from Origin to Target
 */
template <class _Ty>
inline _Ty CalcAngleToTarget(const _Ty& fOrigX, const _Ty& fOrigY, const _Ty& fTargetX, const _Ty& fTargetY) noexcept
{
    auto fDeltaX = fOrigX - fTargetX;
    auto fDeltaY = fOrigY - fTargetY;

    return std::atan2( fDeltaY, fDeltaX );
};

/**
 * 
 * @brief calculates floating point equalivency within a tolerance
 *
 * @param [in] fArg1
 *
 * @param [in] fArg2
 *
 * @parem [in] iEpsilonFactor
 *
 * @retval true   if fArg1 is close enough to fArg2
 * @retval false  if | fArg1 - fArg2 | < (iEpsilonFactor * epsilon())
 *
 */
template<class _Ty, class _EF = int>
constexpr bool fEqual(const _Ty& fArg1, const _Ty& fArg2, _EF iEpsilonFactor) noexcept
{

 //       _Ty nDelta = std::abs(fArg1 - fArg2);
 //       (iEpsilonFactor * smallest effective increment from 1.0)
 //       _Ty nTolerance = iEpsilonFactor * std::numeric_limits<_Ty>::epsilon();
 //       return (nDelta <= nTolerance);

// following only makes sense if working with floating point numbers
    static_assert(std::is_float<_Ty>::value,
                  "fEqual only useful for floating point values");

// had to rewrite in order to declare function as 'constexpr'
    return (fArg1 == fArg2) ? true : (math::AbsDelta(fArg1, fArg2) <=
                              iEpsilonFactor * std::numeric_limits<_Ty>::epsilon());

};

/*
  @todo implement a 'RangeMap' like method

  i.e. [3 to 18] -> [0.5 to 2.5]
  1. Input Range Start, Input Range End : Subtract Input Start, [0 to 15]
  2. Divide by Input Range End, [0 to 1.0]
float RangeMap(float fValue, float fInputMin, float fInputMax, float fOutMin, float fOutMax);
*/

}
}

#endif