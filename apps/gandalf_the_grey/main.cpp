/*
 -------------------------------------------------------------------------------
    This file is part of the Generic Image Library (gimli).
    Copyright (C) 2022  Dirk Stolle

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
#include "grey.hpp"
#include "../return_codes.hpp"

void showVersion()
{
  std::cout << "gandalf-the-grey, version 0.2.0, 2022-03-12\n"
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
  std::cout << "gandalf-the-grey [OPTIONS] [FILE]\n"
            << "\n"
            << "Produces greyscale versions of images.\n"
            << "The original images will not be changed, greyscale versions are saved as\n"
            << "separate files with a file name suffix (usually '_grey').\n"
            << "\n"
            << "options:\n"
            << "  -? | --help     - Shows this help message.\n"
            << "  -v | --version  - Shows version information.\n"
            << "  FILE            - Sets the file name of image to convert to greyscale.\n"
            << "                    This option can occur multiple times, if multiple files\n"
            << "                    need to be processed.\n";
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

  if (files.empty())
  {
    std::cerr << "Error: No files have been specified for conversion to greyscale!\n"
              << "Hint: Image files can be specified as parameter to the program, like so:\n"
              << "\n\tgandalf-the-grey my_image.png another_image.jpeg\n";
    return rcInvalidParameter;
  }

  for (const std::string& file: files)
  {
    const int rc = gandalf_the_grey(file);
    if (rc != 0)
      return rc;
  }

  return 0;
}
