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

#include "Image.hpp"
#include <stdexcept>

namespace gimli
{

Image Image::load(const std::string_view& path, const Format format)
{
  throw std::runtime_error("load() is not implemented yet.");
}

Image::Image()
: dim(Dimension()),
  fmt(Format::Jpeg),
  data(nullptr)
{
}

const Dimension& Image::dimension() const
{
  return dim;
}

Format Image::format() const
{
  return fmt;
}

} // namespace
