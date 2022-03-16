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

#ifndef GIMLI_HASH_SIMILARITY_HPP
#define GIMLI_HASH_SIMILARITY_HPP

#include "../numeric/hamming.hpp"

namespace gimli::hash
{

/** \brief Calculates the similarity of two hashes.
 *
 * \param h1   first hash value
 * \param h2   second hash value
 * \return Returns the similarity of two hashes as a floating point value in
 *         the range [0;1]. Zero means no similarity at all, one means 100 %
 *         similarity.
 * \remark Obviously, the result is only meaningful, if both hashes have been
 *         calculated using the same hash algorithm.
 */
template<typename uint_t>
float similarity(const uint_t h1, const uint_t h2)
{
  static_assert(std::numeric_limits<uint_t>::is_integer && !std::numeric_limits<uint_t>::is_signed);
  constexpr unsigned int digits = std::numeric_limits<uint_t>::digits;

  return static_cast<float>(digits - numeric::hamming_distance(h1, h2)) / static_cast<float>(digits);
}

} // namespace

#endif // GIMLI_HASH_SIMILARITY_HPP
