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

#ifndef GIMLI_IMAGE_HPP
#define GIMLI_IMAGE_HPP

#include <boost/gil/extension/dynamic_image/any_image.hpp>

namespace gimli
{

/* Older approach:

typedef boost::mpl::vector<boost::gil::rgb8_image_t, boost::gil::rgba8_image_t, boost::gil::gray8_image_t> image_types;
using Image = boost::gil::any_image<image_types>;
*/

using Image = boost::gil::rgb8_image_t;

/* Note: Image might change to boost::gil::rgba8_image_t later. */

} // namespace

#endif // GIMLI_IMAGE_HPP
