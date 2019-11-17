/**
 *  @file       Vector2.h
 *  @brief      TVector2 template class implementation
 *
 *  @author     Mark L. Short
 *  @date       May 7, 2017
 *
 *
 */
#pragma once

#if !defined(__VECTOR2_H__)
#define __VECTOR2_H__

/**
 *  TVector2 Implementation Notes:
 *
 *  1. TVector2 is implemented as a template, such that the user has the final
 *  say in terms of dictating the underlying Cartesian X & Y coordinate type.
 *  The only restrictions placed were that the parameterized type be an
 *  arithmetic type (with valid +,-,*,/ operators).
 *
 *  2. Regarding "Originality of Work", the topic of 2D vectors has been
 *  amply covered in numerous texts and library implementations.  To my
 *  knowledge, there does not exist an implementation exactly as follows...
 */

#ifndef _TYPE_TRAITS_
    #include <type_traits>
#endif

#ifndef __MATH_UTILS_H__
    #include "MathUtils.h"
#endif

namespace eng
{
namespace math
{

/**
 * @brief Provides basic 2-dimensional vector operations.
 *
 * @sa https://en.wikipedia.org/wiki/Two-dimensional_space
 */
template <class _Ty>
struct TVector2
{
    typedef typename _Ty type_t;

    _Ty X; ///< X coordinate value
    _Ty Y; ///< Y coordinate value

    static_assert(std::is_arithmetic<_Ty>::value,
                  "invalid template argument for TVector2");

    /// Default constructor
    constexpr TVector2(void) noexcept
        : X(),
          Y()
    { };

    /// non-converting initialization constructor
    constexpr explicit TVector2( _Ty fX, _Ty fY ) noexcept
        : X( fX ),
          Y( fY )
    { };

    /// copy constructor
    constexpr TVector2( const TVector2<_Ty>& o ) noexcept
        : X( o.X ),
          Y( o.Y )
    { };

    /// move constructor
    constexpr TVector2(TVector2<_Ty>&& o) noexcept
        : X(o.X),
          Y(o.Y)
    { };

    /// Default destructor
    ~TVector2() = default;

    /// Assignment operator
    inline TVector2<_Ty>& operator= ( const TVector2<_Ty>& rhs ) noexcept
    {
        if (this != &rhs)
        {
            X = rhs.X;
            Y = rhs.Y;
        }
        return *this;
    };

    inline void Init(_Ty fX, _Ty fY) noexcept
    {
        X = fX;
        Y = fY;
    };

/**
 * @brief calculates the component sum of this vector and another
 *
 * @param [in] opr           the other vector operand
 *
 * @retval TVector2<_Ty>     a new vector object containing the resultant
 *                           component sum
 */
    constexpr TVector2<_Ty> operator + ( const TVector2<_Ty>& opr ) const noexcept
    {
        return TVector2<_Ty>( X + opr.X, Y + opr.Y );
    };

/**
 * @brief calculates the component difference between this vector and another
 *
 * @param [in] opr          the other vector operand
 *
 * @retval TVector2<_Ty>    a new vector object containing the resultant
 *                          difference
 */
    constexpr TVector2<_Ty> operator - ( const TVector2<_Ty>& opr ) const noexcept
    {
        return TVector2<_Ty>( X - opr.X, Y - opr.Y );
    };

/**
 * @brief calculates the component difference between this vector and scalar
 *
 * @param [in] kScalar      scalar decrementer
 *
 * @retval TVector2<_Ty>    a new vector object containing the resultant
 *                          difference
 */
    template <class _TScalar>
    constexpr TVector2<_Ty> operator - ( _TScalar kScalar ) const noexcept
    {
        return TVector2<_Ty>( X - kScalar, Y - kScalar );
    };

/**
 * @brief calculates the component sum of this vector and scalar
 *
 * @param [in] kScalar      scalar add
 *
 * @retval TVector2<_Ty>    a new vector object containing the resultant
 *                          sum
 */
    template <class _TScalar>
    constexpr TVector2<_Ty> operator + ( _TScalar kScalar ) const noexcept
    {
        return TVector2<_Ty>( X + kScalar, Y + kScalar );
    };

/**
 * @brief negates the vector
 *
 * @retval TVector2<_Ty>    a new vector object containing the resultant
 *                          negation
 */
    constexpr TVector2<_Ty> operator - ( void ) const noexcept
    {
        return TVector2<_Ty>( -X, -Y );
    };

/**
 * @brief calculates the product of this vector and a scalar
 *
 * @param [in] kScalar      scalar multiplier
 *
 * @retval TVector2<_Ty>    a new vector object containing the resultant
 *                          product
 */
    template <class _TScalar>
    constexpr TVector2<_Ty> operator * ( _TScalar kScalar ) const noexcept
    {
        static_assert(std::is_scalar<_TScalar>::value,
                      "invalid scalar type for TVector2");
        return TVector2<_Ty>( static_cast<_Ty>(X * kScalar), static_cast<_Ty>(Y * kScalar) );
    };

/**
 * @brief increments the components of this vector by those of another
 *
 * @param [in] opr          right hand side operand
 *
 * @retval TVector2<_Ty>&   reference to this vector
 */
    inline TVector2<_Ty>& operator += ( const TVector2<_Ty>& opr ) noexcept
    {
        X += opr.X;
        Y += opr.Y;

        return *this;
    };

/**
 * @brief decrements the components of this vector by those of another
 *
 * @param [in] opr          right hand side operand
 *
 * @retval TVector2<_Ty>&   reference to this resultant vector
 *
 */
    inline TVector2<_Ty>& operator -= ( const TVector2<_Ty>& opr ) noexcept
    {
        X -= opr.X;
        Y -= opr.Y;

        return *this;
    };

/**
 * @brief divides the components of this vector by those of another
 *
 * @param [in] opr          right hand side operand
 *
 * @retval TVector2<_Ty>&   reference to this resultant vector instance
 *                          whose components are the quotient of the division
 *                          of each component by each corresponding component
 *                          of opr
 */
    inline TVector2<_Ty>& operator /= (const TVector2<_Ty>& opr ) noexcept
    {
        X /= (opr.X != _Ty() ? opr.X : _Ty(1) ); // don't allow divide by 0
        Y /= (opr.Y != _Ty() ? opr.Y : _Ty(1) ); // don't allow divide by 0

        return *this;
    };

/**
 * @brief divides the components of this vector by a scalar
 *
 * @param [in] kScalar      scalar divisor
 *
 * @retval TVector2<_Ty>&   reference to this resultant vector
 */
    template <class _TScalar>
    inline TVector2<_Ty>& operator / ( _TScalar kScalar ) noexcept
    {
        static_assert(std::is_scalar<_TScalar>::value,
                      "template argument != scalar for TVector2");
        kScalar = (kScalar == _TScalar()) ? 1 : kScalar;
        X /= kScalar;
        Y /= kScalar;

        return *this;
    };

/**
 * @brief scales the components of this vector by a scalar factor
 *
 * @param [in] kScalar      scalar
 *
 * @retval TVector2<_Ty>&   reference to this resultant vector
 */
    template <class _TScalar>
    inline TVector2<_Ty>& operator *= ( _TScalar kScalar ) noexcept
    {
        X *= kScalar;
        Y *= kScalar;

        return *this;
    };

/**
 * @brief scales the components of this vector by a scalar add
 *
 * @param [in] kScalar      scalar to add
 *
 * @retval TVector2<_Ty>&   reference to this resultant vector
 *
 */
    template<class _TScalar>
    inline TVector2<_Ty>& operator += ( _TScalar kScalar ) noexcept
    {
        X += kScalar;
        Y += kScalar;

        return *this;
    };

/**
 * @brief scales the components of this vector by a scalar subtract
 *
 * @param [in] kScalar      scalar to subtract
 *
 * @retval TVector2<_Ty>&   reference to this resultant vector
 *
 */
    template<class _TScalar>
    inline TVector2<_Ty>& operator -= ( _TScalar kScalar ) noexcept
    {
        X -= kScalar;
        Y -= kScalar;

        return *this;
    };

/**
 * @brief calculates the Dot Product of this vector
 *        against another
 *
 * @param [in] opr          right hand side operand
 *
 * @retval _Ty              scalar result
 *
 */
    constexpr _Ty CalcDotProduct ( const TVector2<_Ty>& opr ) const noexcept
    {
        return (X * opr.X) + (Y * opr.Y);
    };

/**
 * @brief calculates the component distance (squared) of this vector
 *        against another
 *
 * @param [in] opr          other vector
 *
 * @retval _Ty              scalar result
 */
    constexpr _Ty CalcDistanceSquared ( const TVector2<_Ty>& opr ) const noexcept
    {
        return math::CalcDistanceSquared( X, Y, opr.X, opr.Y );
    };

 /**
  * @brief calculates the component distance of this vector
  *        against another
  *
  * @param [in] opr          other vector
  *
  * @retval _Ty              scaler result
  */
    inline _Ty CalcDistance ( const TVector2<_Ty>& opr ) const noexcept
    {
        return math::CalcDistance( X, Y, opr.X, opr.Y );
    };

/**
 * @brief calculates the magnitude of this vector, which is
 *        the component distance between this vector and
 *        the origin
 *
 * @retval _Ty
 *
 */
    inline _Ty CalcMagnitude ( void ) const noexcept
    {
        return math::CalcDistance( X, Y, _Ty(), _Ty() );
    };

/**
 * @brief calculates the angle of this vector, in Radians
 *
 * @retval _Ty
 *
 */
   inline _Ty CalcRadianAngle (void) const noexcept
   {
       return std::atan2(Y, X);
   };

/**
 * @brief calculates the angle of this vector, in Degrees
 *
 * @retval _Ty
 *
 */
   inline _Ty CalcDegreeAngle (void) const noexcept
   {
       return math::RadiansToDegrees(std::atan2(Y, X));
   };
/**
 * @brief Clamps the components of this vector to a specified minimum and maximum range
 *
 * @param [in] vMin
 * @param [in] vMax
 *
 * @retval TVector2<_Ty>    a vector whose components are clamped to the
 *                          specified minimum and maximum values
 */
    constexpr TVector2<_Ty> Clamp( const TVector2<_Ty>& vMin, const TVector2<_Ty>& vMax ) const noexcept
    {
        TVector2<_Ty> vResult;

        vResult.X = std::min(std::max(X, vMin.X), vMax.X);
        vResult.Y = std::min(std::max(Y, vMin.Y), vMax.Y);

        return vResult;
    };
/**
 * @brief  Computes the floor of each component of this vector
 *
 * @retval TVector2<_Ty>    a vector whose components are the floor of the
 *                          components of this vector
 */
    inline TVector2<_Ty> Floor( void ) const noexcept
    {
        TVector2<_Ty> vResult(std::floor(X), std::floor(Y));

        return vResult;
    };


/**
 * @brief  Computes the absolute value of each component of this vector
 *
 * @retval TVector2<_Ty>    a vector whose components are the absolute value of the
 *                          corresponding components of this vector
 */
    constexpr TVector2<_Ty> Abs( void ) const noexcept
    {
        TVector2<_Ty> vResult(math::Abs(X), math::Abs(Y));

        return vResult;
    };

/**
 * @brief  Computes the per-component reciprocal of this vector
 *
 * @retval TVector2<_Ty>    a vector whose components are the reciprocal of the corresponding
 *                          component of this vector
 */
    constexpr TVector2<_Ty> Reciprocal(void) const noexcept
    {
        TVector2<_Ty> vResult( X ? _Ty(1.0) / X : _Ty(), Y ? _Ty(1.0) / Y : _Ty() );

        return vResult;
    };

/**
 * @brief  Computes a normal of this vector whose magnitude is 1,
 *         but the direction remains unchanged.
 *
 * @retval TVector2<_Ty>    a normalized version of this vector
 */
    inline TVector2<_Ty> Normal(void) const noexcept
    {
        _Ty fDistanceSquared = CalcDistanceSquared();
        // check to see if this vector is already normalized or invalid
        if (fDistanceSquared == _Ty(1.0) || fDistanceSquared == _Ty() )
        {
            return *this;
        }
        else
        {
            _Ty fInverseMagnitude = _Ty(1.0) / std::sqrt(fDistanceSquared);
            TVector2<_Ty> vResult( X * fInverseMagnitude, Y * fInverseMagnitude );
            return vResult;
        }
    };

/**
 * @brief  Rotates this vector
 *
 * @param  [in] fRadians
 *
 * @retval TVector2<_Ty>&    a reference to this vector after
 *                           the rotation operation
 */
    inline TVector2<_Ty>& Rotate(_Ty fRadians) noexcept
    {
       _Ty CosTheta = std::cos(fRadians);
       _Ty SinTheta = std::sin(fRadians);

       _Ty newX = X * CosTheta - Y * SinTheta;
       _Ty newY = X * SinTheta + Y * CosTheta;

       X = newX;
       Y = newY;

       return *this;
    };

};

/**
 *
 * @brief creates a 2d vector given a direction and magnitude 
 *        with additional sanity checking for initial values
 *
 * @param [in] nMagnitude    magnitude
 * @param [in] degDir        direction in degrees
 *
 * @retval TVector2<_Ty>   the created vector
 */
template <typename _Ty,
         class = typename std::enable_if< std::is_floating_point< _Ty >::value, void >::type >
TVector2<_Ty> CreateVector2(_Ty nMagnitude, _Ty degDir) noexcept
{
    _Ty X = math::CalcXComponent(degDir);
    if (math::fEqual(X, _Ty(), 2))
        X = _Ty();

    _Ty Y = math::CalcYComponent(degDir);
    if (math::fEqual(Y, _Ty(), 2))
        Y = _Ty();

    TVector2<_Ty> vForce(X * nMagnitude, Y * nMagnitude);

    return vForce;
};

// common floating point vector2 type definitions
typedef typename math::TVector2<float>       CVector2f;
typedef typename math::TVector2<double>      CVector2d;
typedef typename math::TVector2<long double> CVector2ld;
// int based vector2 type definition
typedef typename math::TVector2<int>         CVector2i;

} // namespace math

} // namespace eng

#endif
