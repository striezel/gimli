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

#include "get_type.hpp"
#include <fstream>
#include "is_jpeg.hpp"
#include "is_png.hpp"
#include "is_targa.hpp"

namespace gimli::types
{

std::ostream& operator<<(std::ostream& os, const ImageType it)
{
  switch(it)
  {
    case ImageType::Jpeg:
         os << "JPEG";
         break;
    case ImageType::Png:
         os << "PNG";
         break;
    case ImageType::Targa:
         os << "Targa image";
         break;
    default:
         os << "unknown";
         break;
  }
  return os;
}

nonstd::expected<ImageType, std::string> get_type(const std::filesystem::path& path)
{
  try
  {
    constexpr std::streamsize bytes_to_read = 17;
    std::vector<uint8_t> buffer(bytes_to_read, 0);
    {
      std::ifstream input(path, std::ios_base::binary | std::ios_base::in);
      input.read(reinterpret_cast<char*>(buffer.data()), bytes_to_read);
      if (!input.good() || input.gcount() < bytes_to_read)
      {
        return nonstd::make_unexpected("File is too short to determine the image type.");
      }
      input.close();
    }
    return get_type(buffer);
  }
  catch (const std::exception& ex)
  {
    return nonstd::make_unexpected(ex.what());
  }
}

ImageType get_type(const std::vector<uint8_t>& data)
{
  if (is_jpeg(data))
    return ImageType::Jpeg;
  if (is_png(data))
    return ImageType::Png;
  if (is_targa(data))
    return ImageType::Targa;

  return ImageType::Unknown;
}

} // namespace
