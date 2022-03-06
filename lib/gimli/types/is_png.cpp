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

#include "is_png.hpp"
#include <png.h>

namespace gimli::types
{

bool is_png(const std::vector<uint8_t>& data)
{
  if (data.size() < 8)
  {
    // Less than eight bytes is not a valid PNG file.
    return false;
  }

  // Let libpng decide whether this is a PNG file.
  return png_sig_cmp(data.data(), 0, 8) == 0;
}

} // namespace
