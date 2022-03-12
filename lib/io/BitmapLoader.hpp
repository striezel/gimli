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

#ifndef GIMLI_BITMAP_LOADER_HPP
#define GIMLI_BITMAP_LOADER_HPP

#include <boost/gil/extension/io/bmp.hpp>
#include "Loader.hpp"

namespace gimli
{

/** \brief Loads Bitmap images.
 */
using BitmapLoader = Loader<boost::gil::bmp_tag>;

} // namespace

#endif // GIMLI_BITMAP_LOADER_HPP
