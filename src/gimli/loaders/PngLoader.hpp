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

#ifndef GIMLI_PNG_LOADER_HPP
#define GIMLI_PNG_LOADER_HPP

#include <string>
#include "Loader.hpp"

namespace gimli
{

/** \brief Loads PNG images.
 */
class PngLoader: Loader
{
  public:
    /** \brief Indicates whether the loader supports a certain image format.
     *
     * \param fmt   the format to check
     * \return Returns true, if the loader supports loading the specified image
     *         format. Returns false, if the format is not supported.
     */
    bool supportsFormat(const Format fmt) const final;

    /** \brief Loads an image from the given path.
     *
     * \param path    the file path of the image to load
     * \param format  the format of the image
     * \return Returns an Image, if the image could be loaded.
     *         Returns an error message otherwise.
     */
    nonstd::expected<Image, std::string> load(const std::string_view& path, const Format format) final;
};

} // namespace

#endif // GIMLI_PNG_LOADER_HPP
