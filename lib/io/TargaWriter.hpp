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

#ifndef GIMLI_TARGA_WRITER_HPP
#define GIMLI_TARGA_WRITER_HPP

#include <boost/gil/extension/io/targa.hpp>
#include "Writer.hpp"

namespace gimli
{

/** \brief Writes Targa (*.tga) images.
 */
using TargaWriter = Writer<boost::gil::targa_tag>;
using TargaWriterGrey = Writer<boost::gil::targa_tag, boost::gil::gray8_image_t>;

} // namespace

#endif // GIMLI_TARGA_WRITER_HPP
