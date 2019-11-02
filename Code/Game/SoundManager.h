/**
 *  @file       SoundManager.h
 *  @brief      CSoundManager class definition
 *
 *  @author     Mark L. Short
 *  @date       May 7, 2017
 *
 *  @cite:
 *             Modified source from Ned's Turkey Farm
 *             http://larc.unt.edu/demos/faves/
 */

#pragma once

#if !defined(__SOUND_MANAGER_H__)
#define __SOUND_MANAGER_H__

#include <Audio.h>
#include <DirectXMath.h>

#ifndef __SOUND_LIST_H__
    #include "Soundlist.h" //list of sound names
#endif

using namespace DirectX;

constexpr const size_t k_nMaxSounds = 20;

/// \brief The sound manager.
///
/// The sound manager allows you to Play multiple
/// overlapping copies of sounds simultaneously.
/// It can load WAV format sounds.
class CSoundManager
{
private:
    AudioEngine*              m_pAudioEngine; ///< XAudio 2.8 Engine wrapped up in DirectXTK.
    std::vector<SoundEffect*> m_pSoundEffects; ///< A list of sound effect.
    SoundEffectInstance**     m_pInstance[k_nMaxSounds]; ///< A list of arrays of sound effect instances.

    int m_rgInstanceCount[k_nMaxSounds]; ///< Number of copies of each sound.

    int m_nCount;              ///< Number of sounds loaded.
    int m_nMaxSounds;          ///< Maximum number of sounds allowed.
    int m_nLastPlayedSound;    ///< Last sound played.
    int m_nLastPlayedInstance; ///< Instance of the last sound played.

    void CreateInstances(int iIndex, int n, SOUND_EFFECT_INSTANCE_FLAGS flags); ///< Create sound instances.
/**
 *  @retval -1 on error
 */
    int  Load(const wchar_t* szFilename); ///< Load sound from file.
    int  GetNextInstance(int iIndex);     ///< Get the next instance that is not playing.

public:
    CSoundManager();  ///< Constructor.
    ~CSoundManager(); ///< Destructor.

    bool InitSounds(void);
/**
  *  @retval -1 on error
  */
    int  LoadAndCreateInstance(const wchar_t* szFilename);
    bool IsAudioDevicePresent (void) const;

    bool Update(void);

    int  Play(int index); ///< Play a sound.
    int  Loop(int index); ///< Play a sound looped.
    void Stop(int index); ///< Stop a sound.

    void SetPitch (float p, int instance = -1, int index = -1); ///< Set sound SetPitch.
    void SetVolume(float v, int instance = -1, int index = -1); ///< Set sound SetVolume.
}; //CSoundManager

#endif