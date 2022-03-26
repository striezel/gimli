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

#include "is_webp.hpp"

namespace gimli::types
{

bool is_webp(const nonstd::span<uint8_t>& data)
{
  if (data.size() < 12)
  {
    // Less than twelve bytes is not a valid WebP file.
    return false;
  }

  // First four bytes are "RIFF" ...
  return (data[0] == 0x52) && (data[1] == 0x49) && (data[2] == 0x46) && (data[3] == 0x46)
    // ... and bytes 8-11 are "WEBP"
    && (data[8] == 0x57) && (data[9] == 0x45) && (data[10] == 0x42) && (data[11] == 0x50);
}

} // namespace
