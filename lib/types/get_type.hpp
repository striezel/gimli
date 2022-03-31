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

#ifndef GIMLI_TYPES_GET_TYPE_HPP
#define GIMLI_TYPES_GET_TYPE_HPP

#include <cstdint>
#include <filesystem>
#include <string>
#include "../../third-party/nonstd/expected.hpp"
#include "../../third-party/nonstd/span.hpp"

namespace gimli::types
{

enum class ImageType
{
  Unknown,
  Bitmap,
  Jpeg,
  Png,
  Targa,
  WebP
};

std::ostream& operator<<(std::ostream& os, const ImageType it);

/** \brief Tries to determine the image type of a file.
 *
 * \param path  path to the potential image file.
 * \return Returns the image type, if it could be detected.
 *         Returns ImageType::Unknown, if the file did not contain any
 *         detectable image data.
 *         Returns an error message, if an error occurred.
 */
nonstd::expected<ImageType, std::string> get_type(const std::filesystem::path& path);

/** \brief Tries to determine the image type of a file.
 *
 * \param data   the first few bytes (>= 17 bytes) read from the file
 * \return Returns the image type, if it could be detected.
 *         Returns ImageType::Unknown, if the file did not contain any
 *         detectable image data.
 */
ImageType get_type(const nonstd::span<uint8_t>& data);

} // namespace

#endif // GIMLI_TYPES_GET_TYPE_HPP
