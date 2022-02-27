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

#ifndef GIMLI_IMAGE_HPP
#define GIMLI_IMAGE_HPP

#include <memory>
#include <string_view>
#include "Dimension.hpp"
#include "Format.hpp"

namespace gimli
{

class Image
{
  public:
    static Image load(const std::string_view& path, const Format format);
    Image(const Dimension& d = Dimension(), const PixelLayout l = PixelLayout::RGB, std::uint8_t _data[] = nullptr);
    Image(const Image& other);

    const Dimension& dimension() const;
    PixelLayout layout() const;
    const std::uint8_t* data() const;
  private:
    Dimension dim;
    PixelLayout pxLayout;
    std::unique_ptr<std::uint8_t[]> pxData;
};

} // namespace

#endif // GIMLI_IMAGE_HPP
