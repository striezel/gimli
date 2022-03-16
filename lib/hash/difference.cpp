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

#include "difference.hpp"
#include "../transforms/Greyscale.hpp"
#include "../transforms/Resize.hpp"

namespace gimli::hash
{

nonstd::expected<uint64_t, std::string> difference(const Image& img)
{
  using namespace boost::gil;

  const auto maybe_grey = Greyscale::transform(img);
  if (!maybe_grey.has_value())
  {
    return nonstd::make_unexpected(maybe_grey.error());
  }
  return difference(maybe_grey.value());
}

nonstd::expected<uint64_t, std::string> difference(const boost::gil::gray8_image_t& img)
{
  using namespace boost::gil;

  const auto maybe_small = Resize::transform(img, point_t(9, 8));
  if (!maybe_small.has_value())
  {
    return nonstd::make_unexpected(maybe_small.error());
  }

  uint64_t result = 0;
  unsigned int shift = 0;
  const auto small_view = const_view(maybe_small.value());
  for (unsigned int y = 0; y < 8; ++y)
  {
    for (unsigned int x = 0; x < 8; ++x)
    {
      result += static_cast<uint64_t>(small_view(x, y) > small_view(x+1, y)) << shift;
      ++shift;
    }
  }
  return result;
}

} // namespace
