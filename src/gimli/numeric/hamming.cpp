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

#include "hamming.hpp"

namespace gimli::numeric
{

unsigned int hamming_distance(const uint64_t a, const uint64_t b)
{
  unsigned int distance = 0;
  for (unsigned int i = 0; i < 64; ++i)
  {
    distance += ((1ull << i) & a) != ((1ull << i) & b);
  }
  return distance;
}

} // namespace
