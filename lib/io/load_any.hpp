/*
 -------------------------------------------------------------------------------
    This file is part of the Generic Image Library (gimli).
    Copyright (C) 2022, 2024, 2026  Dirk Stolle

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

#ifndef GIMLI_LOAD_ANY_HPP
#define GIMLI_LOAD_ANY_HPP

#include "../Image.hpp"
#include "../types/get_type.hpp"
#include "BitmapLoader.hpp"
#include "JpegLoader.hpp"
#include "PngLoader.hpp"
#include "TargaLoader.hpp"
#include "WebpLoader.hpp"

namespace gimli
{

/** \brief Loads an image of the specified type from the given path.
 *
 * \param path    the file path of the image to load
 * \param type    the type of the image
 * \return Returns an Image, if the image could be loaded.
 *         Returns an error message otherwise.
 * \remarks Use this overload of load_any(), if you know the image type.
 *          Otherwise use the overload without type parameter.
 */
template<typename img_t = Image>
nonstd::expected<img_t, std::string> load_any(const std::filesystem::path& path, const types::ImageType type)
{
  using namespace gimli::types;

  switch(type)
  {
    case ImageType::Jpeg:
         return JpegLoader<img_t>::load(path);
    case ImageType::Png:
         return PngLoader<img_t>::load(path);
    case ImageType::WebP:
         return WebpLoader<img_t>::load(path);
    case ImageType::Targa:
         return TargaLoader<img_t>::load(path);
    case ImageType::Bitmap:
         return BitmapLoader<img_t>::load(path);
    case ImageType::Unknown:
    default:
         return nonstd::make_unexpected("Cannot load image of unknown type.");
  }
}

/** \brief Loads an image (of any supported format) from the given path.
 *
 * \param path    the file path of the image to load
 * \return Returns an Image, if the image could be loaded.
 *         Returns an error message otherwise.
 * \remarks Use this overload of load_any(), if you do not know the image type
 *          of the file. Otherwise use the overload with type parameter.
 */
template<typename img_t = Image>
nonstd::expected<img_t, std::string> load_any(const std::filesystem::path& path)
{
  const auto maybe_type = gimli::types::get_type(path);
  if (!maybe_type.has_value())
  {
    return nonstd::make_unexpected(maybe_type.error());
  }
  return load_any<img_t>(path, maybe_type.value());
}

}

#endif // GIMLI_LOAD_ANY_HPP
