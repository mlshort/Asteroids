

Asteroids: Final Project
==================

Directory Structure
-------------------

    +-- Asteroids (Solution File)
        |
        +-- Readme.md (this file)
        |
        +-- mlshort.FinalProject.Asteroids.pptx (project presentation)
        |
        +-- Bin (Asteroids[_x64][D].exe)
        |   |
        |   +-- Assets
        |       |
        |       +-- Audio (wav files)
        |
        +-- Code (Source Code Root Directory)
        |   |
        |   +-- Game (Game Source Code) (Project file)
        |   |   |
        |   |   +-- Resources (RC files)
        |   |       |
        |   |       +-- Audio (wav files)
        |   |
        |   +-- Engine (Engine Source Code) (Project file)
        |       |
        |       +-- Core (Actor2, IRenderable)
        |       |
        |       +-- Math (Vector2, Random, MathUtils)
        |       |
        |       +-- Renderer (AABB, Renderer, Texture)
        |       |
        |       +-- Utility (DebugUtils, TimeUtils)
        |
        |-- Lib (Game Engine Static Library : Engine[_x64][D].lib)
        |
        +-- Obj (compile time intermediaries objects)
        |
        +-- Third Party
            |
            +-- DirectX
            |   |
            |   +-- Lib
            |       |
            |       +-- x86 (DirectX, DirectSound, DirectInput, etc)
            |
            +-- stbi (Solution File) (Project File) (stbi Source Code)


Project Enhancements
--------------------
1. Source Code Repository (Visual Studio Team Services)
    * https://ualr-projects.visualstudio.com/Grad%20School%20Projects/_versionControl
    * https://ualr-projects.visualstudio.com/Grad%20School%20Projects/_versionControl#path=%24%2FGrad%20School%20Projects%2FAsteroids&version=T&_a=contents

2. Windows Unicode Compliant

3. Compiles/Deploys in:
    * Win32 Release Mode
    * Win32 Debug Mode
    * x64 Release Mode (not fully tested)
    * x64 Debug Mode (not fully tested)

4. Intergrated use of XBox Controller (via XInput API)

5. Development and use of seperate Game Engine library
    * Primitive Physics Engine
    * Math
       - Vector2 (2D vector class template)
       - Random (STL Mersiene Twister random number abstraction)
    * Renderer (OpenGL abstraction)
       - Texture (OpenGL/stbi abstraction)
       - AABB (optimized collision detection)
    * Utility
       - TimeUtils (Windows performance counter abastraction)

6. Component Compile-Time product versioning
    * Asteroids\ProductVer.h
    * Asteroids\Code\Game\Resources\Asteroids.rc2 
    * Asteroids\Code\Game\AsteroidsVersion.h
    * Asteroids\Code\Engine\EngineVersion.h

7. Use of various C++11/14 features


HOW TO USE:
---------------

```<language>
'A' || 'Left' || 'DPad Right' || 'LThumb' direction - Rotates ship counter-clockwise
'D' || 'Right' || 'DPad Left' || 'LThumb' direction - Rotates ship clockwise
'W' || 'Forward' || 'DPad UP' || 'LThumb' magnitude - Causes ship to thrust forward
'O'                                                 - Random Asteroid Destroyed
'L'                                                 - Creates New Large Asteroid
'P' || 'Start'                                      - Re-spawns Ship
'T'                                                 - Direction Overlay (for diagnostics)

```