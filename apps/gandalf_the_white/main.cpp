/*
 -------------------------------------------------------------------------------
    This file is part of the Generic Image Library (gimli).
    Copyright (C) 2023, 2024, 2025  Dirk Stolle

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

#if defined(_WIN32) || defined(_WIN64)
#include <cstdlib>
#endif
#include <filesystem>
#include <iostream>
#include <string>
#include <vector>
#include "white.hpp"
#include "../return_codes.hpp"
#include "../versions.hpp"

void showVersion()
{
  std::cout << "gandalf-the-white, version 0.1.2, 2025-01-20\n"
            << "\n";
  library_versions();
  showLicenseInformation("2023, 2024, 2025");
}

void showHelp()
{
  std::cout << "gandalf-the-white [OPTIONS] [FILE]\n"
            << "\n"
            << "Produces white-balanced versions of images.\n"
            << "The original images will not be changed, white-balanced versions are saved as\n"
            << "separate files with a file name suffix (usually '_white').\n"
            << "\n"
            << "options:\n"
            << "  -? | --help     - Shows this help message.\n"
            << "  -v | --version  - Shows version information.\n"
            << "  FILE            - Sets the file name of image to be white-balanced.\n"
            << "                    This option can occur multiple times, if multiple files\n"
            << "                    need to be processed.\n";
}

int main(int argc, char** argv)
{
  std::vector<std::filesystem::path> files;
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
        std::filesystem::path file;
        try
        {
          #if !defined(_WIN32) && !defined(_WIN64)
          file = param;
          #else
          std::wstring utf16(param.size(), L'\0');
          const auto num_chars = std::mbstowcs(&utf16[0], param.c_str(), param.size());
          if (num_chars == static_cast<std::size_t>(-1))
          {
            std::cerr << "Error: " << param << " is not a valid parameter!\n";
            return rcInvalidParameter;
          }
          file = utf16.substr(0, num_chars);
          #endif
        }
        catch (...)
        {
          std::cerr << "Error: " << param << " is neither a valid parameter "
                    << "nor a valid file path!\n";
          return rcInvalidParameter;
        }
        std::error_code error;
        if (!std::filesystem::exists(file, error) || error)
        {
          std::cerr << "Error: File " << param << " does not exist!\n";
          return rcInvalidParameter;
        }
        files.emplace_back(file);
      }
    }
  } // if arguments are there

  if (files.empty())
  {
    std::cerr << "Error: No files have been specified for white-balancing!\n"
              << "Hint: Image files can be specified as parameter to the program, like so:\n"
              << "\n\tgandalf-the-white my_image.png another_image.jpeg\n";
    return rcInvalidParameter;
  }

  for (const std::filesystem::path& file: files)
  {
    const int rc = gandalf_the_white(file);
    if (rc != 0)
      return rc;
  }

  return 0;
}
