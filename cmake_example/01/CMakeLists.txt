cmake_minimum_required (VERSION 3.5)

#检测系统是否支持 pow 函数
include (${CMAKE_ROOT}/Modules/CheckFunctionExists.cmake)

check_function_exists (pow HAVE_POW)

project (Demo)

set (Demo_VERSION_MAJOR 1)
set (Demo_VERSION_MINOR 0)

configure_file (
    "${PROJECT_SOURCE_DIR}/config.h.in"
    "${PROJECT_BINARY_DIR}/config.h"
    )

option (USE_MYMATH
    "use provided math implementation" ON)

if (USE_MYMATH)
    include_directories ("${PROJECT_SOURCE_DIR}/math")
    add_subdirectory (math)
    set (EXTRA_LIBS ${EXTRA_LIBS} MathFunctions)
endif (USE_MYMATH)

set (SOURCE_DIRECTORY . )

aux_source_directory (${SOURCE_DIRECTORY} DIR_SRCS)

add_executable (Demo main.cc)

target_link_libraries (Demo ${EXTRA_LIBS})

install (TARGETS Demo DESTINATION bin)
install (FILES "${PROJECT_BINARY_DIR}/config.h"
    DESTINATION include)

set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")


