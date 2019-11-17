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

/// @brief The sound manager.
///
/// The sound manager allows you to Play multiple
/// overlapping copies of sounds simultaneously.
/// It can load WAV format sounds.
class CSoundManager
{
private:
    AudioEngine*              m_pAudioEngine; ///< XAudio 2.8 Engine wrapped up in DirectXTK.
    std::vector<SoundEffect*> m_rgSoundEffects; ///< A list of sound effect.
    SoundEffectInstance**     m_rgInstances[k_nMaxSounds]; ///< A list of arrays of sound effect instances.

    int m_rgInstanceCount[k_nMaxSounds]; ///< Number of copies of each sound.

    int m_nCount;              ///< Number of sounds loaded.
    int m_nLastPlayedSound;    ///< Last sound played.
    int m_nLastPlayedInstance; ///< Instance of the last sound played.

/**
 *  Create sound instances
 */
    void CreateInstances(int iIndex, int nNumInstances, SOUND_EFFECT_INSTANCE_FLAGS flags) noexcept;
/**
 *  Load sound from file
 *
 *  @retval int  containing sound file index
 *  @retval -1   on error
 */
    int  Load(const wchar_t* szWaveFileName) noexcept;
/**
 *  Get the next instance that is not playing
 */
    int  GetNextInstance(int iIndex) noexcept;

public:
    /// Default Constructor
    CSoundManager() noexcept;
    /// Default Destructor
    ~CSoundManager();

/**
 *  Initialize and allocates sound file resources
 *
 *  @retval true    on success
 *  @retval false   on error
 */
    bool InitSounds(void) noexcept;
/**
 *  @param [in] szWaveFilename   wav file name
 *
 *  @retval int  containing valid index
 *  @retval -1   on error
 */
    int  LoadAndCreateInstance(const wchar_t* szWaveFileName) noexcept;

/**
 *  @retval true   if the audio graph is operating normally
 *  @retval false  if in 'silent mode'
 */
    bool IsAudioDevicePresent (void) const noexcept;

/**
 *  Performs per-frame processing for the audio engine
 *
 *  @retval true   on success
 *  @retval false  if in 'silent mode'
 */
    bool Update(void) noexcept;

/**
 *  Play a sound
 *
 *  @retval int   containing instance played
 *  @retval -1    on error
 */
    int  Play(int iIndex) noexcept;
    int  Loop(int iIndex) noexcept; ///< Play a sound looped.
    void Stop(int iIndex) noexcept; ///< Stop a sound.

/**
 *  Sets a pitch-shift factor. 
 * 
 *  @param [in] fPitch       Ranges from -1 to +1, playback defaults to 0 (which is no pitch-shifting).
 *  @param [in] iInstance
 *  @param [in] iIndex
 *
 *  This will trigger a C++ exception if the object was created with SoundEffectInstance_NoSetPitch
 */
    void SetPitch (float fPitch, int iInstance = -1, int iIndex = -1);
/**
 *  Sets playback volume. Playback defaults to 1
 */
    void SetVolume(float fVolume, int iInstance = -1, int iIndex = -1);
};

#endif