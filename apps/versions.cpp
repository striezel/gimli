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

void library_versions()
{
  std::cout << "Library versions:\n"
            << "  * Boost " << (BOOST_VERSION / 100000) << "." << ((BOOST_VERSION / 100) % 1000) << "." << (BOOST_VERSION % 100) << '\n'
            << "  * libjpeg " << JPEG_LIB_VERSION << " (compile time version)\n"
            #ifdef LIBJPEG_TURBO_VERSION_NUMBER
            << "    provided by libjpeg-turbo " << (LIBJPEG_TURBO_VERSION_NUMBER / 1000000)
            << '.' << ((LIBJPEG_TURBO_VERSION_NUMBER / 1000) % 1000) << '.' << (LIBJPEG_TURBO_VERSION_NUMBER % 1000) << '\n'
            #endif // LIBJPEG_TURBO_VERSION_NUMBER
            << "  * libpng " << png_get_header_ver(nullptr) << std::endl;
}

void showLicenseInformation(const std::string_view years)
{
  std::cout << "\nCopyright (C) " << years << "  Dirk Stolle\n"
            << "License GPLv3+: GNU GPL version 3 or later <https://gnu.org/licenses/gpl.html>\n"
            << "This is free software: you are free to change and redistribute it under the\n"
            << "terms of the GNU General Public License version 3 or any later version.\n"
            << "There is NO WARRANTY, to the extent permitted by law.\n";
}
