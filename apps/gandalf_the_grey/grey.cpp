/*
 -------------------------------------------------------------------------------
    This file is part of the Generic Image Library (gimli).
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

#include "grey.hpp"
#include <filesystem>
#include <iostream>
#include "../return_codes.hpp"
#include "../../lib/io/load_any.hpp"
#include "../../lib/io/write_any.hpp"
#include "../../lib/transforms/Greyscale.hpp"
#include "../../lib/types/get_type.hpp"

int gandalf_the_grey(const std::filesystem::path& file)
{
  const auto img_type = gimli::types::get_type(file);
  if (!img_type.has_value())
  {
    std::cout << "Warning: Could not determine image type of " << file
              << "!\nError message: " << img_type.error() << "\n"
              << "File will be skipped.\n";
    return 0;
  }
  if (img_type.value() == gimli::types::ImageType::Unknown)
  {
    std::cerr << "'I have no memory of this place.' - Gandalf\n"
              << "Error: File " << file << " has an unknown or unsupported image format.\n";
    return rcUnsupportedFormat;
  }

  const auto maybe_image = gimli::load_any(file, img_type.value());
  if (!maybe_image.has_value())
  {
    std::cerr << "Error: File " << file.string() << " could not be loaded.\n"
              << "Error: " << maybe_image.error() << "\n";
    return rcInputOutputError;
  }

  const auto maybe_grey = gimli::Greyscale::transform(maybe_image.value());
  if (!maybe_grey.has_value())
  {
    std::cerr << "Error: File " << file << " could not be transformed to greyscale image.\n"
              << "Error: " << maybe_grey.error() << "\n";
    return rcInputOutputError;
  }

  const std::filesystem::path grey_file = grey_name(file);
  const auto error_text = gimli::write_any_grey(grey_file, maybe_grey.value(), img_type.value());
  if (error_text.has_value())
  {
    std::cerr << "Error: Greyscale version of " << file.string() << " could not be written to file "
              << grey_file << ".\n"
              << "Error: " << error_text.value() << "\n";
    return rcInputOutputError;
  }
  std::cout << file << " -> " << grey_file << "\n";

  return 0;
}

std::filesystem::path grey_name(std::filesystem::path path)
{
  namespace fs = std::filesystem;

  const auto ext = path.extension();
  const auto stem = path.stem();

  fs::path grey{stem};
  grey += std::string("_grey");
  grey += ext;
  path.replace_filename(grey);
  std::error_code error;
  uint_least32_t counter = 0;
  while (fs::exists(path, error) && !error)
  {
    ++counter;
    grey = stem;
    grey += std::string("_grey_");
    grey += std::to_string(counter);
    grey += ext;
    path.replace_filename(grey);
  }
  return path;
}
