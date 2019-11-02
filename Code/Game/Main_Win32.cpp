/**
 *  @file       Main_Win32.cpp
 *  @brief      WinMain implementation
 *  @mainpage
 *  @author     Mark L. Short
 *  @date       May 7, 2017
 *
 *
 *
 *
 *  <b>Cite:</b>
 *       * Fletcher Dunn, Ian Parberry, "3D Math Primer for Graphics and Game Development",
 *         2nd Ed., 2011
 *       * Lipschutz, Lipson, "Schaum's Outlines, Linear Algebra", 4th Ed., 2009
 *       * Charles Kelly, "Programming 2D Games", 2012
 *       * OGRE Open Source 3D Graphics Engine, http://www.ogre3d.org
 *       * GZDoom, http://zdoom.org/wiki/GZDoom
 *       * Microsoft DirectX SDK, http://blogs.msdn.com/b/chuckw/archive/2012/03/27/introducing-directxmath.aspx
 *       * Microsoft Development Network (MSDN), https://msdn.microsoft.com/en-us/default.aspx
 *       * OpenGL SDK, https://www.opengl.org/sdk/
 *       * Unreal Engine 4, https://www.unrealengine.com/
 *
 */

#define WIN32_LEAN_AND_MEAN
#include "targetver.h"  // this needs to be the 1st header included

#include <stdlib.h>
#include <windows.h>

#include "Application.h"

//-----------------------------------------------------------------------------------------------
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE, LPSTR /*commandLineString*/, int )
{
    g_theApp.Initialize( hInstance );

    MSG msg;
    // Enter the infinite message Loop
    for (;;)
    {
        // Check to see if any messages are waiting in the queue
        while (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            // translate keystroke messages into the right format
            ::TranslateMessage(&msg);

            // send the message to the WindowProc function
            ::DispatchMessage(&msg);
        }

        // If the message is WM_QUIT, exit the while Loop
        if (msg.message == WM_QUIT)
            break;

        g_theApp.RunFrame();
    }


    g_theApp.Shutdown();

    // return this part of the WM_QUIT message to Windows
    return static_cast<int>(msg.wParam);
}


