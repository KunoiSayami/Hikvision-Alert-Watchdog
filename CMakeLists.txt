cmake_minimum_required (VERSION 3.8)

project ("AlertWatchdog")

include_directories(include)
add_executable (AlertWatchdog "AlertWatchdog.cpp" "AlertWatchdog.h" "upload.cpp" "libhikvision.cpp")

ADD_LIBRARY(libcurl STATIC IMPORTED)
ADD_LIBRARY(HCNetSDK STATIC IMPORTED)

IF (CMAKE_SYSTEM_NAME MATCHES "Linux")         
    MESSAGE ( STATUS "current platform: Linux")
    set(_PLATFORM_DIR "linux")
    
    # libcurl
    SET_TARGET_PROPERTIES (libcurl PROPERTIES
      IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/lib/linux/libcurl.a)
      
    TARGET_LINK_LIBRARIES (AlertWatchdog libcurl)   
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Windows")
    MESSAGE (STATUS "current platform: Windows")
    set(_PLATFORM_DIR "windows")

    # libcurl
    SET_TARGET_PROPERTIES (libcurl PROPERTIES
        IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/lib/windows/libcurl_a.lib)

    # HCNetSDK
    SET_TARGET_PROPERTIES (HCNetSDK PROPERTIES
        IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/lib/${_PLATFORM_DIR}/HCNetSDK.lib)
    TARGET_LINK_LIBRARIES (AlertWatchdog libcurl HCNetSDK)
ENDIF (CMAKE_SYSTEM_NAME MATCHES "Linux")