/**
 *  @file       SoundList.h
 *  @brief      List of sound wave files
 *
 *  @author     Mark L. Short
 *  @date       May 7, 2017
 *
 */

#pragma once

#if !defined(__SOUND_LIST_H__)
#define __SOUND_LIST_H__

#ifndef _INC_TCHAR
    #include <tchar.h>
#endif

const constexpr TCHAR* k_szSoundFiles[] =
{
    _T("Assets\\Audio\\Engine2.wav"),
    _T("Assets\\Audio\\TorpedoFire.wav"),
    _T("Assets\\Audio\\TorpedoHit.wav"),
    _T("Assets\\Audio\\Explode.wav")
};


enum SOUND_T
{
    SND_ENGINE,
    SND_MISSILE_FIRE,
    SND_MISSILE_HIT,
    SND_EXPLOSION
};

#endif
