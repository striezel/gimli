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

#include "PngLoader.hpp"
#include <fstream>
#include <memory>
#include <png.h>

namespace gimli
{

bool PngLoader::supportsFormat(const Format fmt) const
{
  return fmt == Format::Png;
}

nonstd::expected<Image, std::string> PngLoader::load(const std::string_view& path, const Format format)
{
  if (format != Format::Png)
    return nonstd::make_unexpected("PngLoader only supports PNG and no other formats.");

  // Unfortunately, libpng relies on C-style FILE in its I/O, so we cannot use
  // std::ifstream from C++ directly.
  std::unique_ptr<FILE, decltype(&fclose)> file_png{fopen(path.data(), "rb"), fclose};
  if (!file_png)
  {
    return nonstd::make_unexpected(std::string("File ").append(path) + " could not be opened for reading.");
  }
  // read PNG signature
  // Eight bytes is the maximum size that can be checked by libpng.
  png_byte header[8];
  const size_t itemsRead = fread(header, 1, 8, file_png.get());
  if (png_sig_cmp(header, 0, itemsRead) != 0)
  {
    return nonstd::make_unexpected(std::string("File ").append(path) + " is not a PNG file.");
  }

  // initialize
  png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
  if (!png_ptr)
  {
    return nonstd::make_unexpected(std::string("png_create_read_struct() failed with file ").append(path) + ".");
  }

  png_infop info_ptr = png_create_info_struct(png_ptr);
  if (!info_ptr)
  {
    png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);
    return nonstd::make_unexpected(std::string("png_create_info_struct() failed with file ").append(path) + ".");
  }

  png_init_io(png_ptr, file_png.get());
  png_set_sig_bytes(png_ptr, 8);
  png_read_info(png_ptr, info_ptr);

  // get colour type and bit depth
  png_byte colour_type = png_get_color_type(png_ptr, info_ptr);
  // expansions and transformations
  // expand paletted images to RGB
  if (colour_type == PNG_COLOR_TYPE_PALETTE)
  {
    png_set_expand(png_ptr);
  }
  // expand low bit greyscale images to 8 bit
  const png_byte bit_depth = png_get_bit_depth(png_ptr, info_ptr);
  if ((colour_type == PNG_COLOR_TYPE_GRAY) && (bit_depth < 8))
  {
    png_set_expand(png_ptr);
  }
  // strip 16 bits per sample to 8 bits per sample
  if (bit_depth == 16)
  {
    png_set_strip_16(png_ptr);
  }
  // set greyscaled images to RGB(A) images
  if ((colour_type == PNG_COLOR_TYPE_GRAY) || (colour_type == PNG_COLOR_TYPE_GRAY_ALPHA))
  {
    png_set_gray_to_rgb(png_ptr);
  }

  png_read_update_info(png_ptr, info_ptr);

  // get width / height values
  const std::uint_least32_t width = png_get_image_width(png_ptr, info_ptr);
  const std::uint_least32_t height = png_get_image_height(png_ptr, info_ptr);

  // update colour type, it might have changed
  colour_type = png_get_color_type(png_ptr, info_ptr);

  PixelLayout layout;
  switch (colour_type)
  {
    case PNG_COLOR_TYPE_RGB:
         layout = PixelLayout::RGB;
         break;
    case PNG_COLOR_TYPE_RGBA:
         layout = PixelLayout::RGBA;
         break;
    default:
         png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);
         return nonstd::make_unexpected(std::string("Colour type of file  ").append(path) + " is neither RGB nor RGBA.");
  }

  // read file
  const auto row_size_in_bytes = png_get_rowbytes(png_ptr,info_ptr);

  // prepare the array for the data
  std::uint8_t* v_ptr = (std::uint8_t*) malloc(row_size_in_bytes * height * sizeof(png_byte));
  if (v_ptr == nullptr)
  {
    png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);
    return nonstd::make_unexpected("Could not allocate memory for pixel data!");
  }

  // create row pointers
  png_bytepp row_pointers = (png_bytepp) malloc(sizeof(png_bytep) * height);
  if (row_pointers == nullptr)
  {
    png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);
    free(v_ptr);
    v_ptr = nullptr;
    return nonstd::make_unexpected("Could not allocate memory for PNG row pointers!");
  }
  for (std::uint_least32_t y = 0; y < height; ++y)
  {
    row_pointers[y] = v_ptr + (height - 1 - y) * row_size_in_bytes;
  }

  png_read_image(png_ptr, row_pointers);
  file_png.reset();

  png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);
  // free row pointer array
  free(row_pointers);
  row_pointers = nullptr;
  Dimension dim;
  dim.setHeight(height);
  dim.setWidth(width);
  return Image(dim, layout, v_ptr);
}

} // namespace
