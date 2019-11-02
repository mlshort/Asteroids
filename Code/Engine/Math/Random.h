/**
 *  @file       Random.h
 *  @brief      CRandom class interface
 *              ... this is a work-in-progress and not currently used ...
 *
 *  @author     Mark L. Short
 *  @date       May 7, 2017
 *
 *
 */

#pragma once

#if !defined(__RANDOM_H__)
#define __RANDOM_H__

namespace eng
{
namespace math
{
    template<class _Ty = int>
    class CRandom
    {

        bool m_bIsInitialized;

    public:
        constexpr CRandom() noexcept;
        ~CRandom() noexcept;

        void Init(void) noexcept;

        // Default int range is [MIN_INT, MAX_INT].  Max value is included.
        _Ty NextInt( void );

        _Ty NextInt( _Ty iMaxVal );

        _Ty NextInt( _Ty iMinVal, _Ty iMaxVal );

        // Default float range is [0.0f, 1.0f).  Max value is excluded.
        float    NextFloat( float fMaxVal = 1.0f );

        float    NextFloat( float fMinVal, float fMaxVal );

        void     SetSeed  ( _Ty iSet );

    };


}
}

#endif