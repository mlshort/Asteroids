// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Scrolling Bitmap constants.h v1.1
// Last modification: Feb-11-2013

#ifndef _CONSTANTS_H            // Prevent multiple definitions if this 
#define _CONSTANTS_H            // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <tchar.h>

//=============================================================================
// Function templates for safely dealing with pointer referenced items.
// The functions defined by these templates may be called using a normal
// function call syntax. The compiler will create a function that replaces T
// with the type of the calling parameter.
//=============================================================================
// Safely release pointer referenced item
template <typename T>
inline void safeRelease(T& ptr)
{
    if (ptr)
    { 
        ptr->Release(); 
        ptr = NULL;
    }
}
#define SAFE_RELEASE safeRelease            // for backward compatiblility

// Safely delete pointer referenced item
template <typename T>
inline void safeDelete(T& ptr)
{
    if (ptr)
    { 
        delete ptr; 
        ptr = NULL;
    }
}
#define SAFE_DELETE safeDelete              // for backward compatiblility

// Safely delete pointer referenced array
template <typename T>
inline void safeDeleteArray(T& ptr)
{
    if (ptr)
    { 
        delete[] ptr; 
        ptr = NULL;
    }
}
#define SAFE_DELETE_ARRAY safeDeleteArray   // for backward compatiblility

// Safely call onLostDevice
template <typename T>
inline void safeOnLostDevice(T& ptr)
{
    if (ptr)
        ptr->onLostDevice(); 
}
#define SAFE_ON_LOST_DEVICE safeOnLostDevice    // for backward compatiblility

// Safely call onResetDevice
template <typename T>
inline void safeOnResetDevice(T& ptr)
{
    if (ptr)
        ptr->onResetDevice(); 
}
#define SAFE_ON_RESET_DEVICE safeOnResetDevice  // for backward compatiblility

//=============================================================================
//                  Constants
//=============================================================================

// window
const TCHAR CLASS_NAME[] = _T("Spacewar");
const TCHAR GAME_TITLE[] = _T("Scrolling Bitmap");
const bool FULLSCREEN = false;              // windowed or fullscreen
const UINT GAME_WIDTH =  640;               // width of game in pixels
const UINT GAME_HEIGHT = 480;               // height of game in pixels
 
// game
const double PI = 3.14159265;
const float FRAME_RATE  = 200.0;                // the target frame rate (frames/sec)
const float MIN_FRAME_RATE = 10.0f;             // the minimum frame rate
const float MIN_FRAME_TIME = 1.0f/FRAME_RATE;   // minimum desired time for 1 frame
const float MAX_FRAME_TIME = 1.0f/MIN_FRAME_RATE; // maximum time used in calculations
const float FULL_HEALTH = 100;
const int SPACE_SCALE = 2;                  // scale factor of space image
const int SPACE_WIDTH = 640 * SPACE_SCALE;  // width of scaled space image
const int SPACE_HEIGHT = 480 * SPACE_SCALE; // height of scaled space image
const UINT MOON_SIZE = 64;                  // size of moon images
const UINT MOON1_FRAME = 12;                // frame of moon1
const UINT NEBULA_SIZE = 128;               // size of nebula images
// graphic images
const TCHAR SPACE_IMAGE[] = _T("pictures\\space.jpg");   // photo source NASA/courtesy of nasaimages.org 
const TCHAR TEXTURES1_IMAGE[] = _T("pictures\\textures1.png");  // game textures
const TCHAR MENU_IMAGE[] = _T("pictures\\menu.png");     // menu texture

// audio files required by audio.cpp
// WAVE_BANK must be location of .xwb file.
const TCHAR WAVE_BANK[]  = _T("audio\\Win\\waveBank.xwb");
// SOUND_BANK must be location of .xsb file.
const TCHAR SOUND_BANK[] = _T("audio\\Win\\soundBank.xsb");

// audio cues
const TCHAR CHEER[]          = _T("cheer");
const TCHAR COLLIDE[]        = _T("collide");
const TCHAR EXPLODE[]        = _T("explode");
const TCHAR ENGINE1[]        = _T("engine1");
const TCHAR ENGINE2[]        = _T("engine2");
const TCHAR TORPEDO_CRASH[]  = _T("torpedoCrash");
const TCHAR TORPEDO_FIRE[]   = _T("torpedoFire");
const TCHAR TORPEDO_HIT[]    = _T("torpedoHit");

// key mappings
// In this game simple constants are used for key mappings. If variables were used
// it would be possible to save and restore key mappings from a data file.
const UCHAR CONSOLE_KEY  = '`';         // ` key
const UCHAR ESC_KEY      = VK_ESCAPE;   // escape key
const UCHAR ALT_KEY      = VK_MENU;     // Alt key
const UCHAR ENTER_KEY    = VK_RETURN;   // Enter key
const UCHAR SHIP1_LEFT_KEY    = VK_LEFT; // left arrow
const UCHAR SHIP1_RIGHT_KEY   = VK_RIGHT; // right arrow
const UCHAR SHIP1_FORWARD_KEY = VK_UP;   // up arrow
const UCHAR SHIP1_FIRE_KEY    = VK_DOWN; // down arrow

// weapon types
enum WEAPON {TORPEDO, SHIP, PLANET};

#endif
