/*
 -------------------------------------------------------------------------------
    This file is part of the Generic Image Library (gimli).
    Copyright (C) 2022, 2024  Dirk Stolle

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

#ifndef GIMLI_WRITER_HPP
#define GIMLI_WRITER_HPP

#include <filesystem>
#include <optional>
#include <string>
#include "../Image.hpp"

namespace gimli
{

/** \brief Template for writing a certain image type.
 */
template<typename tag_t, typename image_t = Image>
class Writer
{
  public:
    /** \brief Writes an image from the given path.
     *
     * \param path    the file path of the image to write
     * \param image   the image data that shall be written
     * \return Returns an empty optional, if the image was written successfully.
     *         Returns an error message otherwise.
     */
    static std::optional<std::string> write(const std::filesystem::path& path, const image_t& image)
    {
      using namespace boost::gil;

      try
      {
        write_view(path, const_view(image), tag_t());
        return std::nullopt;
      }
      catch (const std::exception& ex)
      {
        return std::optional(ex.what());
      }
    }
};

} // namespace

#endif // GIMLI_WRITER_HPP
