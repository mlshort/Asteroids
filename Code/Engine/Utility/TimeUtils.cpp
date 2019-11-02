/**
 *  @file       TimeUtils.cpp
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

#define WIN32_LEAN_AND_MEAN
#include "targetver.h"     // needs to be the 1st header included
#include <Windows.h>

#include "Time.h"

namespace eng
{
namespace util
{

//-----------------------------------------------------------------------------------------------]
/**
  @brief Initializes a time struct
  
  @param [out] nStartTime   initialized to the current tick count

  @retval double  containing the tick interval (ticks per second)
 */
double InitializeTime( LARGE_INTEGER& liStartTime )
{
    double fTickInterval = 0.0;
    LARGE_INTEGER liFrequency;

    // @warniing
    // QueryPerformanceCounter returns values that represent time in units of 1/(the frequency of 
    // the performance counter obtained from QueryPerformanceFrequency). Conversion between the two 
    // requires calculating the ratio of the QPC interval and 100-nanoseconds intervals. Be careful to
    // avoid losing precision because the values might be small (0.0000001 / 0.000000340).

    //   Retrieves the frequency of the performance counter. The frequency of 
    //   the performance counter is fixed at system boot and is consistent 
    //   across all processors. Therefore, the frequency need only be queried upon 
    //   application initialization, and the result can be cached

    // nFrequency receives the current performance-counter frequency, in counts per second.
    if (::QueryPerformanceFrequency(&liFrequency) != 0)
    {
        //  Retrieves the current value of the performance counter, which is a high 
        //  resolution (<1us) time stamp that can be used for time-interval measurements
        ::QueryPerformanceCounter(&liStartTime);

            // Example: QueryPerformanceFrequency returns the value 3,125,000 on a particular 
            //          machine. 
            //          What is the tick interval and resolution of QPC measurements on this machine? 
            //          The tick interval, or period, is the reciprocal of 3,125,000, which is 
            //          0.000000320 (secs) or 320 (nanoseconds). 

         fTickInterval = 1.0 / static_cast<double>( liFrequency.QuadPart );  
    }
    else
    {
        // @todo - handle the error
    }

    return fTickInterval;
}


//-----------------------------------------------------------------------------------------------
double GetCurrentTimeInSeconds(void)
{
    static LARGE_INTEGER liStartTime;
    static double fTickInterval = eng::util::InitializeTime(liStartTime);
 
    LARGE_INTEGER liCurrTime;
    ::QueryPerformanceCounter(&liCurrTime);
    auto nElapsedTicks = liCurrTime.QuadPart - liStartTime.QuadPart;

    return static_cast<double>(nElapsedTicks) * fTickInterval;
}

} // namespace util
} // namespace eng
