cmake_minimum_required (VERSION 3.8...3.31)

# test binary for components and functions
project(hobbit)

set(hobbit_sources
    ../../lib/io/BitmapLoader.hpp
    ../../lib/io/BitmapWriter.hpp
    ../../lib/io/JpegLoader.hpp
    ../../lib/io/Loader.hpp
    ../../lib/io/PngLoader.hpp
    ../../lib/io/TargaLoader.hpp
    ../../lib/io/TargaWriter.hpp
    ../../lib/io/WebpLoader.hpp
    ../../lib/io/WebpWriter.hpp
    ../../lib/io/Writer.hpp
    ../../lib/io/load_any.cpp
    ../../lib/io/write_any.cpp
    ../../lib/transforms/Resize.hpp
    ../../lib/types/get_type.cpp
    ../../lib/types/is_bitmap.cpp
    ../../lib/types/is_jpeg.cpp
    ../../lib/types/is_png.cpp
    ../../lib/types/is_targa.cpp
    ../../lib/types/is_webp.cpp
    ../versions.cpp
    hobbit.cpp
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
add_executable(hobbit ${hobbit_sources})

# GNU GCC before 9.1.0 needs to link to libstdc++fs explicitly.
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS "9.1.0")
  target_link_libraries(hobbit stdc++fs)
endif ()

# Clang before 9.0 needs to link to libc++fs explicitly.
if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang" AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS "9.0")
  if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS "8.0")
    # If we are on Clang 7.x, then the filesystem library from GCC is better.
    target_link_libraries(hobbit stdc++fs)
  else ()
    # Use Clang's C++ filesystem library, it is recent enough.
    target_link_libraries(hobbit c++fs)
  endif ()
endif ()

# libjpeg for reading JPEG images
find_package (JPEG)
if (JPEG_FOUND)
  include_directories(${JPEG_INCLUDE_DIR})
  target_link_libraries (hobbit ${JPEG_LIBRARIES})
else ()
  message ( FATAL_ERROR "libjpeg was not found!" )
endif (JPEG_FOUND)

# libpng for reading PNG images
find_package (PNG)
if (PNG_FOUND)
  include_directories(${PNG_INCLUDE_DIRS})
  target_link_libraries (hobbit ${PNG_LIBRARIES})
else ()
  message ( FATAL_ERROR "libpng was not found!" )
endif (PNG_FOUND)

# #################### #
# tests for executable #
# #################### #

# add tests for --version and --help parameters
# default help parameter "--help"
add_test(NAME hobbit_help
         COMMAND $<TARGET_FILE:hobbit> --help)

# short help parameter with question mark "-?"
add_test(NAME hobbit_help_question_mark
         COMMAND $<TARGET_FILE:hobbit> -?)

# Windows-style help parameter "/?"
if (NOT DEFINED ENV{GITHUB_ACTIONS} OR NOT MINGW)
    add_test(NAME hobbit_help_question_mark_windows
             COMMAND $<TARGET_FILE:hobbit> /?)
endif ()

# parameter to show version number
add_test(NAME hobbit_version
         COMMAND $<TARGET_FILE:hobbit> --version)
