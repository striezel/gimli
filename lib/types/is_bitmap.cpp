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

#include "is_bitmap.hpp"

namespace gimli::types
{

bool is_bitmap(const nonstd::span<uint8_t>& data)
{
  // The first two bytes of a Bitmap file are the ASCII characters 'B' and 'M'.
  return (data.size() >= 2)
  && (data[0] == 0x42) /* 'B' */ && (data[1] == 0x4D) /* 'M' */;
}

} // namespace
