/*
 -------------------------------------------------------------------------------
    This file is part of the Generic Image Library (gimli).
    Copyright (C) 2025  Dirk Stolle

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

#include "legolas.hpp"
#include <iostream>
#include <iterator>
#include "../return_codes.hpp"
#include "../../lib/io/load_any.hpp"

int legolas(const std::vector<std::filesystem::path>& files)
{
  // Main function already checked that at least two elements are in the vector,
  // so accessing element at index zero is not out of range.
  const auto& ref_path = files[0];
  const auto maybe_reference_image = gimli::load_any(ref_path);
  if (!maybe_reference_image.has_value())
  {
    std::cerr << "Error: File " << ref_path.string() << " could not be loaded.\n"
              << "Error: " << maybe_reference_image.error() << "\n";
    return rcInputOutputError;
  }

  const auto reference_image = maybe_reference_image.value();
  const auto ref_view = const_view(reference_image);
  for (auto iter = std::next(files.begin()); iter != files.end(); ++iter)
  {
    const auto maybe_image = gimli::load_any(*iter);
    if (!maybe_image.has_value())
    {
      std::cerr << "Error: File " << iter->string() << " could not be loaded.\n"
                << "Error: " << maybe_image.error() << "\n";
      return rcInputOutputError;
    }
    const auto image = maybe_image.value();

    if ((reference_image.width() != image.width()) || (reference_image.height() != image.height()))
    {
      std::cout << "Image " << iter->string() << " has different dimensions than the reference image " << ref_path.string() << ".\n";
      continue;
    }

    const auto img_view = const_view(image);
    auto ref_it = ref_view.begin();
    const auto img_end = img_view.end();
    bool identical = true;
    for (auto img_it = img_view.begin(); img_it != img_end; ++img_it, ++ref_it)
    {
      const auto img_pixel = *img_it;
      const auto ref_pixel = *ref_it;
      if ((get_color(img_pixel, boost::gil::red_t()) != get_color(ref_pixel, boost::gil::red_t()))
        || (get_color(img_pixel, boost::gil::green_t()) != get_color(ref_pixel, boost::gil::green_t()))
        || (get_color(img_pixel, boost::gil::blue_t()) != get_color(ref_pixel, boost::gil::blue_t())))
      {
        std::cout << "Image " << iter->string() << " is different from the reference image " << ref_path.string() << ".\n";
        identical = false;
        break;
      }
    }

    if (identical)
    {
      std::cout << "Image " << iter->string() << " is identical to the reference image " << ref_path.string() << ".\n";
    }
  }

  return 0;
}
