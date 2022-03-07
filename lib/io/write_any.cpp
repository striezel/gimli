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

#include "write_any.hpp"
#include "JpegWriter.hpp"
#include "PngWriter.hpp"
#include "TargaWriter.hpp"

namespace gimli
{

std::optional<std::string> write_any(const std::string& path, const Image& image, const types::ImageType type)
{
  using namespace gimli::types;

  switch(type)
  {
    case ImageType::Jpeg:
         return JpegWriter::write(path, image);
    case ImageType::Png:
         return PngWriter::write(path, image);
    case ImageType::Targa:
         return TargaWriter::write(path, image);
    case ImageType::Unknown:
    default:
         return "Cannot write image of unknown type.";
  }
}

}
