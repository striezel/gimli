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

#ifndef GIMLI_LOAD_ANY_HPP
#define GIMLI_LOAD_ANY_HPP

#include "../Image.hpp"
#include "../types/get_type.hpp"

namespace gimli
{

/** \brief Loads an image (of any supported format) from the given path.
 *
 * \param path    the file path of the image to load
 * \return Returns an Image, if the image could be loaded.
 *         Returns an error message otherwise.
 * \remarks Use this overload of load_any(), if you do not know the image type
 *          of the file. Otherwise use the overload with type parameter.
 */
nonstd::expected<Image, std::string> load_any(const std::string& path);

/** \brief Loads an image of the specified type from the given path.
 *
 * \param path    the file path of the image to load
 * \param type    the type of the image
 * \return Returns an Image, if the image could be loaded.
 *         Returns an error message otherwise.
 * \remarks Use this overload of load_any(), if you know the image type.
 *          Otherwise use the overload without type parameter.
 */
nonstd::expected<Image, std::string> load_any(const std::string& path, const types::ImageType type);

}

#endif // GIMLI_LOAD_ANY_HPP
