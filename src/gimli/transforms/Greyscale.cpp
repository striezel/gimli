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
#include <boost/gil/gray.hpp>

namespace gimli
{

nonstd::expected<boost::gil::gray8_image_t, std::string> Greyscale::transform(const Image& source)
{
  using namespace boost::gil;

  gray8_image_t img(source.dimensions());
  // Boost GIL's conversion seems to be based on Rec. 601 luma, i. e.:
  //   grey value = 0.299 * red + 0.587 * green + 0.114 * blue
  copy_pixels(
    color_converted_view<gray8_pixel_t>(const_view(source)),
    view(img));

  return img;
}

} // namespace
