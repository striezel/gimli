# We might support earlier versions, too, but try to use a recent one.
cmake_minimum_required (VERSION 3.8)

add_subdirectory (gandalf_the_grey)
add_subdirectory (gimli)
if (NOT WIN32)
    # Shell scripts for hobbit are not translated to Windows CMD scripts yet.
    # Therefore, those tests are not run on Windows at the moment.
    add_subdirectory (hobbit)
endif ()
