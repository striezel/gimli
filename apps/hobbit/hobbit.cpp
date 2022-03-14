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

nonstd::expected<boost::gil::point_t, std::string> parse_size(const std::string& data)
{
  const auto x_pos = data.find('x');
  if ((x_pos == std::string::npos) || (x_pos < 1) || (x_pos == data.size() - 1))
  {
    return nonstd::make_unexpected("'" + data + "' is not a valid dimension. "
      + std::string(" Dimensions should contains width and height as integers, separated by 'x'.")
      + " For example, '123x456' would be a proper dimension for width of 123 pixels and height of 456 pixels.");
  }
  const auto w_string = data.substr(0, x_pos);
  const auto h_string = data.substr(x_pos + 1);
  long long int w = 0;
  long long int h = 0;

  try
  {
    std::size_t pos = 0;
    w = std::stoll(w_string, &pos);
    if (pos != w_string.length())
    {
      return nonstd::make_unexpected("Dimension's width is not a valid integer.");
    }
    h = std::stoll(h_string, &pos);
    if (pos != h_string.length())
    {
      return nonstd::make_unexpected("Dimension's height is not a valid integer.");
    }
  }
  catch (const std::out_of_range& range_ex)
  {
    return nonstd::make_unexpected("Dimension value is out of range.");
  }
  catch (const std::invalid_argument& arg_ex)
  {
    return nonstd::make_unexpected("Dimension value is invalid.");
  }
  if ((w <= 0) || (h <= 0))
  {
    return nonstd::make_unexpected("Dimension value must contain positive integers only.");
  }

  return boost::gil::point_t(w, h);
}

std::string sized_name(const std::string& file, const boost::gil::point_t& dims)
{
  namespace fs = std::filesystem;

  fs::path path(file);
  const auto ext = path.extension();
  const auto stem = path.stem();

  const auto size_string = "_" + std::to_string(dims.x) + "x" + std::to_string(dims.y);
  fs::path sized(stem.native() + size_string + ext.native());
  path.replace_filename(sized);
  std::error_code error;
  uint_least32_t counter = 0;
  while (fs::exists(path, error) && !error)
  {
    ++counter;
    sized = stem.native() + size_string + "_" + std::to_string(counter) + ext.native();
    path.replace_filename(sized);
  }
  return path;
}
