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

#include "is_targa.hpp"

namespace gimli::types
{

bool is_targa(const nonstd::span<uint8_t>& data)
{
  return (data.size() >= 17)
  // Byte zero can have any vaue.
  // Byte one indicates palette type: 0 = no palette, 1 = has palette.
  && ((data[1] == 0x00) || (data[1] == 0x01))
  /* Byte two is image type:
     0  = no data
     1  = indexed (palette)
     2  = RGB (24 or 32 bit)
     3  = monochrome
     9  = indexed (palette) with RLE
     10 = RGB (24 Bit) with RLE
     11 = monochrome with RLE */
  && ((data[2] == 0x00) || (data[2] == 0x01) || (data[2] == 0x02)
      || (data[2] == 0x03) || (data[2] == 0x09) || (data[2] == 0x0A)
      || (data[2] == 0x0B))
  // Bytes 3+4: start of palette, bytes 5+6: length of palette.
  // Byte 7: size of a palette entry in bits
  // Bytes 8+9: x coordinate, bytes 10+11: y coordinate of origin
  // Bytes 12+13: width, bytes 14+15: height
  /* Byte 16: Bits per pixel, allowed values are 1, 8, 15, 16, 24 and 32. */
  && ((data[16] == 0x01) || (data[16] == 0x08) || (data[16] == 0x0F)
      || (data[16] == 0x10) || (data[16] == 0x18) || (data[16] == 0x20));
}

} // namespace
