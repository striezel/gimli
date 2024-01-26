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
#include <optional>
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
#include "../return_codes.hpp"
#include "hobbit.hpp"

void showVersion()
{
  std::cout << "hobbit, version 0.1.1, 2024-01-26\n"
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
  std::cout << "hobbit [OPTIONS] [FILE]\n"
            << "\n"
            << "Resizes images.\n"
            << "The original images will not be changed, resized versions are saved as\n"
            << "separate files with a file name suffix (usually containing the size).\n"
            << "\n"
            << "options:\n"
            << "  -? | --help         - Shows this help message.\n"
            << "  -v | --version      - Shows version information.\n"
            << "  --size WIDTHxHEIGHT - Sets the new image size in pixels (WIDTH pixels wide\n"
            << "                        and HEIGHT pixels high).\n"
            << "  FILE                - Sets the file name of the image to resize.\n"
            << "                        This option can occur multiple times, if multiple files\n"
            << "                        need to be processed.\n";
}

int main(int argc, char** argv)
{
  std::vector<std::string> files;
  std::optional<boost::gil::point_t> dimension = std::nullopt;
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
      else if ((param == "--size") || (param == "-s"))
      {
        if (dimension.has_value())
        {
          std::cerr << "Error: Dimension was already set to "
                    << dimension.value().x << "x" << dimension.value().y
                    << "!" << std::endl;
          return rcInvalidParameter;
        }
        // enough parameters?
        if ((i+1 < argc) && (argv[i+1] != nullptr))
        {
          const auto maybe_dim = parse_size(argv[i+1]);
          if (!maybe_dim.has_value())
          {
            std::cerr << "Error while parsing dimension value: "
                      << maybe_dim.error() << std::endl;
            return rcInvalidParameter;
          }
          dimension = maybe_dim.value();
          // Skip next parameter, because it's already used as dimension.
          ++i;
        }
        else
        {
          std::cerr << "Error: You have to enter a dimension value after \""
                    << param << "\"." << std::endl;
          return rcInvalidParameter;
        }
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

  if (files.empty())
  {
    std::cerr << "Error: No files have been specified to resize!\n"
              << "Hint: Image files can be specified as parameter to the program, like so:\n"
              << "\n\thobbit --size 123x456 my_image.png another_image.jpeg\n";
    return rcInvalidParameter;
  }

  if (!dimension.has_value())
  {
    std::cerr << "Error: No dimension has been specified for resize operation!\n"
              << "Hint: The new dimension can be specified as parameter to the program, like so:\n"
              << "\n\thobbit --size 123x456 my_image.png another_image.jpeg\n";
    return rcInvalidParameter;
  }

  for (const std::string& file: files)
  {
    const int rc = hobbit(file, dimension.value());
    if (rc != 0)
      return rc;
  }

  return 0;
}
