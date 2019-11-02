/**
 *  @file       IRenderable.h
 *  @brief      IRenderable abstract base class interface
 *
 *  @author     Mark L. Short
 *  @date       May 7, 2017
 *
 *
 */

#pragma once

#if !defined(__IRENDERABLE_H__)
#define __IRENDERABLE_H__

namespace eng
{


class __declspec(novtable) IRenderable
{
public:

    virtual ~IRenderable() = default;

    virtual void    Update(float fDeltaTime) = 0;
    virtual void    Render(void) const = 0;
};

}

#endif