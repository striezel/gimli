# gimli - the Generic Image Library

[![GitHub CI Clang status](https://github.com/striezel/gimli/workflows/Clang/badge.svg)](https://github.com/striezel/gimli/actions)
[![GitHub CI GCC status](https://github.com/striezel/gimli/workflows/GCC/badge.svg)](https://github.com/striezel/gimli/actions)
[![GitHub CI MSYS2 status](https://github.com/striezel/gimli/workflows/MSYS2/badge.svg)](https://github.com/striezel/gimli/actions)
[![GitLab pipeline status](https://gitlab.com/striezel/gimli/badges/main/pipeline.svg)](https://gitlab.com/striezel/gimli/)

gimli is a library that can load common image formats (such as JPEG or PNG)
and perform some basic operations on them.

_Note: The library is still in an early stage of development. So far it has only
very few features._

Furthermore, some example applications are provided that make use of the library
and its features. Currently, this includes the following applications:

* [`gandalf-the-grey`](./apps/gandalf_the_grey/readme.md) - produces greyscale
  versions of images
* [`gandalf-the-white`](./apps/gandalf_the_white/readme.md) - produces
  white-balanced versions of images
* [`gimli`](./apps/gimli/readme.md) - finds like images by hashes
* [`hobbit`](./apps/hobbit/readme.md) - resizes images to smaller (or larger)
  dimensions
* [`legolas`](./legolas/readme.md) - tests whether images are identical

_Note that those example applications are licensed under GNU GPL v3, whereas the
library code itself is licensed under the weaker copyleft license GNU LGPL v3._

## Building from source

### Prerequisites

To build gimli from source you need a C++ compiler with support for C++17,
CMake 3.8 or later, the Boost libraries (version 1.69+), the libjpeg library,
and the libpng library.
pkg-config is required to make it easier to find compiler options for the
installed libraries. Additionally, the library uses Catch (C++ Automated Test
Cases in Headers) to perform some tests.

It also helps to have Git, a distributed version control system, on your build
system to get the latest source code directly from the Git repository.

All of that can usually be installed by typing

    apt-get install catch cmake g++ git libboost-dev libjpeg-dev libpng-dev pkg-config

or

    yum install boost-devel catch-devel cmake gcc-c++ git libjpeg-devel libpng-devel pkgconfig

or

    apk add boost-dev catch2 cmake g++ git jpeg-dev libpng-dev make pkgconf

into a root terminal.

### Getting the source code

Get the source directly from Git by cloning the Git repository and change to
the directory after the repository is completely cloned:

    git clone https://gitlab.com/striezel/gimli.git
    cd gimli

That's it, you should now have the current source code on your machine.

### Build process

The build process is relatively easy, because CMake does all the preparations.
Starting in the root directory of the source, you can do the following steps:

    mkdir build
    cd build
    cmake ../
    cmake --build . --parallel

If you want to run the test suite, too, then there is one more step:

    ctest -V

## Building from source on Windows

For information how to build gimli on Windows, see the
[build instructions for MSYS2](./documentation/msys2-build.md).

## Copyright and Licensing

Copyright 2022, 2023, 2024, 2025  Dirk Stolle

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
