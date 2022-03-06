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

#ifndef GIMLI_IS_TARGA_HPP
#define GIMLI_IS_TARGA_HPP

#include <cstdint>
#include <vector>

namespace gimli::types
{

/** \brief Checks whether a file is a Targa image file.
 *
 * \param data   the first few bytes read from the file
 * \return Returns true, if the data indicates that it was read from a Targa
 *         image file. Returns false otherwise.
 */
bool is_targa(const std::vector<uint8_t>& data);

} // namespace

#endif // GIMLI_IS_TARGA_HPP
