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

#include "likeness.hpp"
#include <cmath>
#include <iostream>
#include "../return_codes.hpp"
#include "../../lib/hash/average.hpp"
#include "../../lib/hash/difference.hpp"
#include "../../lib/hash/similarity.hpp"
#include "../../lib/hash/vertical_difference.hpp"
#include "../../lib/io/load_any.hpp"
#include "../../lib/transforms/Greyscale.hpp"
#include "../../lib/types/get_type.hpp"

std::string to_percentage(const float similarity)
{
  return std::to_string(std::round(similarity * 10000.0) / 100.0) + " %";
}

int likeness(const std::string& file, const Hashes& ref_hash)
{
  const auto img = load_to_grey(file);
  if (!img.has_value())
  {
    return img.error();
  }

  const auto hashes = calculate_hashes(img.value());
  if (!hashes.has_value())
  {
    std::cerr << "Error: Hash calculation for " << file << " failed!\n"
              << hashes.error() << "\n";
    return rcInputOutputError;
  }

  const auto& h = hashes.value();
  std::cout << file << "\n"
            << "    likeness (aHash): "
            << to_percentage(gimli::hash::similarity(ref_hash.avg_hash, h.avg_hash))
            << "\n    likeness (dHash): "
            << to_percentage(gimli::hash::similarity(ref_hash.diff_hash, h.diff_hash))
            << "\n    likeness (vHash): "
            << to_percentage(gimli::hash::similarity(ref_hash.vertical_diff_hash, h.vertical_diff_hash))
            << "\n";
  return 0;
}

nonstd::expected<boost::gil::gray8_image_t, int> load_to_grey(const std::string& file)
{
  const auto img_type = gimli::types::get_type(file);
  if (!img_type.has_value())
  {
    std::cout << "Warning: Could not determine image type of " << file
              << "!\nError message: " << img_type.error() << "\n"
              << "File will be skipped." << std::endl;
    return nonstd::make_unexpected(0);
  }
  if (img_type.value() == gimli::types::ImageType::Unknown)
  {
    std::cerr << "'I have no memory of this place.' - Gandalf\n"
              << "Error: File " << file << " has an unknown or unsupported image format." << std::endl;
    return nonstd::make_unexpected(rcUnsupportedFormat);
  }

  const auto maybe_image = gimli::load_any(file, img_type.value());
  if (!maybe_image.has_value())
  {
    std::cerr << "Error: File " << file << " could not be loaded.\n"
              << "Error: " << maybe_image.error() << "\n";
    return nonstd::make_unexpected(rcInputOutputError);
  }

  const auto maybe_grey = gimli::Greyscale::transform(maybe_image.value());
  if (!maybe_grey.has_value())
  {
    std::cerr << "Error: File " << file << " could not be transformed to greyscale image.\n"
              << "Error: " << maybe_grey.error() << "\n";
    return nonstd::make_unexpected(rcInputOutputError);
  }

  return maybe_grey.value();
}

nonstd::expected<Hashes, std::string> calculate_hashes(const boost::gil::gray8_image_t& img)
{
  const auto avg = gimli::hash::average(img);
  if (!avg.has_value())
  {
    return nonstd::make_unexpected(avg.error());
  }
  const auto diff = gimli::hash::difference(img);
  if (!diff.has_value())
  {
    return nonstd::make_unexpected(diff.error());
  }
  const auto v_diff = gimli::hash::vertical_difference(img);
  if (!v_diff.has_value())
  {
    return nonstd::make_unexpected(diff.error());
  }
  return Hashes{ avg.value(), diff.value(), v_diff.value() };
}
