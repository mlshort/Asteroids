/**
 *  @file       Actor2.cpp
 *  @brief      CActor2 class implementation
 *
 *  @author     Mark L. Short
 *  @date       May 7, 2017
 *
 *
 */

#include "targetver.h"  // needs to be 1st header included
#include "Actor2.h"

namespace eng
{


//-----------------------------------------------------------------------------------------------
bool CActor2::IntersectsWith(const CActor2& o) const noexcept
{
    bool bReturn = false;

    if (IsActive() && o.IsActive())
    {
        float fRange = m_fRadius + o.m_fRadius;
        bReturn = ( std::abs(get_CenterX() - o.get_CenterX()) < fRange &&
                    std::abs(get_CenterY() - o.get_CenterY()) < fRange );
#ifdef _DEBUG

//        auto distance = get_Center().CalcDistance(o.get_Center());
//        bool bReturn2 = distance < fRange;

//        if (bReturn != bReturn2)
//        {
//            ::__debugbreak();
//        }
#endif
    }

    return bReturn;
}

} // namespace eng
