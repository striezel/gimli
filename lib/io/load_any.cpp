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

#include "load_any.hpp"
#include "BitmapLoader.hpp"
#include "JpegLoader.hpp"
#include "PngLoader.hpp"
#include "TargaLoader.hpp"
#include "../types/get_type.hpp"

namespace gimli
{

nonstd::expected<Image, std::string> load_any(const std::string& path)
{
  const auto maybe_type = gimli::types::get_type(path);
  if (!maybe_type.has_value())
  {
    return nonstd::make_unexpected(maybe_type.error());
  }
  return load_any(path, maybe_type.value());
}

nonstd::expected<Image, std::string> load_any(const std::string& path, const types::ImageType type)
{
  using namespace gimli::types;

  switch(type)
  {
    case ImageType::Jpeg:
         return JpegLoader::load(path);
    case ImageType::Png:
         return PngLoader::load(path);
    case ImageType::Targa:
         return TargaLoader::load(path);
    case ImageType::Bitmap:
         return BitmapLoader::load(path);
    case ImageType::Unknown:
    default:
         return nonstd::make_unexpected("Cannot load image of unknown type.");
  }
}

}
