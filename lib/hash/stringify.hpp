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

#ifndef GIMLI_HASH_STRINGIFY_HPP
#define GIMLI_HASH_STRINGIFY_HPP

#include <cstdint>
#include <limits>
#include <sstream>
#include <string>

namespace gimli::hash
{

/** \brief Gets the hexadecimal representation of a string.
 *
 * \param hash_value   value of the hash
 * \return Returns the hexadecimal representation of the string.
 */
template<typename uint_t>
std::string stringify(const uint_t hash_value)
{
  static_assert(std::numeric_limits<uint_t>::is_integer && !std::numeric_limits<uint_t>::is_signed);
  constexpr unsigned int hex_digits = std::numeric_limits<uint_t>::digits / 4;

  std::ostringstream stream;
  stream.fill('0');
  stream.width(hex_digits);
  stream << std::hex << hash_value;
  return stream.str();
}

} // namespace

#endif // GIMLI_HASH_STRINGIFY_HPP
