/**
 *  @file       CommonDef.h
 *  @brief      Application Common Definitions
 *
 *  @author     Mark L. Short
 *  @date       May 7, 2017
 *
 */

#pragma once

#if !defined(__COMMON_DEF_H__)
#define __COMMON_DEF_H__

#ifndef __VECTOR2_H__
    #include "Engine/Math/Vector2.h"
#endif

typedef int                  TILE_INDEX;
typedef eng::math::CVector2i WORLD_COORDS;

typedef float                DEGREES;
typedef float                RADIANS;

constexpr size_t MAX_CONTROLLERS = 4;  // XInput handles up to 4 controllers

constexpr int    WINDOW_PHYSICAL_WIDTH = 1600;
constexpr int    WINDOW_PHYSICAL_HEIGHT = 900;

constexpr int   OFFSET_FROM_WINDOWS_DESKTOP = 50;
constexpr float VIEW_LEFT   = 0.0;
constexpr float VIEW_RIGHT  = 1600.0;
constexpr float VIEW_BOTTOM = 0.0;
constexpr float VIEW_TOP    = VIEW_RIGHT * static_cast< float >(WINDOW_PHYSICAL_HEIGHT) / static_cast< float >(WINDOW_PHYSICAL_WIDTH);

constexpr size_t MAX_ACTORS             = 512;
constexpr size_t ASTEROID_VERTICES      = 12;
constexpr size_t INITIAL_ASTEROIDS      = 6;
constexpr size_t ASTEROID_WAVE_DELTA    = 4;

constexpr float k_fProjectileRadius     =   1.5f;
constexpr float k_fProjectileSpeed      = 500.f;

constexpr float k_ShipRadius            =  15.f;
constexpr float k_fShipLineWidth        =   1.5f;
constexpr float k_fShipThrust           = 250.f;
constexpr float k_fShipTurnRate         = 160.f;

constexpr float k_fAsteroidLineWidth    =   1.5f;
constexpr float k_fAsteroidRadiusLarge  =  40.f;
constexpr float k_fAsteroidRadiusMedium =  30.f;
constexpr float k_fAsteroidRadiusSmall  =  20.f;
constexpr float k_fAsteroidSpeed        =  50.f;

#include "Resources\resource.h"


#endif