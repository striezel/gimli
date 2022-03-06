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

#ifndef GIMLI_TRANSFORM_GREYSCALE_HPP
#define GIMLI_TRANSFORM_GREYSCALE_HPP

#include "../../../third-party/nonstd/expected.hpp"
#include "../Image.hpp"

namespace gimli
{

struct Greyscale
{
  public:
    /** \brief Transforms a non-greyscale image to greyscale.
     *
     * \param source   the source image
     * \return Returns the transformation result, if successful.
     *         Returns an error message otherwise.
     */
    static nonstd::expected<boost::gil::gray8_image_t, std::string> transform(const Image& source);
};

} // namespace

#endif // GIMLI_TRANSFORM_GREYSCALE_HPP
