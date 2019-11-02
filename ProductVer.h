/**
 *  @file       ProductVer.h
 *  @brief      Maintains global product version information
 *
 *  @author     Mark L. Short
 *  @date       May 7, 2017
 *
 *
 *  <b>Purpose:</b>
 *
 *  Purpose of this file is to provide one global point of reference to update
 *  and modify the build and product information to be uniformly shared across
 *  multiple projects (modules).
 *
 *  This information is ultimately included and compiled in each module's resource
 *  (.rc) file and becomes part of the VS_VERSION_INFO data.
 *
 *  For a better understanding of the following stringifying preprocessor macros
 *  see - http://www.decompile.com/cpp/faq/file_and_line_error_string.htm
 *
 */


/**
 *  @todo - generate the NUM_BUILD via a persisted Revision or Change # from the repository
 *
 *  On using Perforce as the repository, this is not currently implemented as Perforce
 *  does not directly provide a means to get a simple number string, but embeds this
 *  information in a complex string with other description information that requires
 *  pre-build parsing (i.e. "$Revision: #5 $").
 *
 */


#if !defined(__PRODUCT_VER_H__)
#define __PRODUCT_VER_H__

#define NUM_BUILD           3
#define PRODUCT_VER_BASE    1,0,0,

#define STR_PRODUCT_NAME    "Asteroids\0"
#define STR_COMPANY_NAME    "UALR\0"

#define str(s) #s
#define xstr(s) str(s)

#define glue(a,b)      a##b
#define xglue(a,b)     glue(a,b)

#endif
