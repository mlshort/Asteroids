/**
 *  @file       EngineVersion.h
 *  @brief      Maintains engine subsystem version and build number constants
 *
 *  @author     Mark L. Short
 *  @date       May 7, 2017
 *
 *
 */

#pragma once

#if !defined(__ENGINE_VERSION_H__)
#define __ENGINE_VERSION_H__

#ifndef __PRODUCT_VER_H__
    #include "ProductVer.h"
#endif

#define FILEVER_BASE     1,0,4,
#define SPECIAL_BUILD    $Change: 1473 $

#define FILE_VERSION         xglue(FILEVER_BASE, NUM_BUILD)
#define PRODUCT_VERSION      xglue(PRODUCT_BASE, NUM_BUILD)
#define STR_FILE_VERSION     xstr(FILE_VERSION)
#define STR_PRODUCT_VERSION  xstr(PRODUCT_VERSION)
#define STR_SPECIAL_BUILD    xstr(SPECIAL_BUILD)

#endif

