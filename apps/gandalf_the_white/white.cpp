/*
 -------------------------------------------------------------------------------
    This file is part of the Generic Image Library (gimli).
    Copyright (C) 2023  Dirk Stolle

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

#include "white.hpp"
#include <filesystem>
#include <iostream>
#include "../return_codes.hpp"
#include "../../lib/io/load_any.hpp"
#include "../../lib/io/write_any.hpp"
#include "../../lib/transforms/Greyscale.hpp"
#include "../../lib/types/get_type.hpp"

int gandalf_the_white(const std::string& file)
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
    std::cerr << "'I have no memory of this place.' - Gandalf\n"
              << "Error: File " << file << " has an unknown or unsupported image format." << std::endl;
    return rcUnsupportedFormat;
  }

  const auto maybe_image = gimli::load_any(file, img_type.value());
  if (!maybe_image.has_value())
  {
    std::cerr << "Error: File " << file << " could not be loaded.\n"
              << "Error: " << maybe_image.error() << "\n";
    return rcInputOutputError;
  }

  const auto maybe_white = white_balance(maybe_image.value());
  if (!maybe_white.has_value())
  {
    std::cerr << "Error: File " << file << " could not be transformed to greyscale image.\n"
              << "Error: " << maybe_white.error() << "\n";
    return rcInputOutputError;
  }

  const std::string white_file = white_name(file);
  const auto error_text = gimli::write_any_rgb(white_file, maybe_white.value(), img_type.value());
  if (error_text.has_value())
  {
    std::cerr << "Error: White-balanced version of " << file << " could not be written to file "
              << white_file << ".\n"
              << "Error: " << error_text.value() << "\n";
    return rcInputOutputError;
  }
  std::cout << file << " -> " << white_file << "\n";

  return 0;
}

boost::gil::rgb8_pixel_t get_maximum_channels(const boost::gil::rgb8_image_t& source)
{
  using namespace boost::gil;

  const auto source_view = const_view(source);
  auto it = source_view.begin();
  const auto end = source_view.end();
  uint8_t r_max = 0;
  uint8_t g_max = 0;
  uint8_t b_max = 0;
  while (it != end)
  {
    const auto r = get_color(*it, red_t());
    if (r > r_max)
    {
      r_max = r;
    }
    const auto g = get_color(*it, green_t());
    if (g > g_max)
    {
      g_max = g;
    }
    const auto b = get_color(*it, blue_t());
    if (b > b_max)
    {
      b_max = b;
    }
    ++it;
  }
  if (r_max == 0)
    r_max = 255;
  if (g_max == 0)
    g_max = 255;
  if (b_max == 0)
    b_max = 255;

  return rgb8_pixel_t{r_max, g_max, b_max};
}

nonstd::expected<boost::gil::rgb8_image_t, std::string> white_balance(const boost::gil::rgb8_image_t& source)
{
  using namespace boost::gil;

  const auto max_channels = get_maximum_channels(source);
  const uint8_t r_max = get_color(max_channels, red_t());
  const uint8_t g_max = get_color(max_channels, green_t());
  const uint8_t b_max = get_color(max_channels, blue_t());

  try
  {
    rgb8_image_t img(source.dimensions());

    const auto source_view = const_view(source);
    auto it = source_view.begin();
    const auto end = source_view.end();
    auto img_view = view(img);
    auto dest_it = img_view.begin();
    while (it != end)
    {
      const uint8_t new_r = static_cast<uint16_t>(get_color(*it, red_t())) * 255 / r_max;
      const uint8_t new_g = static_cast<uint16_t>(get_color(*it, green_t())) * 255 / g_max;
      const uint8_t new_b = static_cast<uint16_t>(get_color(*it, blue_t())) * 255 / b_max;
      *dest_it = rgb8_pixel_t{ new_r, new_g, new_b };
      ++it;
      ++dest_it;
    }

    return img;
  }
  catch (const std::exception& ex)
  {
    return nonstd::make_unexpected(ex.what());
  }
}

std::string white_name(const std::string& file)
{
  namespace fs = std::filesystem;

  fs::path path(file);
  const auto ext = path.extension().string();
  const auto stem = path.stem().string();

  fs::path white(stem + std::string("_white") + ext);
  path.replace_filename(white);
  std::error_code error;
  uint_least32_t counter = 0;
  while (fs::exists(path, error) && !error)
  {
    ++counter;
    white = stem + std::string("_white_") + std::to_string(counter) + ext;
    path.replace_filename(white);
  }
  return path.string();
}
