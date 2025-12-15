cmake_minimum_required (VERSION 3.8...3.31)

project(legolas)

set(legolas_sources
    ../../lib/io/BitmapLoader.hpp
    ../../lib/io/JpegLoader.hpp
    ../../lib/io/Loader.hpp
    ../../lib/io/PngLoader.hpp
    ../../lib/io/TargaLoader.hpp
    ../../lib/io/WebpLoader.hpp
    ../../lib/io/load_any.cpp
    ../../lib/types/get_type.cpp
    ../../lib/types/is_bitmap.cpp
    ../../lib/types/is_jpeg.cpp
    ../../lib/types/is_png.cpp
    ../../lib/types/is_targa.cpp
    ../../lib/types/is_webp.cpp
    ../versions.cpp
    legolas.cpp
    main.cpp)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    add_definitions (-Wall -Wextra -Wpedantic -pedantic-errors -Wshadow -fexceptions)

    if (CODE_COVERAGE OR ENABLE_SANITIZER)
        add_definitions (-O0)
    else()
        add_definitions (-O2)
        set( CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -s" )
    endif()
endif ()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_executable(legolas ${legolas_sources})

# GNU GCC before 9.1.0 needs to link to libstdc++fs explicitly.
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS "9.1.0")
  target_link_libraries(legolas stdc++fs)
endif ()

# Clang before 9.0 needs to link to libc++fs explicitly.
if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang" AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS "9.0")
  if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS "8.0")
    # If we are on Clang 7.x, then the filesystem library from GCC is better.
    target_link_libraries(legolas stdc++fs)
  else ()
    # Use Clang's C++ filesystem library, it is recent enough.
    target_link_libraries(legolas c++fs)
  endif ()
endif ()

# libjpeg for reading JPEG images
find_package (JPEG)
if (JPEG_FOUND)
  include_directories(${JPEG_INCLUDE_DIR})
  target_link_libraries (legolas ${JPEG_LIBRARIES})
else ()
  message ( FATAL_ERROR "libjpeg was not found!" )
endif (JPEG_FOUND)

# libpng for reading PNG images
find_package (PNG)
if (PNG_FOUND)
  include_directories(${PNG_INCLUDE_DIRS})
  target_link_libraries (legolas ${PNG_LIBRARIES})
else ()
  message ( FATAL_ERROR "libpng was not found!" )
endif (PNG_FOUND)

# #################### #
# tests for executable #
# #################### #

# add tests for --version and --help parameters
# default help parameter "--help"
add_test(NAME legolas_help
         COMMAND $<TARGET_FILE:legolas> --help)

# short help parameter with question mark "-?"
add_test(NAME legolas_help_question_mark
         COMMAND $<TARGET_FILE:legolas> -?)

# Windows-style help parameter "/?"
if (NOT DEFINED ENV{GITHUB_ACTIONS} OR NOT MINGW)
    add_test(NAME legolas_help_question_mark_windows
             COMMAND $<TARGET_FILE:legolas> /?)
endif ()

# parameter to show version number
add_test(NAME legolas_version
         COMMAND $<TARGET_FILE:legolas> --version)
