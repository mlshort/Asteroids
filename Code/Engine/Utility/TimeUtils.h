/**
 *  @file       TimeUtils.h
 *  @brief      A simple high-precision time utility function for Windows
 *
 *  @author     Mark L. Short
 *  @date       May 7, 2017
 *
 *
 * <b>Cite:</b>
 *
 * @sa https://msdn.microsoft.com/en-us/library/windows/desktop/dn553408(v=vs.85).aspx
 *
 */

#pragma once

#if !defined(__TIME_UTILS_H__)
#define __TIME_UTILS_H__

namespace eng
{
namespace util
{

//-----------------------------------------------------------------------------------------------
double GetCurrentTimeInSeconds(void) noexcept;

}
}

#endif
