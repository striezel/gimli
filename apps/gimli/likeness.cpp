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

#include "likeness.hpp"
#include <cmath>
#include <iostream>
#include <iterator>
#include "../return_codes.hpp"
#include "../../lib/hash/factory.hpp"
#include "../../lib/hash/similarity.hpp"
#include "../../lib/io/load_any.hpp"
#include "../../lib/transforms/Greyscale.hpp"
#include "../../lib/types/get_type.hpp"

std::string to_percentage(const float similarity)
{
  return std::to_string(std::round(similarity * 10000.0) / 100.0) + " %";
}

int calculate_hash(const std::filesystem::path& file, std::unordered_map<std::string, uint64_t>& hashes, const gimli::hash::algorithm algo)
{
  const auto img = load_to_grey(file);
  if (!img.has_value())
  {
    return img.error();
  }
  const auto hash = gimli::hash::factory::calculate(algo, img.value());
  if (!hash.has_value())
  {
    std::cerr << "Error: Hash calculation for " << file.string() << " failed!\n"
              << hash.error() << "\n";
    return rcInputOutputError;
  }
  hashes[file.string()] = hash.value();
  return 0;
}

nonstd::expected<boost::gil::gray8_image_t, int> load_to_grey(const std::filesystem::path& file)
{
  const auto img_type = gimli::types::get_type(file);
  if (!img_type.has_value())
  {
    std::cout << "Warning: Could not determine image type of " << file.string()
              << "!\nError message: " << img_type.error() << "\n"
              << "File will be skipped." << std::endl;
    return nonstd::make_unexpected(0);
  }
  if (img_type.value() == gimli::types::ImageType::Unknown)
  {
    std::cerr << "'I have no memory of this place.' - Gandalf\n"
              << "Error: File " << file.string() << " has an unknown or unsupported image format.\n";
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
    std::cerr << "Error: File " << file.string() << " could not be transformed to greyscale image.\n"
              << "Error: " << maybe_grey.error() << "\n";
    return nonstd::make_unexpected(rcInputOutputError);
  }

  return maybe_grey.value();
}

std::vector<likeness_entry> sort_by_similarity(const std::unordered_map<std::string, uint64_t>& hashes)
{
  const auto length = hashes.size();
  if (length <= 1)
  {
    return { };
  }
  std::vector<likeness_entry> result;
  result.reserve(length * (length - 1) / 2);

  const auto end = hashes.cend();
  for (auto i = hashes.cbegin(); i != end; ++i)
  {
    for (auto j = std::next(i); j != end; ++j)
    {
      result.emplace_back(std::make_tuple(i->first, j->first,
                          gimli::hash::similarity(i->second, j->second)));
    }
  }

  std::sort(result.begin(), result.end(), [](const likeness_entry& a, const likeness_entry& b)
  {
    return std::get<2>(a) > std::get<2>(b);
  });
  return result;
}
