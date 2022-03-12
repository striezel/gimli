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

#ifndef GIMLI_BITMAP_WRITER_HPP
#define GIMLI_BITMAP_WRITER_HPP

#include <boost/gil/extension/io/bmp.hpp>
#include "Writer.hpp"

namespace gimli
{

/** \brief Writes Bitmap (*.bmp) images.
 */
using BitmapWriter = Writer<boost::gil::bmp_tag>;
class BitmapWriterGrey
{
  public:
    /** \brief Writes an image to the given path.
     *
     * \param path    the file path of the image to write
     * \param image   the image data that shall be written
     * \return Returns an empty optional, if the image was written successfully.
     *         Returns an error message otherwise.
     */
    static std::optional<std::string> write(const std::string& path, const boost::gil::gray8_image_t& image)
    {
      using namespace boost::gil;

      try
      {
        // Boost GIL's Bitmap write implementation only supports rgb8 and rgba8,
        // so we have to convert the data from gray8 to rgb8.
        rgb8_image_t image_rgb(image.dimensions());

        const auto img_view = const_view(image);
        const auto rgb_view = view(image_rgb);
        for (unsigned int y = 0; y < image.height(); ++y)
        {
          for (unsigned int x = 0; x < image.width(); ++x)
          {
            const uint8_t grey = img_view(x, y);
            get_color(rgb_view(x, y), red_t()) = grey;
            get_color(rgb_view(x, y), green_t()) = grey;
            get_color(rgb_view(x, y), blue_t()) = grey;
          }
        }

        write_view(path, const_view(image_rgb), boost::gil::bmp_tag());
        return std::nullopt;
      }
      catch (const std::exception& ex)
      {
        return std::optional(ex.what());
      }
    }
};

} // namespace

#endif // GIMLI_BITMAP_WRITER_HPP
