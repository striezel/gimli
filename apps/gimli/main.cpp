/*
 -------------------------------------------------------------------------------
    This file is part of the Generic Image Library (gimli).
    Copyright (C) 2022, 2024, 2025  Dirk Stolle

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
#include <optional>
#include <unordered_map>
#include <string>
#include <vector>
#include "likeness.hpp"
#include "../return_codes.hpp"
#include "../versions.hpp"

void showVersion()
{
  std::cout << "gimli, version 0.2.2, 2025-01-20\n"
            << "\n";
  library_versions();
  showLicenseInformation();
}

void showHelp()
{
  std::cout << "gimli [OPTIONS] [FILE]\n"
            << "\n"
            << "Tests how much images look like each other.\n"
            << "\n"
            << "options:\n"
            << "  -? | --help      - Shows this help message.\n"
            << "  -v | --version   - Shows version information.\n"
            << "  --hash=ALGORITHM - Sets the image hashing algorithm to ALGORITHM.\n"
            << "                     Allowed values for the algorithm are:\n"
            << "                         avg: Uses average hashing.\n"
            << "                         diff: Uses horizontal difference hashing.\n"
            << "                         minmax: Uses minimum-maximum hashing.\n"
            << "                         vdiff: Uses vertical difference hashing.\n"
            << "                     If no algorithm is set explicitly, then the program\n"
            << "                     behaves as if --hash=diff is specified.\n"
            << "  FILE             - Sets the file name of an image to compare.\n"
            << "                     This option has to occur at least two times, because one\n"
            << "                     needs at least two images for a comparison.\n";
}

int main(int argc, char** argv)
{
  std::optional<gimli::hash::algorithm> algorithm {std::nullopt};
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
      else if ((param == "--hash=avg") || (param == "--average"))
      {
        if (algorithm.has_value())
        {
          std::cerr << "Error: Hashing algorithm was already set.\n";
          return rcInvalidParameter;
        }
        algorithm = gimli::hash::algorithm::average;
      }
      else if ((param == "--hash=diff") || (param == "--difference") || (param == "--diff"))
      {
        if (algorithm.has_value())
        {
          std::cerr << "Error: Hashing algorithm was already set.\n";
          return rcInvalidParameter;
        }
        algorithm = gimli::hash::algorithm::difference;
      }
      else if ((param == "--hash=minmax") || (param == "--minmax"))
      {
        if (algorithm.has_value())
        {
          std::cerr << "Error: Hashing algorithm was already set.\n";
          return rcInvalidParameter;
        }
        algorithm = gimli::hash::algorithm::minmax;
      }
      else if ((param == "--hash=vdiff") || (param == "--vertical-difference") || (param == "--vdiff"))
      {
        if (algorithm.has_value())
        {
          std::cerr << "Error: Hashing algorithm was already set.\n";
          return rcInvalidParameter;
        }
        algorithm = gimli::hash::algorithm::vertical_difference;
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

  if (files.size() < 2)
  {
    std::cerr << "Error: Not enough files have been specified for comparison!\n"
              << "Hint: At least two images are required. Image files can be "
              << "specified as parameter to the program, like so:\n"
              << "\n\tgimli my_image.png another_image.jpeg\n";
    return rcInvalidParameter;
  }

  if (!algorithm.has_value())
  {
    algorithm = gimli::hash::algorithm::difference;
  }

  std::unordered_map<std::string, uint64_t> hash_map;
  for (const auto& file: files)
  {
    const int rc = calculate_hash(file, hash_map, algorithm.value());
    if (rc != 0)
      return rc;
  }

  const auto sorted = sort_by_similarity(hash_map);
  std::cout << "Similarity of files:\n";
  for (const auto& element: sorted)
  {
    std::cout << to_percentage(std::get<2>(element)) << " "
              << std::get<0>(element) << " " << std::get<1>(element) << "\n";
  }

  return 0;
}
