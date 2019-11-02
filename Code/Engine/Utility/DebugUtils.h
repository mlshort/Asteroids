/**
 *  @file       DebugUtils.h
 *  @brief      Debugging and utility method declarations
 *
 *  @author     Mark L. Short
 *  @date       May 7, 2017
 *
 *
 */
#pragma once

#if !defined(__DEBUG_UTILITY_H__)
#define __DEBUG_UTILITY_H__

/**
 *  @todo the following is currently only supported on the windows platforms
 */

#ifdef _MSC_VER

#ifndef _INC_TCHAR
    #include <tchar.h>
#endif


#ifdef _DEBUG
    #ifndef _FSTREAM_
        #include <fstream>
    #endif

    #if defined(UNICODE) || defined(_UNICODE)
        extern std::wofstream dbg;
    #else
        extern std::ofstream  dbg;
    #endif
#endif

namespace eng
{
namespace util
{

/**
   @brief  Directs output to the IDE output window.

   @param [in] szFmt          printf-styled format string

   @retval int                the number of characters written if the number of
                              characters to write is less than or equal to count;
                              if the number of characters to write is greater than
                              count, the function returns -1 indicating that output
                              has been truncated. The return value does not include
                              the terminating null, if one is written.
*/
    int DebugTrace(const _TCHAR* szFmt, ...) noexcept;

/**
   @brief  Retrieves the current executable directory

   @param [out] szModulePath   destination memory address used to write
                               application's directory path
   @param [in]  cchLen         count of characters available to be written in
                               the destination buffer

   @retval _TCHAR*              destination address
   @retval nullptr             on error
*/
    _TCHAR* GetModulePath(_TCHAR* szModulePath, size_t cchLen) noexcept;

} // namespace util
} // namespace eng

#else



#endif  // #ifdef _MSC_VER

#endif