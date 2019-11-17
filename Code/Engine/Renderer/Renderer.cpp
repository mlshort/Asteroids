/**
 *  @file       Renderer.cpp
 *  @brief      CRenderer class implementation
 *
 *  @author     Mark L. Short
 *  @date       May 7, 2017
 *
 *
 */

#define WIN32_LEAN_AND_MEAN
#include "targetver.h"  // this needs to be the 1st header included

#include <Windows.h>
#include <gl/gl.h>
#include <stdlib.h>

#include "Renderer.h"

#pragma comment( lib, "opengl32" ) // Link in the OpenGL32.lib static library


namespace eng
{
namespace rdr
{

using  namespace eng::math;

constexpr float g_fDefaultLineWidth = 2.f;

//-----------------------------------------------------------------------------------------------
void CRenderer::Initialize(void) noexcept
{
    glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
    glLineWidth( g_fDefaultLineWidth );
    glEnable( GL_LINE_SMOOTH );
};

//-----------------------------------------------------------------------------------------------
void CRenderer::ClearColorBuffer(void) noexcept
{
    glClear( GL_COLOR_BUFFER_BIT );
};

//-----------------------------------------------------------------------------------------------
void CRenderer::SetViewPort( int iX, int iY, int iWidth, int iHeight ) noexcept
{
    glViewport(iX, iY, iWidth, iHeight);
};

//-----------------------------------------------------------------------------------------------
void CRenderer::SetOrtho( const CVector2f& vBottomLeft, const CVector2f& vTopRight ) noexcept
{
    glLoadIdentity();
    glOrtho(vBottomLeft.X, vTopRight.X, vBottomLeft.Y, vTopRight.Y, 0.f, 1.f);
};

//-----------------------------------------------------------------------------------------------
void CRenderer::SetLineWidth ( float fLineWidth ) noexcept
{
    glLineWidth( fLineWidth );
};

//-----------------------------------------------------------------------------------------------
void CRenderer::SetColor     ( const ColorRGBA& clr ) noexcept
{
    glColor4f( clr.fRed, clr.fGreen, clr.fBlue, clr.fAlpha );
};

//-----------------------------------------------------------------------------------------------
void CRenderer::SetPointSize ( float fPointSize ) noexcept
{
    glPointSize( fPointSize );
};

//-----------------------------------------------------------------------------------------------
void CRenderer::SetClearColor (const ColorRGBA& clr ) noexcept
{
    glClearColor( clr.fRed, clr.fGreen, clr.fBlue, clr.fAlpha );
};

//-----------------------------------------------------------------------------------------------
void CRenderer::TranslateView( const CVector2f& vTranslate ) noexcept
{
    glTranslatef( vTranslate.X, vTranslate.Y, 0.f );
};

//-----------------------------------------------------------------------------------------------
void CRenderer::RotateView( float fDegrees ) noexcept
{
    glRotatef( fDegrees, 0.f, 0.f, 1.f );
};

//-----------------------------------------------------------------------------------------------
void CRenderer::ScaleView( float fUniformScale ) noexcept
{
    glScalef(fUniformScale, fUniformScale, 1.f);
};

//-----------------------------------------------------------------------------------------------
void CRenderer::PushView(void) noexcept
{
    glPushMatrix();
};

//-----------------------------------------------------------------------------------------------
void CRenderer::PopView(void) noexcept
{
    glPopMatrix();
};

//-----------------------------------------------------------------------------------------------
void CRenderer::DrawLine( const CVector2f& vStart, const CVector2f& vEnd) noexcept
{
    glDisable( GL_TEXTURE_2D ); // need to disable texturing before drawing non-textured objects
    glBegin ( GL_LINES );
    {
        glVertex2f( vStart.X, vStart.Y );
        glVertex2f( vEnd.X,   vEnd.Y );
    }
    glEnd();
};

//-----------------------------------------------------------------------------------------------
void CRenderer::DrawPoint( const CVector2f& vCenter, const ColorRGBA& clr, float fPointSize ) noexcept
{
    glPointSize( fPointSize );
    glColor4f  ( clr.fRed, clr.fGreen, clr.fBlue, clr.fAlpha );

    glBegin( GL_POINTS );
        glVertex2f( vCenter.X, vCenter.Y );
    glEnd();
};

//-----------------------------------------------------------------------------------------------
void CRenderer::DrawLine( const CVector2f& vStart, const CVector2f& vEnd, const ColorRGBA& clr, float fLineWidth /* = 1.f */) noexcept
{
    glLineWidth( fLineWidth );
    glColor4f  ( clr.fRed, clr.fGreen, clr.fBlue, clr.fAlpha );

    DrawLine( vStart, vEnd );

    return;
};

//-----------------------------------------------------------------------------------------------
void CRenderer::DrawPolygon( const CVector2f& vCenter, float fRadius, size_t nSides, float fDegOrientation ) noexcept
{
    const float RADIANS_PER_SIDE = static_cast<float>( eng::math::RADIANS_PER_CIRCLE / nSides );

    // Orientation of the polygon (in Radians)
    float fRadOrientation = eng::math::DegreesToRadians( fDegOrientation );

    glBegin ( GL_LINE_LOOP );
    {
        for (float fRadCurrent = 0.f; fRadCurrent < eng::math::RADIANS_PER_CIRCLE; fRadCurrent += RADIANS_PER_SIDE)
        {
            float x  = vCenter.X + (fRadius * std::cos(fRadCurrent + fRadOrientation));
            float y  = vCenter.Y + (fRadius * std::sin(fRadCurrent + fRadOrientation));
            glVertex2f(x, y);
        }
    }
    glEnd();

    return;
};

//-----------------------------------------------------------------------------------------------
void CRenderer::DrawPolygon( const CVector2f*& rgVertices, size_t nVertices, float fDegOrientation ) noexcept
{
    glPushMatrix();

    glRotatef   ( fDegOrientation, 0.f, 0.f, 1.f );

    glBegin ( GL_LINE_LOOP );
    {
        const CVector2f* pV = &rgVertices[0];
        for ( size_t i = 0; i < nVertices; i++)
        {
            glVertex2f( pV[i].X, pV[i].Y );
        }
    }
    glEnd();

    glPopMatrix();

    return;
};

//-----------------------------------------------------------------------------------------------
void CRenderer::DrawPolygon( const std::vector<CVector2f>& rgVertices, float fDegOrientation ) noexcept
{
    glPushMatrix();

    glRotatef   ( fDegOrientation, 0.f, 0.f, 1.f );

    glBegin ( GL_LINE_LOOP );
    {
        for ( auto v : rgVertices)
        {
            glVertex2f( v.X, v.Y );
        }
    }
    glEnd();

    glPopMatrix();

    return;
};

void CRenderer::DrawTexturedAABB( const CAABB2& aabb, const CTexture& texture, const ColorRGBA& tint,
                                  const CVector2f& vTexCoordMins, const CVector2f& vTexCoordMaxs ) noexcept
{
    glColor4f    ( tint.fRed, tint.fGreen, tint.fBlue, tint.fAlpha );
    glEnable     ( GL_TEXTURE_2D );
    glBindTexture( GL_TEXTURE_2D,  texture.get_TextureID() );

    glBegin(GL_QUADS);
    {
        glTexCoord2f(vTexCoordMins.X, vTexCoordMaxs.Y); glVertex2f(aabb.get_Min().X, aabb.get_Min().Y);
        glTexCoord2f(vTexCoordMaxs.X, vTexCoordMaxs.Y); glVertex2f(aabb.get_Max().X, aabb.get_Min().Y);
        glTexCoord2f(vTexCoordMaxs.X, vTexCoordMins.Y); glVertex2f(aabb.get_Max().X, aabb.get_Max().Y);
        glTexCoord2f(vTexCoordMins.X, vTexCoordMins.Y); glVertex2f(aabb.get_Min().X, aabb.get_Max().Y);
    }
    glEnd();
 
    return;
};

void CRenderer::DrawQuad        ( const CVector2f rgVertices[4], const ColorRGBA& clr ) noexcept
{ 
    glColor4f  ( clr.fRed, clr.fGreen, clr.fBlue, clr.fAlpha );
    glBegin ( GL_QUADS );
    {
        for ( size_t i = 0; i < 4; i++)
        {
            glVertex2f( rgVertices[i].X, rgVertices[i].Y );
        }
    }
    glEnd();

    return;
};

void CRenderer::DrawAABB        ( const CAABB2& aabb, const ColorRGBA& clr ) noexcept
{ 
    glColor4f( clr.fRed, clr.fGreen, clr.fBlue, clr.fAlpha );
    glDisable( GL_TEXTURE_2D ); // need to disable texturing before drawing non-textured objects
    glBegin  ( GL_QUADS );
    {
        glVertex2f( aabb.get_Min().X, aabb.get_Min().Y );
        glVertex2f( aabb.get_Max().X, aabb.get_Min().Y );
        glVertex2f( aabb.get_Max().X, aabb.get_Max().Y );
        glVertex2f( aabb.get_Min().X, aabb.get_Max().Y );
    }
    glEnd();

    return;
};



}  // namespace rdr
}  // namespace eng
