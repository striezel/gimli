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

#include "Greyscale.hpp"

namespace gimli
{

nonstd::expected<Image, std::string> Greyscale::transform(const Image& source)
{
  // There is nothing to do, if it already uses greyscale instead of RGB(A).
  if (source.layout() == PixelLayout::Grey)
  {
    return source;
  }

  const auto source_data = source.data();
  const auto& dimension = source.dimension();
  const std::size_t total_pixels = dimension.width() * dimension.height();
  std::unique_ptr<std::uint8_t[]> dest_data = std::make_unique<std::uint8_t[]>(total_pixels);
  unsigned int bytes_per_pixel = 3;
  switch (source.layout())
  {
    case PixelLayout::RGB:
         bytes_per_pixel = 3;
         break;
    case PixelLayout::RGBA:
         bytes_per_pixel = 4;
         break;
    case PixelLayout::Grey:
         bytes_per_pixel = 1;
         break;
    default:
         return nonstd::make_unexpected("Unknown pixel layout.");
  }

  std::size_t offset = 0;
  const auto w = dimension.width();
  const auto h = dimension.height();

  for (std::size_t x = 0; x < w; ++x)
  {
    for (std::size_t y = 0; y < h; ++y)
    {
      // Weighted average, sRGB / Rec. 709.
      dest_data.get()[y * w + x] = 0.2126 * source_data[offset]
                                 + 0.7152 * source_data[offset + 1]
                                 + 0.0722 * source_data[offset + 2];
      offset += bytes_per_pixel;
    }
  }
  const auto data = dest_data.get();
  dest_data.release();
  return Image(dimension, PixelLayout::Grey, data);
}

} // namespace
