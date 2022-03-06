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

#ifndef GIMLI_NUMERIC_HAMMING_HPP
#define GIMLI_NUMERIC_HAMMING_HPP

#include <cstdint>
#include <limits>

namespace gimli::numeric
{

/** \brief Calculates the Hamming distance of two integers.
 *
 * \param a   first integer
 * \param b   second integer
 * \return Returns the Hamming distance of a and b.
 *
 */
template<typename uint_t>
unsigned int hamming_distance(const uint_t a, const uint_t b)
{
  static_assert(std::numeric_limits<uint_t>::is_integer && !std::numeric_limits<uint_t>::is_signed);
  constexpr unsigned int digits = std::numeric_limits<uint_t>::digits;
  unsigned int distance = 0;
  for (unsigned int i = 0; i < digits; ++i)
  {
    const uint_t shifted = static_cast<uint_t>(1u) << i;
    distance += (shifted & a) != (shifted & b);
  }
  return distance;
}

} // namespace

#endif // GIMLI_NUMERIC_HAMMING_HPP
