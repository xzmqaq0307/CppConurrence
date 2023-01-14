#
# (C) Copyright 2022, ZWSOFT Co., LTD. (Guangzhou) All Rights Reserved.
#

if(CC_PLATFORM STREQUAL "x64")
    set(platform_nameStyle_A "x64")
    set(platform_nameStyle_B "x64")
    set(platform_nameStyle_C "x64")
    set(platform_nameStyle_D "win64")
elseif(CC_PLATFORM STREQUAL "Win32")
    set(platform_nameStyle_A "x86")
    set(platform_nameStyle_B "Win32")
    set(platform_nameStyle_C "win32")
    set(platform_nameStyle_D "win32")
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(config_pathName "Debug")
elseif(CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
    set(config_pathName "Release")
endif()