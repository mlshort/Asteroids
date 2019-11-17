/**
 *  @file       SoundManager.cpp
 *  @brief      CSoundManager class implementation
 *
 *  @author     Mark L. Short
 *  @date       May 7, 2017
 *
 *  @cite:
 *             Modified source from Ned's Turkey Farm
 *             http://larc.unt.edu/demos/faves/
 */

#define WIN32_LEAN_AND_MEAN
#include "targetver.h"  // this needs to be the 1st header included
#include "CommonDef.h"

#include <stdio.h>
#include <string>

#include "SoundManager.h"

extern TCHAR  g_szModulePath[MAX_PATH];


CSoundManager::CSoundManager() noexcept
    : m_nCount(0),
      m_nLastPlayedInstance(-1),
      m_nLastPlayedSound(-1)
{
    memset(m_rgInstanceCount, 0, sizeof(m_rgInstanceCount));
    memset(m_rgInstances, 0, sizeof(m_rgInstances));

    ::CoInitializeEx(nullptr, COINIT_MULTITHREADED);
    AUDIO_ENGINE_FLAGS eflags = AudioEngine_Default;

#ifdef _DEBUG
    eflags = eflags | AudioEngine_Debug;
#endif
    try
    {
        m_pAudioEngine = new AudioEngine(eflags);
    }
    catch (...)
    {
        delete m_pAudioEngine;
        m_pAudioEngine = nullptr;
    }
}



CSoundManager::~CSoundManager()
{
    for (int i = 0; i < m_nCount; i++)
    {
        for (int j = 0; j < m_rgInstanceCount[i]; j++)
        {
            delete m_rgInstances[i][j];
        }
        delete [] m_rgInstances[i];
    }

    for (auto SndEffect : m_rgSoundEffects)
        delete SndEffect;

    delete m_pAudioEngine;

    ::CoUninitialize ();
}


int CSoundManager::Load(const wchar_t* szFileName) noexcept
{
    int iRetVal = -1;
    SoundEffect* pSndEff = nullptr;
    try
    {
        pSndEff = new SoundEffect(m_pAudioEngine, szFileName);
    }
    catch (...)
    {
        // we have an exception, lets prevent a resource leak
        delete pSndEff;
        pSndEff = nullptr;
    }

    if (pSndEff)
    {
        m_rgSoundEffects.push_back (pSndEff);
        iRetVal = static_cast<int>(m_rgSoundEffects.size() - 1);
    }
   
    return iRetVal;
}

bool CSoundManager::InitSounds(void) noexcept
{
    int iResult = -1;
    for (int iCtr = 0; iCtr < _countof (k_szSoundFiles); iCtr++)
    {
        std::wstring szFileName(g_szModulePath);
        szFileName += k_szSoundFiles[iCtr];

        iResult = LoadAndCreateInstance(szFileName.c_str());
        if (iResult == -1)
            break;
    }

    return (iResult != -1);
}

int CSoundManager::LoadAndCreateInstance(const wchar_t* szFilename) noexcept
{
    auto iIndex = Load(szFilename);

    if (iIndex != -1)
       CreateInstances(iIndex, 1, SoundEffectInstance_Default );

    return iIndex;
}

bool CSoundManager::Update(void) noexcept
{
    return m_pAudioEngine ? m_pAudioEngine->Update () : false;
};

bool CSoundManager::IsAudioDevicePresent (void) const noexcept
{
    return m_pAudioEngine ? m_pAudioEngine->IsAudioDevicePresent () : false;
};


void CSoundManager::CreateInstances(int iIndex, int iNumInstances, SOUND_EFFECT_INSTANCE_FLAGS flags) noexcept
{
    m_rgInstanceCount[iIndex] = iNumInstances;
    m_rgInstances[iIndex] = new SoundEffectInstance*[iNumInstances];

    try
    {
        for (int i = 0; i < iNumInstances; i++)
            m_rgInstances[iIndex][i] = m_rgSoundEffects[iIndex]->CreateInstance(flags).release();
    }
    catch (...)
    {
       return;
    }

    m_nCount++;
}


int CSoundManager::GetNextInstance(int iIndex) noexcept
{
    int iInstance = 0; //current instance

    //get status of first instance
    SoundState soundState = m_rgInstances[iIndex][iInstance]->GetState();

    //find next unplayed instance, if any
    while (iInstance < m_rgInstanceCount[iIndex] && ( soundState == PLAYING )) //while current copy in use
    {
        if (++iInstance < m_rgInstanceCount[iIndex]) //go to next copy
            soundState = m_rgInstances[iIndex][iInstance]->GetState();
    }
    return iInstance;
}


int CSoundManager::Play(int iIndex) noexcept
{
    if (iIndex < 0 || iIndex >= m_nCount)
        return -1; //bail if bad index

    int iInstance = GetNextInstance(iIndex);
    if (iInstance < m_rgInstanceCount[iIndex]) //if unused copy found
        m_rgInstances[iIndex][iInstance]->Play(); //Play it

    m_nLastPlayedSound = iIndex;
    m_nLastPlayedInstance = iInstance;

    return iInstance;
}


int CSoundManager::Loop(int iIndex) noexcept
{
    if (iIndex < 0 || iIndex >= m_nCount)
        return -1; //bail if bad index

    int iInstance = GetNextInstance(iIndex);
    if (iInstance < m_rgInstanceCount[iIndex]) //if unused copy found
        m_rgInstances[iIndex][iInstance]->Play(true); //Play it looped

    m_nLastPlayedSound = iIndex;
    m_nLastPlayedInstance = iInstance;

    return iInstance;
}

void CSoundManager::Stop(int iIndex) noexcept
{
    if (iIndex < 0 || iIndex >= m_nCount)
        return; //bail if bad index

    for (int iInstance = 0; iInstance < m_rgInstanceCount[iIndex]; iInstance++)
    {
        SoundEffectInstance* p = m_rgInstances[iIndex][iInstance];
        if (p != nullptr)
            p->Stop();
    }
}


void CSoundManager::SetPitch(float fPitch, int iInstance /* = -1 */, int iIndex /* = -1 */)
{
    if (iIndex == -1)
        iIndex = m_nLastPlayedSound;

    if (iInstance == -1)
        iInstance = m_nLastPlayedInstance;

    if (iInstance >= 0 && iInstance < m_rgInstanceCount[iIndex])
        m_rgInstances[iIndex][iInstance]->SetPitch(fPitch);
}


void CSoundManager::SetVolume(float fVolume, int iInstance /* = -1 */, int iIndex /* = -1 */)
{
    if (iIndex == -1)
        iIndex = m_nLastPlayedSound;

    if (iInstance == -1)
        iInstance = m_nLastPlayedInstance;

    if (iInstance >= 0 && iInstance < m_rgInstanceCount[iIndex])
        m_rgInstances[iIndex][iInstance]->SetVolume(fVolume);
}