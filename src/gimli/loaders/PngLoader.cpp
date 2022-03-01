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

#include "PngLoader.hpp"
#include <boost/gil/extension/io/png.hpp>

namespace gimli
{

nonstd::expected<Image, std::string> PngLoader::load(const std::string& path)
{
  using namespace boost::gil;

  Image image;
  try
  {
    read_image(path, image, png_tag());
  }
  catch (const std::exception& ex)
  {
    return nonstd::make_unexpected(ex.what());
  }

  return image;
}

} // namespace
