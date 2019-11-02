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

const int WINDOW_PHYSICAL_WIDTH  = 1600;
const int WINDOW_PHYSICAL_HEIGHT = 900;

const int   OFFSET_FROM_WINDOWS_DESKTOP = 50;
const float VIEW_LEFT   = 0.0;
const float VIEW_RIGHT  = 1600.0;
const float VIEW_BOTTOM = 0.0;
const float VIEW_TOP    = VIEW_RIGHT * static_cast< float >(WINDOW_PHYSICAL_HEIGHT) / static_cast< float >(WINDOW_PHYSICAL_WIDTH);


const size_t MAX_ACTORS             = 512;
const size_t ASTEROID_VERTICES      = 12;
const size_t INITIAL_ASTEROIDS      = 6;
const size_t ASTEROID_WAVE_DELTA    = 4;

const float k_fProjectileRadius     =   1.5f;
const float k_fProjectileSpeed      = 500.f;

const float k_ShipRadius            =  15.f;
const float k_fShipLineWidth        =   1.5f;
const float k_fShipThrust           = 250.f;
const float k_fShipTurnRate         = 160.f;

const float k_fAsteroidLineWidth    =   1.5f;
const float k_fAsteroidRadiusLarge  =  40.f;
const float k_fAsteroidRadiusMedium =  30.f;
const float k_fAsteroidRadiusSmall  =  20.f;
const float k_fAsteroidSpeed        =  50.f;

#include "Resources\resource.h"


#endif