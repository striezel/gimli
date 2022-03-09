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

#ifndef GIMLI_WRITE_ANY_HPP
#define GIMLI_WRITE_ANY_HPP

#include <optional>
#include <string>
#include "../Image.hpp"
#include "../types/get_type.hpp"

namespace gimli
{

/** \brief Writes an RGB image of the specified type to the given path.
 *
 * \param path    the file path of the image to load
 * \param image   the image data that shall be written
 * \param type    the type of the image
 * \return Returns an empty optional, if the image was written successfully.
 *         Returns an error message otherwise.
 */
std::optional<std::string> write_any_rgb(const std::string& path, const Image& image, const types::ImageType type);

/** \brief Writes a greyscale image of the specified type to the given path.
 *
 * \param path    the file path of the image to load
 * \param image   the image data that shall be written
 * \param type    the type of the image
 * \return Returns an empty optional, if the image was written successfully.
 *         Returns an error message otherwise.
 */
std::optional<std::string> write_any_grey(const std::string& path, const boost::gil::gray8_image_t& image, const types::ImageType type);

}

#endif // GIMLI_WRITE_ANY_HPP
