# We might support earlier versions, too, but try to use a more recent one.
cmake_minimum_required (VERSION 3.8)

# test binary for components and functions
project(gimli_tests)

set(gimli_tests_sources
    ../../lib/hash/average.cpp
    ../../lib/hash/difference.cpp
    ../../lib/hash/factory.hpp
    ../../lib/hash/minmax.cpp
    ../../lib/hash/similarity.hpp
    ../../lib/hash/stringify.hpp
    ../../lib/hash/vertical_difference.cpp
    ../../lib/io/BitmapLoader.hpp
    ../../lib/io/JpegLoader.hpp
    ../../lib/io/PngLoader.hpp
    ../../lib/io/TargaLoader.hpp
    ../../lib/io/WebpLoader.hpp
    ../../lib/io/Writer.hpp
    ../../lib/io/load_any.cpp
    ../../lib/io/write_any.cpp
    ../../lib/numeric/hamming.hpp
    ../../lib/transforms/Greyscale.cpp
    ../../lib/transforms/Resize.hpp
    ../../lib/types/get_type.cpp
    ../../lib/types/is_bitmap.cpp
    ../../lib/types/is_jpeg.cpp
    ../../lib/types/is_png.cpp
    ../../lib/types/is_targa.cpp
    ../../lib/types/is_webp.cpp
    hash/average.cpp
    hash/difference.cpp
    hash/factory.cpp
    hash/minmax.cpp
    hash/similarity.cpp
    hash/stringify.cpp
    hash/vertical_difference.cpp
    io/BitmapLoader.cpp
    io/JpegLoader.cpp
    io/PngLoader.cpp
    io/TargaLoader.cpp
    io/WebpLoader.cpp
    io/load_any.cpp
    io/write_any.cpp
    numeric/hamming.cpp
    transforms/Greyscale.cpp
    transforms/Resize.cpp
    types/get_type.cpp
    types/is_bitmap.cpp
    types/is_jpeg.cpp
    types/is_png.cpp
    types/is_targa.cpp
    types/is_webp.cpp
    main.cpp)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    add_definitions (-Wall -fexceptions)
endif ()
if (CODE_COVERAGE)
    add_definitions (-O0)
else()
    add_definitions (-O2)
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set( CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -s" )
add_executable(gimli_tests ${gimli_tests_sources})

# GNU GCC before 9.1.0 needs to link to libstdc++fs explicitly.
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS "9.1.0")
  target_link_libraries(gimli_tests stdc++fs)
endif ()

# Clang before 9.0 needs to link to libc++fs explicitly.
if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang" AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS "9.0")
  if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS "8.0")
    # If we are on Clang 7.x, then the filesystem library from GCC is better.
    target_link_libraries(gimli_tests stdc++fs)
  else ()
   # Use Clang's C++ filesystem library, it is recent enough.
   target_link_libraries(gimli_tests c++fs)
  endif ()
endif ()

# libjpeg for reading JPEG images
find_package (JPEG)
if (JPEG_FOUND)
  include_directories(${JPEG_INCLUDE_DIR})
  target_link_libraries (gimli_tests ${JPEG_LIBRARIES})
else ()
  message ( FATAL_ERROR "libjpeg was not found!" )
endif (JPEG_FOUND)

# libpng for reading PNG images
find_package (PNG)
if (PNG_FOUND)
  include_directories(${PNG_INCLUDE_DIRS})
  target_link_libraries (gimli_tests ${PNG_LIBRARIES})
else ()
  message ( FATAL_ERROR "libpng was not found!" )
endif (PNG_FOUND)

# add test case
add_test(NAME test_gimli
         COMMAND $<TARGET_FILE:gimli_tests>)
