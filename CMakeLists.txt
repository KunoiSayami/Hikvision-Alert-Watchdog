# CMakeList.txt: AlertWatchdog 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)

project ("AlertWatchdog")

# 将源代码添加到此项目的可执行文件。
add_executable (AlertWatchdog "AlertWatchdog.cpp" "AlertWatchdog.h" "upload.cpp" "libhikvision.cpp")
include_directories(include)

# TODO: 如有需要，请添加测试并安装目标。
ADD_LIBRARY(libcurl STATIC IMPORTED)
IF (CMAKE_SYSTEM_NAME MATCHES "Linux")         
    MESSAGE ( STATUS "current platform: Linux")
    SET_TARGET_PROPERTIES (libcurl PROPERTIES
        IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/lib/linux/libcurl.a)
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Windows")
    MESSAGE (STATUS "current platform: Windows")
    SET_TARGET_PROPERTIES (libcurl PROPERTIES
        IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/lib/windows/libcurl_a.lib)
ENDIF (CMAKE_SYSTEM_NAME MATCHES "Linux")
TARGET_LINK_LIBRARIES (AlertWatchdog libcurl)