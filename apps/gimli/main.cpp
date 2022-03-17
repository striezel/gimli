/*
 -------------------------------------------------------------------------------
    This file is part of the Generic Image Library (gimli).
    Copyright (C) 2022  Dirk Stolle

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

#include <filesystem>
#include <iostream>
#include <string>
#include <vector>
#include <jpeglib.h>
#include <png.h>
#include <boost/version.hpp>
#if defined(__has_include)
  #if __has_include(<boost/gil/version.hpp>)
    #include <boost/gil/version.hpp>
  #endif
#endif
#include "likeness.hpp"
#include "../return_codes.hpp"

void showVersion()
{
  std::cout << "gimli, version 0.1.0-pre, 2022-03-17\n"
            << "\n"
            << "Library versions:" << std::endl
            << "  * Boost " << (BOOST_VERSION / 100000) << "." << ((BOOST_VERSION / 100) % 1000) << "." << (BOOST_VERSION % 100) << std::endl
            #if defined(__has_include)
              #if __has_include(<boost/gil/version.hpp>)
            << "  * Boost GIL: API version " << BOOST_GIL_VERSION << ", library version " << BOOST_GIL_LIB_VERSION << std::endl
              #endif
            #endif
            << "  * libjpeg " << JPEG_LIB_VERSION << " (compile time version)" << std::endl
            << "  * libpng " << png_get_header_ver(nullptr) << std::endl;
}

void showHelp()
{
  std::cout << "gimli [OPTIONS] [FILE]\n"
            << "\n"
            << "Tests how much images look like each other.\n"
            << "\n"
            << "options:\n"
            << "  -? | --help     - Shows this help message.\n"
            << "  -v | --version  - Shows version information.\n"
            << "  FILE            - Sets the file name of an image to compare.\n"
            << "                    This option has to occur at least two times, because one\n"
            << "                    needs at least two images for a comparison.\n";
}

int main(int argc, char** argv)
{
  namespace fs = std::filesystem;

  std::vector<std::string> files;
  if ((argc > 1) && (argv != nullptr))
  {
    for (int i = 1; i < argc; ++i)
    {
      if (argv[i] == nullptr)
      {
        std::cerr << "Error: Parameter at index " << i << " is null pointer!\n";
        return rcInvalidParameter;
      }
      const std::string param(argv[i]);
      if ((param == "-v") || (param == "--version"))
      {
        showVersion();
        return 0;
      }
      else if ((param == "-?") || (param == "/?") || (param == "--help"))
      {
        showHelp();
        return 0;
      }
      else
      {
        // Parameter might be a file.
        std::error_code error;
        if (!std::filesystem::exists(param, error) || error)
        {
          std::cerr << "Error: File " << param << " does not exist!\n";
          return rcInvalidParameter;
        }
        files.emplace_back(param);
      }
    }
  } // if arguments are there

  if (files.size() < 2)
  {
    std::cerr << "Error: Not enough files have been specified for comparison!\n"
              << "Hint: At least two images are required. Image files can be "
              << "specified as parameter to the program, like so:\n"
              << "\n\tgimli my_image.png another_image.jpeg\n";
    return rcInvalidParameter;
  }

  Hashes reference_hash;
  // Load first image as reference image.
  {
    const auto grey_img = load_to_grey(files[0]);
    if (!grey_img.has_value())
    {
      return grey_img.error();
    }
    const auto maybe_hash = calculate_hashes(grey_img.value());
    if (!maybe_hash.has_value())
    {
      std::cerr << "Error: Hash calculation for " << files[0] << " failed!\n"
                << maybe_hash.error() << "\n";
      return rcInputOutputError;
    }
    reference_hash = maybe_hash.value();
  }

  std::cout << files[0] << " is set as reference image.\n";

  const std::vector<std::string>::size_type vector_size = files.size();
  for (std::vector<std::string>::size_type i = 1; i < vector_size; ++i)
  {
    const int rc = likeness(files[i], reference_hash);
    if (rc != 0)
      return rc;
  }

  return 0;
}
