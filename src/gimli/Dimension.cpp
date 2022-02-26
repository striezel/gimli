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

#include "Dimension.hpp"

namespace gimli
{

Dimension::Dimension()
: w(0),
  h(0)
{
}

std::uint32_t Dimension::width() const
{
  return w;
}

void Dimension::setWidth(const std::uint32_t new_width)
{
  w = new_width;
}

std::uint32_t Dimension::height() const
{
  return h;
}

void Dimension::setHeight(const std::uint32_t new_height)
{
  h = new_height;
}

bool Dimension::operator==(const Dimension& other) const
{
  return (w == other.w) && (h == other.h);
}

} // namespace
