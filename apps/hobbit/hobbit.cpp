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

#include "hobbit.hpp"
#include <filesystem>
#include <iostream>
#include "../return_codes.hpp"
#include "../../lib/io/load_any.hpp"
#include "../../lib/io/write_any.hpp"
#include "../../lib/transforms/Resize.hpp"
#include "../../lib/types/get_type.hpp"

int hobbit(const std::string& file, const boost::gil::point_t& new_size)
{
  const auto img_type = gimli::types::get_type(file);
  if (!img_type.has_value())
  {
    std::cout << "Warning: Could not determine image type of " << file
              << "!\nError message: " << img_type.error() << "\n"
              << "File will be skipped." << std::endl;
    return 0;
  }
  if (img_type.value() == gimli::types::ImageType::Unknown)
  {
    std::cerr << "Error: File " << file << " has an unknown or unsupported image format." << std::endl;
    return rcUnsupportedFormat;
  }

  const auto maybe_image = gimli::load_any(file, img_type.value());
  if (!maybe_image.has_value())
  {
    std::cerr << "Error: File " << file << " could not be loaded.\n"
              << "Error: " << maybe_image.error() << "\n";
    return rcInputOutputError;
  }

  const auto maybe_resized = gimli::Resize::transform(maybe_image.value(), new_size);
  if (!maybe_resized.has_value())
  {
    std::cerr << "Error: File " << file << " could not be resized.\n"
              << "Error: " << maybe_resized.error() << "\n";
    return rcInputOutputError;
  }

  const std::string resized_file = sized_name(file, new_size);
  const auto error_text = gimli::write_any_rgb(resized_file, maybe_resized.value(), img_type.value());
  if (error_text.has_value())
  {
    std::cerr << "Error: Resized version of " << file << " could not be written to file "
              << resized_file << ".\n"
              << "Error: " << error_text.value() << "\n";
    return rcInputOutputError;
  }
  std::cout << file << " -> " << resized_file << "\n";

  return 0;
}

std::string sized_name(const std::string& file, const boost::gil::point_t& dims)
{
  namespace fs = std::filesystem;

  fs::path path(file);
  const auto ext = path.extension();
  const auto stem = path.stem();

  fs::path grey(stem.native() + std::string("_resized") + ext.native());
  path.replace_filename(grey);
  std::error_code error;
  uint_least32_t counter = 0;
  while (fs::exists(path, error) && !error)
  {
    ++counter;
    grey = stem.native() + std::string("_resized_") + std::to_string(counter) + ext.native();
    path.replace_filename(grey);
  }
  return path;
}
