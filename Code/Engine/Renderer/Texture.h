/**
 *  @file       Texture.h
 *  @brief      CTexture class interface
 *
 *  @author     Mark L. Short
 *  @date       May 7, 2017
 *
 *  <b>Implementation:</b>
 * 
 *   Textures are created by calling Texture::CreateOrGetTexture(), for example:
 *   Subsequent calls to CreateOrGetTexture() with the same name return a pointer to the 
 *          already-loaded texture (and do not load it a second time).
 *
 */
#pragma once

#if !defined(__TEXTURE_H__)
#define __TEXTURE_H__

#ifndef _MAP_
    #include <map>
#endif

#ifndef _STRING_
    #include <string>
#endif

#ifndef __VECTOR2_H__
    #include "Engine/Math/Vector2.h"
#endif


namespace eng
{
namespace rdr
{

class CTexture
{
    static std::map< std::string, CTexture*> s_mapRegistry;
    unsigned int                             m_nOpenGLTextureID; ///< Holds the ID of the texture object
    math::CVector2i                          m_vTexelSize;
    int                                      m_iComponents;       ///< RGBA Components

public:
    constexpr CTexture() noexcept;
    ~CTexture();

    bool                   Init              (const char* szImageFilePath);
    constexpr unsigned int get_TextureID     (void) const noexcept;

    static CTexture*       GetTextureByName  (const char* szImageFilePath);
    static CTexture*       CreateOrGetTexture(const char* szImageFilePath);
};

constexpr unsigned int 
CTexture::get_TextureID  (void) const noexcept
{ return m_nOpenGLTextureID; };

}
}
#endif