/**
 *  @file       DebugUtils.cpp
 *  @brief      Implementation of debugging methods
 *
 *  @author     Mark L. Short
 *  @date       May 7, 2017
 *
 *
 */

/**
 *  the following is currently only supported on the windows platforms
 */

#ifdef _MSC_VER

// turn off silly warnings that encourage use of xxxx_s functions
#define _CRT_SECURE_NO_WARNINGS
#include "targetver.h"  // needs to be the 1st header included
#include <stdlib.h>
#include <stdarg.h>
#include <Windows.h>

#include "DebugUtils.h"

#ifdef _DEBUG

    #if defined(UNICODE) || defined(_UNICODE)
        std::wofstream dbg;
    #else
        std::ofstream  dbg;
    #endif

#endif

namespace eng
{
namespace util
{

int DebugTrace(const _TCHAR* szFmt, ...) noexcept
{
    _TCHAR szDebugMsg[512] = { 0 };

    va_list	vaArgs;
    va_start(vaArgs, szFmt);

    // use the format string and arguments to construct the debug output string
    int iReturnVal = _vsntprintf(szDebugMsg,
                                  _countof(szDebugMsg) - 1,
                                  szFmt,
                                  vaArgs);

    va_end(vaArgs);

    ::OutputDebugString(szDebugMsg);
    return iReturnVal;
};

_TCHAR* GetModulePath(_TCHAR* szModulePath, size_t cchLen) noexcept
{
    _TCHAR* szReturnVal = nullptr;

    // Get the executable file path
    TCHAR szModuleFileName[_MAX_PATH] = { 0 };

    // Note, if HANDLE is nullptr, GetModuleFileName is supposed to return the file
    // path to the current executable, but it appears that it is inconsistently
    // returning filename as well....
    DWORD dwStrLen = ::GetModuleFileName (nullptr, szModuleFileName,
                                          _countof(szModuleFileName));

    if (dwStrLen != 0)
    {
        TCHAR szDir[_MAX_PATH] = { 0 };

        _tsplitpath(szModuleFileName, szDir, &szDir[_MAX_DRIVE - 1], nullptr, nullptr);

        szReturnVal = _tcsncpy(szModulePath, szDir, cchLen);
    }

    return szReturnVal;
};

}  // namespace util
}  // namespace eng

#else



#endif  // #ifdef _MSC_VER

