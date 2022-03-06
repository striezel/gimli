# We might support earlier versions, too, but try to use a more recent one.
cmake_minimum_required (VERSION 3.8)

# test binary for components and functions
project(gimli_tests)

set(gimli_tests_sources
    ../../src/gimli/hash/average.cpp
    ../../src/gimli/loaders/JpegLoader.hpp
    ../../src/gimli/loaders/PngLoader.hpp
    ../../src/gimli/numeric/hamming.cpp
    ../../src/gimli/transforms/Greyscale.cpp
    ../../src/gimli/transforms/Resize.hpp
    hash/average.cpp
    loaders/JpegLoader.cpp
    loaders/PngLoader.cpp
    numeric/hamming.cpp
    transforms/Greyscale.cpp
    transforms/Resize.cpp
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
