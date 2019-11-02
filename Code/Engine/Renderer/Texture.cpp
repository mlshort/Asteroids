/**
 *  @file       Texture.cpp
 *  @brief      CTexture class implementation
 *
 *  @author     Mark L. Short
 *  @date       May 7, 2017
 *
 *  <b>Cite:</b>
 *
 */

#define WIN32_LEAN_AND_MEAN
#include "targetver.h"   // this needs to be the 1st header included

#include <windows.h>
#include <gl/gl.h>

#include "stb_image.h"

#include "Texture.h"

namespace eng
{
namespace rdr
{
//---------------------------------------------------------------------------
std::map< std::string, CTexture* >  CTexture::s_mapRegistry;

//---------------------------------------------------------------------------
constexpr CTexture::CTexture() noexcept
    : m_nOpenGLTextureID(0),
      m_vTexelSize(0, 0),
      m_iComponents(0)
{
};

//---------------------------------------------------------------------------
CTexture::~CTexture()
{
}

//---------------------------------------------------------------------------
bool CTexture::Init(const char* szImageFilePath)
{
    bool bReturn = false;

    int numComponentsRequested = STBI_default; // don't care; we support 3 (RGB) or 4 (RGBA)
    unsigned char* pImageData  = stbi_load(szImageFilePath, &m_vTexelSize.X, &m_vTexelSize.Y, &m_iComponents, numComponentsRequested);

    if (pImageData)
    {
        // Enable texturing
        glEnable(GL_TEXTURE_2D);

        // Tell OpenGL that our pixel data is single-byte aligned
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        // Ask OpenGL for an unused texName (ID number) to use for this texture
        glGenTextures(1, (GLuint*) &m_nOpenGLTextureID);

        // Tell OpenGL to bind (set) this as the currently active texture
        glBindTexture(GL_TEXTURE_2D, m_nOpenGLTextureID);

        // Set texture clamp vs. wrap (repeat)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP); // one of: GL_CLAMP or GL_REPEAT
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP); // one of: GL_CLAMP or GL_REPEAT

        // Set magnification (texel > pixel) and minification (texel < pixel) filters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); // one of: GL_NEAREST, GL_LINEAR
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);  // one of: GL_NEAREST, GL_LINEAR, GL_NEAREST_MIPMAP_NEAREST, GL_NEAREST_MIPMAP_LINEAR, GL_LINEAR_MIPMAP_NEAREST, GL_LINEAR_MIPMAP_LINEAR

        GLenum bufferFormat = GL_RGBA; // the format our source pixel data is currently in; any of: GL_RGB, GL_RGBA, GL_LUMINANCE, GL_LUMINANCE_ALPHA, ...
        if (m_iComponents == STBI_rgb )
            bufferFormat = GL_RGB;

        if (m_iComponents == STBI_rgb_alpha)
            bufferFormat = GL_RGBA;

        if (m_iComponents == STBI_grey_alpha)
            bufferFormat = GL_LUMINANCE_ALPHA;

        if (m_iComponents == STBI_grey)
            bufferFormat = GL_LUMINANCE;

        GLenum internalFormat = bufferFormat; // the format we want the texture to me on the card; allows us to translate into a different texture format as we upload to OpenGL

        // Upload this pixel data to our new OpenGL texture
        glTexImage2D(GL_TEXTURE_2D,     // Creating this as a 2d texture
                     0,                 // Which mipmap level to use as the "root" (0 = the highest-quality, full-res image), if mipmaps are enabled
                     internalFormat,    // Type of texel format we want OpenGL to use for this texture internally on the video card
                     m_vTexelSize.X,    // Texel-width of image; for maximum compatibility, use 2^N + 2^B, where N is some integer in the range [3,10], and B is the border thickness [0,1]
                     m_vTexelSize.Y,    // Texel-height of image; for maximum compatibility, use 2^M + 2^B, where M is some integer in the range [3,10], and B is the border thickness [0,1]
                     0,                 // Border size, in texels (must be 0 or 1)
                     bufferFormat,      // Pixel format describing the composition of the pixel data in buffer
                     GL_UNSIGNED_BYTE,  // Pixel color components are unsigned bytes (one byte per color/alpha channel)
                     pImageData);	    // Location of the actual pixel data bytes/buffer

        stbi_image_free(pImageData);
        bReturn = true;
    }

    return bReturn;
}


//---------------------------------------------------------------------------
// Returns a pointer to the already-loaded texture of a given image file,
//	or nullptr if no such texture/image has been loaded.
//
CTexture* CTexture::GetTextureByName(const char* szImageFilePath)
{
    CTexture* pRetResult = nullptr;

    auto it = CTexture::s_mapRegistry.find(szImageFilePath);
    if (it != CTexture::s_mapRegistry.end())
        pRetResult = it->second;

    return pRetResult;
}


//---------------------------------------------------------------------------
// Finds the named Texture among the registry of those already loaded; if
//	found, returns that Texture*.  If not, attempts to load that texture,
//	and returns a Texture* just created (or nullptr if unable to load file).
//
CTexture* CTexture::CreateOrGetTexture(const char* szImageFilePath)
{
    CTexture* pRetResult = CTexture::GetTextureByName(szImageFilePath);

    if (pRetResult == nullptr)
    {
        pRetResult = new CTexture();
        if (pRetResult)
        {
            if (pRetResult->Init (szImageFilePath))
            {
                CTexture::s_mapRegistry[szImageFilePath] = pRetResult;
            }
            else 
            {
                // handle the error
                delete pRetResult;
                pRetResult = nullptr;
            }
        }
    }

    return pRetResult;
}

}
}