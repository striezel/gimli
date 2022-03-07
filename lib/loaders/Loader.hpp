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

#ifndef GIMLI_LOADER_HPP
#define GIMLI_LOADER_HPP

#include <string>
#include "../../third-party/nonstd/expected.hpp"
#include "../Image.hpp"

namespace gimli
{

/** \brief Template for loading a certain image type.
 */
template<typename tag_t>
class Loader
{
  public:
    /** \brief Loads an image from the given path.
     *
     * \param path    the file path of the image to load
     * \return Returns an Image, if the image could be loaded.
     *         Returns an error message otherwise.
     */
    nonstd::expected<Image, std::string> load(const std::string& path)
    {
      using namespace boost::gil;

      Image image;
      try
      {
        read_and_convert_image(path, image, tag_t());
      }
      catch (const std::exception& ex)
      {
        return nonstd::make_unexpected(ex.what());
      }

      return image;
    }
};

} // namespace

#endif // GIMLI_LOADER_HPP
