/**
 *  @file       Application.cpp
 *  @brief      CApplication class implementation
 *
 *  @author     Mark L. Short
 *  @date       May 7, 2017
 *
 *
 */
#define WIN32_LEAN_AND_MEAN
#include "targetver.h"  // this needs to be the 1st header included
#include "CommonDef.h"

#include <Windows.h>

#include "Engine/Utility/DebugUtils.h"
#include "Engine/Utility/TimeUtils.h"
#include "Engine/Renderer/Renderer.h"

#include "Game.h"
#include "SoundManager.h"
#include "Application.h"


//-----------------------------------------------------------------------------
// Defines, constants, and global variables
//-----------------------------------------------------------------------------

CXboxController  CApplication::s_rgControllers[MAX_CONTROLLERS] = { CXboxController(0), 
                                                                    CXboxController(1), 
                                                                    CXboxController(2), 
                                                                    CXboxController(3) };

bool             g_bDeadZoneOn = true;


HGLRC            g_hglrc                  = nullptr;
const TCHAR      g_szClassName[]          = _T( "Simple Window Class" );
TCHAR            g_szModulePath[MAX_PATH] = {0};


//-----------------------------------------------------------------------------------------------
CApplication::~CApplication()
{
    if (m_pGame)
        delete m_pGame;

    if (m_pSoundManager)
        delete m_pSoundManager;
};

//-----------------------------------------------------------------------------------------------
void CApplication::RegisterWndClass (void ) noexcept
{
    // Define a window class
    WNDCLASSEX wndClassEx;
    memset( &wndClassEx, 0, sizeof( wndClassEx ) );
    wndClassEx.cbSize        = sizeof( wndClassEx );
    wndClassEx.style         = CS_OWNDC; // Redraw on move, request own Display Context
    wndClassEx.lpfnWndProc   = static_cast< WNDPROC >(CApplication::MainWndProc); // Assign a win32 message-handling function
    wndClassEx.hInstance     = m_hInstance;
    wndClassEx.hIcon         = nullptr;
    wndClassEx.hCursor       = nullptr;
    wndClassEx.lpszClassName = g_szClassName;
    ::RegisterClassEx( &wndClassEx );
};

//-----------------------------------------------------------------------------------------------
void CApplication::CreateOpenGLWindow( void ) noexcept
{
    RegisterWndClass();

    const DWORD dwStyleFlags   = WS_CAPTION | WS_BORDER | WS_THICKFRAME |
                                 WS_SYSMENU | WS_OVERLAPPED;
    const DWORD dwStyleFlagsEx = WS_EX_APPWINDOW;

    RECT desktopRect;
    HWND hwndDesktop = ::GetDesktopWindow();
    ::GetClientRect( hwndDesktop, &desktopRect );

    RECT windowRect = { OFFSET_FROM_WINDOWS_DESKTOP, OFFSET_FROM_WINDOWS_DESKTOP,
                        WINDOW_PHYSICAL_WIDTH  - 2*OFFSET_FROM_WINDOWS_DESKTOP,
                        WINDOW_PHYSICAL_HEIGHT - 2*OFFSET_FROM_WINDOWS_DESKTOP };
    ::AdjustWindowRectEx( &windowRect, dwStyleFlags, FALSE, dwStyleFlagsEx );


    m_hMainWnd = ::CreateWindowEx( dwStyleFlagsEx,
                                   g_szClassName,
                                   m_pszAppName,
                                   dwStyleFlags,
                                   windowRect.left,
                                   windowRect.top,
                                   windowRect.right - windowRect.left,
                                   windowRect.bottom - windowRect.top,
                                   nullptr,
                                   nullptr,
                                   m_hInstance,
                                   nullptr );

    ::ShowWindow( m_hMainWnd, SW_SHOW );
    ::SetForegroundWindow( m_hMainWnd );
    ::SetFocus( m_hMainWnd );

    m_hdcDisplay = ::GetDC( m_hMainWnd );

    HCURSOR cursor = ::LoadCursor( nullptr, IDC_ARROW );
    ::SetCursor( cursor );

    PIXELFORMATDESCRIPTOR pfd;
    memset( &pfd, 0, sizeof( pfd ) );
    pfd.nSize        = sizeof( pfd );
    pfd.nVersion     = 1;
    pfd.dwFlags      = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType   = PFD_TYPE_RGBA;
    pfd.cColorBits   = 24;
    pfd.cDepthBits   = 24;
    pfd.cAccumBits   = 0;
    pfd.cStencilBits = 8;

/*
    The ChoosePixelFormat function attempts to match an appropriate pixel format supported by a
    device context to a given pixel format specification.
*/
    int pixelFormatCode = ::ChoosePixelFormat( m_hdcDisplay, &pfd );
    ::SetPixelFormat( m_hdcDisplay, pixelFormatCode, &pfd );
    g_hglrc = wglCreateContext( m_hdcDisplay );

/*
    The wglMakeCurrent function makes a specified OpenGL rendering context the calling thread's current rendering context.
    All subsequent OpenGL calls made by the thread are drawn on the device identified by hdc.
*/
    wglMakeCurrent( m_hdcDisplay, g_hglrc );

/*
    The glOrtho function multiplies the current matrix by an orthographic matrix.
*/

    eng::g_theRdr.SetOrtho( eng::math::CVector2f(VIEW_LEFT, VIEW_BOTTOM),
                            eng::math::CVector2f(VIEW_RIGHT, VIEW_TOP) );

    eng::g_theRdr.Initialize();
};

//-----------------------------------------------------------------------------------------------
void CApplication::Initialize( HINSTANCE hInstance )
{
    m_hInstance = hInstance;

    eng::util::GetModulePath(g_szModulePath, _countof(g_szModulePath) - 1);

    CreateOpenGLWindow( );

    m_Keyboard.SetHandler(CApplication::KeyboardHandler);

    m_pSoundManager = new CSoundManager();
    if (m_pSoundManager)
        m_pSoundManager->InitSounds();

    m_pGame = new CGame(m_pSoundManager);
    if (m_pGame)
        m_pGame->InitActors();

};

//-----------------------------------------------------------------------------------------------
void CApplication::Shutdown( void ) noexcept
{
};

//-----------------------------------------------------------------------------------------------
void CApplication::RunFrame( void )
{
    static double s_timeLastFrameBegan = eng::util::GetCurrentTimeInSeconds();
    double timeThisFrameBegan          = eng::util::GetCurrentTimeInSeconds();
    float deltaSeconds                 = static_cast< float >( timeThisFrameBegan - s_timeLastFrameBegan );
    s_timeLastFrameBegan               = timeThisFrameBegan;

// Note: FPS = 1 / deltaSeconds
    Update( deltaSeconds );

    Render();
};

//-----------------------------------------------------------------------------------------------
void CApplication::Update ( float fDeltaTime )
{
    m_Keyboard.UpdateStates();

    if (m_pGame)
    {
        UpdateControllerStates();

        if (m_Keyboard.IsKeyPressed(Keys::O))
        {
            m_pGame->SpawnLargeAsteroid();
        }
        if (m_Keyboard.IsKeyPressed(Keys::L))
        {
            m_pGame->DestroyRandomAsteroid();
        }
        if (m_Keyboard.IsKeyPressed(Keys::Space) || s_rgControllers[0].get_A() )
        {
            if (m_pGame->IsShipActive ())
            {
                m_pGame->FireProjectile ();
                PlaySound (SND_MISSILE_FIRE);
            }
        }
        if (m_Keyboard.IsKeyPressed(Keys::P) || s_rgControllers[0].get_Start() )
        {
            m_pGame->SpawnShip();
        }

        m_pGame->Update( fDeltaTime );

        if (m_pSoundManager)
        {
            if (m_pSoundManager->Update() == false)
            {
                if (m_pSoundManager->IsAudioDevicePresent() == false)
                {
                    // TODO
                }
            }
        }
    }
}
//-----------------------------------------------------------------------------------------------
bool CApplication::PlaySound(int iIndex) noexcept
{
    bool bReturn = false;

    if (m_pSoundManager)
    {
        m_pSoundManager->Play(iIndex);
        bReturn = true;
    }
    return bReturn;
};
//-----------------------------------------------------------------------------------------------
bool CApplication::StopSound(int iIndex) noexcept
{
    bool bReturn = false;

    if (m_pSoundManager)
    {
        m_pSoundManager->Stop(iIndex);
        bReturn = true;
    }
    return bReturn;
};
//-----------------------------------------------------------------------------------------------
void CApplication::Render( void )
{
    if (m_pGame)
        m_pGame->Render();

    ::SwapBuffers( m_hdcDisplay );
};

//-----------------------------------------------------------------------------------------------
void CApplication::ProcessKeyboardMsg(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    m_Keyboard.ProcessMessage(uMsg, wParam, lParam);
};

//-----------------------------------------------------------------------------------------------
void CApplication::OnSize(void)
{
    /* set viewport to cover the window */
    eng::g_theRdr.SetViewPort( 0, 0, m_iMainWinHeight, m_iMainWinHeight);
};

//-----------------------------------------------------------------------------------------------
void CApplication::UpdateControllerStates(void)
{
    for (DWORD i = 0; i < MAX_CONTROLLERS; i++)
    {
        s_rgControllers[i].UpdateControllerState();

        if (s_rgControllers[i].m_bConnected)
        {
            if (g_bDeadZoneOn)
            {
                // Zero value if thumbsticks are within the dead zone
                if (( s_rgControllers[i].m_stInput.Gamepad.sThumbLX <  XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
                      s_rgControllers[i].m_stInput.Gamepad.sThumbLX > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE ) &&
                    ( s_rgControllers[i].m_stInput.Gamepad.sThumbLY <  XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
                      s_rgControllers[i].m_stInput.Gamepad.sThumbLY > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE ))
                {
                    s_rgControllers[i].m_stInput.Gamepad.sThumbLX = 0;
                    s_rgControllers[i].m_stInput.Gamepad.sThumbLY = 0;
                }

                if (( s_rgControllers[i].m_stInput.Gamepad.sThumbRX <  XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE &&
                      s_rgControllers[i].m_stInput.Gamepad.sThumbRX > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE ) &&
                    ( s_rgControllers[i].m_stInput.Gamepad.sThumbRY <  XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE &&
                      s_rgControllers[i].m_stInput.Gamepad.sThumbRY > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE))
                {
                    s_rgControllers[i].m_stInput.Gamepad.sThumbRX = 0;
                    s_rgControllers[i].m_stInput.Gamepad.sThumbRY = 0;
                }
            }
        }
    }
};

//-----------------------------------------------------------------------------------------------
/**
  @brief An application-defined function that processes messages sent to a window

  @param [in] hWnd      A handle to the window
  @param [in] uMsg      The message
  @param [in] wParam    Additional message information. The contents of this parameter depend
                        on the value of the uMsg parameter
  @param [in] lParam    Additional message information. The contents of this parameter depend
                        on the value of the uMsg parameter

  @retval LRESULT       The return value is the result of the message processing and depends on
                        the message sent

 */
LRESULT CALLBACK CApplication::MainWndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
    switch( uMsg )
    {
        case WM_ACTIVATEAPP:
        {
            // We need to explicitly use XInput v9.1.0, as newer (1_4+) versions do not run under Windows 7 or prior.
            // This function (XInputEnable) in particular is not supported under Windows 7 (and prior).
            // Regardless, the best practice here is to have the Application maintain awareness of the app's
            //    focus state, and not do input polling (of all kinds - not just controllers) while unfocused.
//             if (wParam == TRUE)
//                 XInputEnable(TRUE);
//             else
//                 XInputEnable(FALSE);
        }
        break;
        // a window is about to be destroyed
        case WM_DESTROY:
        {
            // local variables
            HGLRC    hglrc = wglGetCurrentContext();
            HDC      hdc;

            // if the thread has a current rendering context ...
            if ( hglrc )
            {

                // obtain its associated device context
                hdc = wglGetCurrentDC();

                // make the rendering context not current
                wglMakeCurrent(nullptr, nullptr);

                // release the device context
                ::ReleaseDC(g_theApp.m_hMainWnd, hdc);

                // delete the rendering context
                wglDeleteContext(hglrc);

            }
            ::PostQuitMessage(0);
        }
        break;

        case WM_SIZE:
            g_theApp.m_iMainWinWidth = (int) LOWORD(lParam);
            g_theApp.m_iMainWinHeight = (int) HIWORD(lParam);
            g_theApp.OnSize();
            return 0;
            break;

        case WM_KEYDOWN:
        case WM_KEYUP:
            g_theApp.ProcessKeyboardMsg(uMsg, wParam, lParam);
            break;
        }

    return ::DefWindowProc( hWnd, uMsg, wParam, lParam );
}

//-----------------------------------------------------------------------------------------------
void CALLBACK CApplication::KeyboardHandler(UINT nKey, BOOL /*bKeyPressed*/)
{
    Keys Key = static_cast<Keys>( nKey );
    switch (Key)
    {
        case Keys::Escape:
            ::PostQuitMessage(0);
            break;

        default:
            break;
    }

    return;
};


