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

#ifndef GIMLI_HASH_DIFFERENCE_HPP
#define GIMLI_HASH_DIFFERENCE_HPP

#include <cstdint>
#include <string>
#include "../../third-party/nonstd/expected.hpp"
#include "../Image.hpp"

namespace gimli::hash
{

/** \brief Calculates the difference hash ("dHash") of an image.
 *
 * \param img  the input image
 * \return Returns the hash of the image in case of success.
 *         Returns an error message otherwise.
 */
nonstd::expected<uint64_t, std::string> difference(const Image& img);

} // namespace

#endif // GIMLI_HASH_DIFFERENCE_HPP
