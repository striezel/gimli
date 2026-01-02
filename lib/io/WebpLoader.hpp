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

#ifndef GIMLI_WEBP_LOADER_HPP
#define GIMLI_WEBP_LOADER_HPP

#include <filesystem>
#include <string>
#include "../../third-party/nonstd/expected.hpp"
#include "../Image.hpp"

namespace gimli
{

/** \brief Loads WebP images.
 *
 * \remarks This is not implemented yet.
 */
template<typename img_t = Image>
class WebpLoader
{
  public:
    /** \brief Loads an image from the given path.
     *
     * \param path    the file path of the image to load
     * \return Returns an Image, if the image could be loaded.
     *         Returns an error message otherwise.
     */
    static nonstd::expected<img_t, std::string> load(const std::filesystem::path& path)
    {
      return nonstd::make_unexpected("Loading of WebP images is not implemented yet.");
    }
};

} // namespace

#endif // GIMLI_WEBP_LOADER_HPP
