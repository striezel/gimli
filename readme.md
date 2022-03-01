# gimli - the Generic Image Library

gimli will be a library that can load common image formats (such as JPEG or PNG)
and perform some basic operations on them.

_Note: The library is still in an early stage of development. So far it has only
very few features._

## Building from source

### Prerequisites

To build gimli from source you need a C++ compiler with support for C++17,
CMake 3.8 or later, the libjpeg library, and the libpng library.
pkg-config is required to make it easier to find compiler options for the
installed libraries. Additionally, the library uses Catch (C++ Automated Test
Cases in Headers) to perform some tests.

It also helps to have Git, a distributed version control system, on your build
system to get the latest source code directly from the Git repository.

All of that can usually be installed be typing

    apt-get install catch cmake g++ git libjpeg-dev libpng-dev pkg-config

or

    yum install catch cmake gcc-c++ git libjpeg-devel libpng-devel pkgconfig

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
    make -j4

If you want to run the test suite, too, then there is one more step:

    ctest -V

## Copyright and Licensing

Copyright 2022  Dirk Stolle

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
