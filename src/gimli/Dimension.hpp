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

#ifndef GIMLI_DIMENSION_HPP
#define GIMLI_DIMENSION_HPP

#include <cstdint>

namespace gimli
{

class Dimension
{
  public:
    Dimension();
    bool operator==(const Dimension& other) const;

    std::uint32_t width() const;
    void setWidth(const std::uint32_t new_width);

    std::uint32_t height() const;
    void setHeight(const std::uint32_t new_height);
  private:
    std::uint32_t w; /**< width in pixels */
    std::uint32_t h; /**< height in pixels */
};

}

#endif // GIMLI_DIMENSION_HPP
