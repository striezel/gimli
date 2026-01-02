/*
 -------------------------------------------------------------------------------
    This file is part of the test suite for Generic Image Library (gimli).
    Copyright (C) 2022, 2026  Dirk Stolle

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

#include "../find_catch.hpp"
#include <cstdio> // for std::remove
#include <fstream>
#include <string_view>
#include "../../../lib/io/BitmapLoader.hpp"

TEST_CASE("BitmapLoader")
{
  using namespace gimli;

  SECTION("load")
  {
    SECTION("missing file")
    {
      const auto result = BitmapLoader<boost::gil::rgb8_image_t>::load("does-not-exist.bmp");
      REQUIRE_FALSE( result.has_value() );
      const auto& error = result.error();
      REQUIRE( error.find("failed to open") != std::string::npos );
    }

    SECTION("existing file")
    {
      using namespace std::string_view_literals;

      const auto data = "BM\x92\0\0\0\0\0\0\0\x7A\0\0\0\x6C\0\0\0\x02\0\0\0\x03\0\0\0\x01\0\x18\0\0\0\0\0\x18\0\0\0#.\0\0#.\0\0\0\0\0\0\0\0\0\0BGRs\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x02\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\xFF\0\0\xFF\0\0\0\0\0\xFF\0\0\xFF\0\0\0\0\0\xFF\0\0\xFF\0\0"sv;
      // write Bitmap file
      const auto name = "rgb.bmp";
      {
        std::ofstream file(name, std::ios::out | std::ios::binary);
        file.write(data.data(), data.size());
        file.close();
      }

      const auto result = BitmapLoader<boost::gil::rgb8_image_t>::load(name);
      REQUIRE( std::remove(name) == 0 );
      REQUIRE( result.has_value() );
      const auto& img = result.value();
      REQUIRE( img.width() == 2 );
      REQUIRE( img.height() == 3 );

      const auto view = boost::gil::const_view(img);
      REQUIRE( view(0, 0) == boost::gil::rgb8_pixel_t(255, 0, 0) );
      REQUIRE( view(1, 0) == boost::gil::rgb8_pixel_t(255, 0, 0) );
      REQUIRE( view(0, 1) == boost::gil::rgb8_pixel_t(0, 255, 0) );
      REQUIRE( view(1, 1) == boost::gil::rgb8_pixel_t(0, 255, 0) );
      REQUIRE( view(0, 2) == boost::gil::rgb8_pixel_t(0, 0, 255) );
      REQUIRE( view(1, 2) == boost::gil::rgb8_pixel_t(0, 0, 255) );
    }

    SECTION("JPEG file is not a Bitmap")
    {
      using namespace std::string_view_literals;

      const auto data = "\xFF\xD8\xFF\xE0\0\x10JFIF\0\x01\x01\x01\x01,\x01,\0\0\xFF\xDB\0C\0\x03\x02\x02\x03\x02\x02\x03\x03\x03\x03\x04\x03\x03\x04\x05\x08\x05\x05\x04\x04\x05\x0A\x07\x07\x06\x08\x0C\x0A\x0C\x0C\x0B\x0A\x0B\x0B\x0D\x0E\x12\x10\x0D\x0E\x11\x0E\x0B\x0B\x10\x16\x10\x11\x13\x14\x15\x15\x15\x0C\x0F\x17\x18\x16\x14\x18\x12\x14\x15\x14\xFF\xDB\0C\x01\x03\x04\x04\x05\x04\x05\x09\x05\x05\x09\x14\x0D\x0B\x0D\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\xFF\xC0\0\x11\x08\0\x03\0\x02\x03\x01\x11\0\x02\x11\x01\x03\x11\x01\xFF\xC4\0\x14\0\x01\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x08\xFF\xC4\0\x1B\x10\0\0\x07\x01\0\0\0\0\0\0\0\0\0\0\0\0\0\x04\x05\x06\x17S\x95\xD3\xFF\xC4\0\x15\x01\x01\x01\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x06\x08\xFF\xC4\0\x1D\x11\0\0\x05\x05\0\0\0\0\0\0\0\0\0\0\0\0\0\x04U\x94\xD3\x02\x05\x07\x15\x17\xFF\xDA\0\x0C\x03\x01\0\x02\x11\x03\x11\0?\0\x17\xCD\x0E\xAB\xD3\x31Iq\x16\xA7\x06\xC7\x89\xF5\x38\x33\x30\x39\xBA\xBE\xAB\x1CxjQ\xFF\xD9"sv;
      const auto name = "not-a.bmp";
      // write "Bitmap" file
      {
        std::ofstream file(name, std::ios::out | std::ios::binary);
        file.write(data.data(), data.size());
        file.close();
      }

      const auto result = BitmapLoader<boost::gil::rgb8_image_t>::load(name);
      REQUIRE( std::remove(name) == 0 );
      REQUIRE_FALSE( result.has_value() );
      const auto& error = result.error();
      REQUIRE_FALSE( error.empty() );
    }
  }
}
