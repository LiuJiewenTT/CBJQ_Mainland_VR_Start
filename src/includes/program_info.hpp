#ifndef PROGRAM_INFO_H
#define PROGRAM_INFO_H

#define UNICODE
#define _UNICODE

// 修改版本号去version.rc改
#include "version.rc"
#define PROGRAM_VERSION VER_PRODUCTVERSION_STR
#define PROGRAMFILE_VERSION VER_FILEVERSION_STR

#define BUILD_TIMEZONE "UTC+8"

#ifdef __GNUC__
    const char *get_gcc_version();
    const char *get_gcc_build_description();
    #define GCC_VERSION get_gcc_version()
    #define BUILD_DATE __DATE__
    #define BUILD_TIME __TIME__

    #define BUILDER "GNUC"
    #ifdef __cplusplus
    #define BUILDER_SPECIFIC "GNUC(G++)"
    #else
    #define BUILDER_SPECIFIC "GNUC(GCC)"
    #endif
    #define BUILD_DESCRIPTION get_gcc_build_description()
#else
    const char *get_build_description();
    #ifdef __DATE__
    #define BUILD_DATE __DATE__
    #else
    #define BUILD_DATE "Unknown"
    #endif

    #ifdef __TIME__
    #define BUILD_TIME __TIME__
    #else
    #define BUILD_TIME "Unknown"
    #endif

    #define BUILDER "Unknown"
    #define BUILD_DESCRIPTION get_build_description()
#endif

const char *get_program_info_string();
#define PROGRAM_INFO_STRING get_program_info_string()

#endif  //  PROGRAM_INFO_H