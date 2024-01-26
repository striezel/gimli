/*
 -------------------------------------------------------------------------------
    This file is part of the Generic Image Library (gimli) example applications.
    Copyright (C) 2022, 2024  Dirk Stolle

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 -------------------------------------------------------------------------------
*/

#include "versions.hpp"
#include <iostream>
#include <jpeglib.h>
#include <png.h>
#include <boost/version.hpp>
#if defined(__has_include)
  #if __has_include(<boost/gil/version.hpp>)
    #include <boost/gil/version.hpp>
  #endif
#endif

void library_versions()
{
  std::cout << "Library versions:\n"
            << "  * Boost " << (BOOST_VERSION / 100000) << "." << ((BOOST_VERSION / 100) % 1000) << "." << (BOOST_VERSION % 100) << '\n'
            #if defined(__has_include)
              #if __has_include(<boost/gil/version.hpp>)
            << "  * Boost GIL: API version " << BOOST_GIL_VERSION << ", library version " << BOOST_GIL_LIB_VERSION << '\n'
              #endif
            #endif
            << "  * libjpeg " << JPEG_LIB_VERSION << " (compile time version)\n"
            << "  * libpng " << png_get_header_ver(nullptr) << std::endl;
}
