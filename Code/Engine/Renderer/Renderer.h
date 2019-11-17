/**
 *  @file       Renderer.h
 *  @brief      CRenderer class interface
 *
 *  @author     Mark L. Short
 *  @date       May 7, 2017
 *
 *
 *
 */
#pragma once

#if !defined(__RENDERER_H__)
#define __RENDERER_H__

#ifndef __AABB2_H__
    #include "Engine/Renderer/AABB2.h"
#endif

#ifndef __TEXTURE_H__
    #include "Engine/Renderer/Texture.h"
#endif

#ifndef _VECTOR_
    #include <vector>
#endif

namespace eng
{

struct ColorRGBA
{
    float fRed;
    float fGreen;
    float fBlue;
    float fAlpha;
};

constexpr ColorRGBA RGBA_WHITE   = { 1.0f, 1.0f, 1.0f,  1.0f };
constexpr ColorRGBA RGBA_BLACK   = { 0.0f, 0.0f, 0.0f,  1.0f };
constexpr ColorRGBA RGBA_RED     = { 1.0f, 0.0f, 0.0f,  1.0f };
constexpr ColorRGBA RGBA_GREEN   = { 0.0f, 1.0f, 0.0f,  1.0f };
constexpr ColorRGBA RGBA_BLUE    = { 0.0f, 0.0f, 1.0f,  1.0f };
constexpr ColorRGBA RGBA_CYAN    = { 0.0f, 1.0f, 1.0f,  1.0f };
constexpr ColorRGBA RGBA_YELLOW  = { 1.0f, 1.0f, 0.0f,  1.0f };
constexpr ColorRGBA RGBA_MAGENTA = { 1.0f, 0.0f, 1.0f,  1.0f };
constexpr ColorRGBA RGBA_GRAY    = { 0.5f, 0.5f, 0.5f,  1.0f };
constexpr ColorRGBA RGBA_BROWN   = { 0.6f, 0.4f, 0.12f, 1.0f };


namespace rdr
{

class CRenderer
{
public:
    /// Default Constructor
    constexpr CRenderer() noexcept
    { };

    /// Default Destructor
    ~CRenderer() = default;

    void Initialize      ( void ) noexcept;

    void ClearColorBuffer( void ) noexcept;

    void SetOrtho        ( const math::CVector2f& vBottomLeft, const math::CVector2f& vTopRight ) noexcept;
    void SetLineWidth    ( float fLineWidth ) noexcept;
    void SetPointSize    ( float fPointSize ) noexcept;
    void SetColor        ( const ColorRGBA& clr ) noexcept;
    void SetClearColor   ( const ColorRGBA& clr ) noexcept;

    void TranslateView   ( const math::CVector2f& vTranslate ) noexcept;
    void RotateView      ( float fDegrees ) noexcept;

    void ScaleView       ( float fUniformScale ) noexcept;
    void PushView        ( void ) noexcept;
    void PopView         ( void ) noexcept;

    void SetViewPort     ( int iX, int iY, int iWidth, int iHeight ) noexcept;

    void DrawPoint       ( const math::CVector2f& vCenter, const ColorRGBA& clr, float fPointSize ) noexcept;

    void DrawLine        ( const math::CVector2f& vStart, const math::CVector2f& vEnd ) noexcept;
    void DrawLine        ( const math::CVector2f& vStart, const math::CVector2f& vEnd, const ColorRGBA& clr, float fLineWidth = 1.f ) noexcept;

    void DrawPolygon     ( const math::CVector2f& vCenter, float fRadius, size_t nSides, float fDegOrientation ) noexcept;
    void DrawPolygon     ( const math::CVector2f*& rgVertices, size_t nVertices, float fDegOrientation ) noexcept;
    void DrawPolygon     ( const std::vector<math::CVector2f>& rgVertices, float fDegOrientation ) noexcept;

    void DrawQuad        ( const math::CVector2f rgVertices[4], const ColorRGBA& clr ) noexcept;
    void DrawAABB        ( const CAABB2& aabb, const ColorRGBA& clr) noexcept;

    void DrawTexturedAABB( const CAABB2& aabb, const CTexture& texture, const ColorRGBA& clrTint,
                           const math::CVector2f& vTexCoordMins = math::CVector2f(0.f, 0.f), 
                           const math::CVector2f& vTexCoordMaxs = math::CVector2f(1.f, 1.f) ) noexcept;

};


} // namespace rdr

_declspec(selectany) rdr::CRenderer g_theRdr;

} // namespace eng



#endif