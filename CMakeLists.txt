cmake_minimum_required (VERSION 3.8)

project ("AlertWatchdog")

include_directories(include)
add_executable (AlertWatchdog "AlertWatchdog.cpp" "AlertWatchdog.h" "upload.cpp" "libhikvision.cpp")

ADD_LIBRARY(libcurl STATIC IMPORTED)
#add_compile_definitions(CURL_STATICLIB)
#add_definitions(-DCURL_STATICLIB)

IF (CMAKE_SYSTEM_NAME MATCHES "Linux")         
    MESSAGE ( STATUS "current platform: Linux")
    ADD_LIBRARY(HCNetSDK SHARED IMPORTED)

    # libcurl
    SET_TARGET_PROPERTIES (libcurl PROPERTIES
        IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/lib/libcurl.a)

    SET_TARGET_PROPERTIES (HCNetSDK PROPERTIES
        IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/lib/libhcnetsdk.so)
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Windows")
    MESSAGE (STATUS "current platform: Windows")
    ADD_LIBRARY(HCNetSDK STATIC IMPORTED)
    # libcurl
    SET_TARGET_PROPERTIES (libcurl PROPERTIES
        IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/lib/libcurl_a.lib)

    # HCNetSDK
    SET_TARGET_PROPERTIES (HCNetSDK PROPERTIES
        IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/lib/HCNetSDK.lib)
ENDIF (CMAKE_SYSTEM_NAME MATCHES "Linux")

TARGET_LINK_LIBRARIES (AlertWatchdog libcurl HCNetSDK)