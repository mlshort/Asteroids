/**
 *  @file       Random.cpp
 *  @brief      CRandom class implementation
 *
 *  @author     Mark L. Short
 *  @date       May 7, 2017
 *
 *
 */

/*
 *
 * Following is a work in progress... is not currently used
 *
 */

#include "targetver.h"  // needs to be the 1st header included

#include <random>
#include <chrono>
#include <functional>

#include "Random.h"

namespace eng
{
namespace math
{

std::random_device  g_rd;
std::mt19937        g_mtEngine(g_rd());

template<class _Ty = int>
constexpr CRandom<_Ty>::CRandom() noexcept
    : m_bIsInitialized(false)
{
};

template<class _Ty>
CRandom<_Ty>::~CRandom() noexcept
{
}

template<class _Ty>
void CRandom<_Ty>::Init(void) noexcept
{
    if (!m_bIsInitialized)
    {
 //       auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();

        m_bIsInitialized = true;
    }
}

template<class _Ty>
_Ty CRandom<_Ty>::NextInt(void)
{
    return std::uniform_int_distribution<_Ty>(0x80000000, 0x7FFFFFFF)(g_mtEngine);
}

template<class _Ty>
_Ty CRandom<_Ty>::NextInt(_Ty iMaxVal)
{
    return std::uniform_int_distribution<_Ty>(0, iMaxVal)(g_mtEngine);
}

template<class _Ty>
_Ty CRandom<_Ty>::NextInt(_Ty MinVal, _Ty MaxVal)
{
    return std::uniform_int_distribution<_Ty>(MinVal, MaxVal)(g_mtEngine);
}

// Default float range is [0.0f, 1.0f).  Max value is excluded.
template<class _Ty>
float CRandom<_Ty>::NextFloat(float fMaxVal /*= 1.0f*/)
{
    return std::uniform_real_distribution<float>(0.0f, fMaxVal)(g_mtEngine);
}

template<class _Ty>
float CRandom<_Ty>::NextFloat(float MinVal, float MaxVal)
{
    return std::uniform_real_distribution<float>(MinVal, MaxVal)(g_mtEngine);
}

template<class _Ty>
void CRandom<_Ty>::SetSeed(_Ty Seed)
{
    g_mtEngine.seed(Seed);
}

/*


 */
template<class _Ty = int>
_Ty getRand(const _Ty& MinVal, const _Ty& MaxVal)
{
    static std::random_device randDev;
    static std::mt19937 twister(randDev());
    static std::uniform_int_distribution<_Ty> dist;

    dist.param(std::uniform_int_distribution<_Ty>::param_type(MinVal, MaxVal));
    return dist(twister);
};

}
}
