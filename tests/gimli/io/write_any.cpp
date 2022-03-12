/*
 -------------------------------------------------------------------------------
    This file is part of the test suite for Generic Image Library (gimli).
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

#include "../find_catch.hpp"
#include <cstdio> // for std::remove
#include "../../../lib/io/write_any.hpp"

TEST_CASE("write_any")
{
  using namespace gimli;
  using namespace gimli::types;
  using namespace boost::gil;

  SECTION("write_any_rgb")
  {
    Image img(point_t(1, 1));
    view(img)(0, 0) = rgb8_pixel_t(255, 0, 0);

    SECTION("Bitmap format")
    {
      const auto name = "write_any_rgb.bmp";
      const auto result = write_any_rgb(name, img, ImageType::Bitmap);
      REQUIRE( std::remove(name) == 0 );
      REQUIRE_FALSE( result.has_value() );
    }

    SECTION("JPEG format")
    {
      const auto name = "write_any_rgb.jpeg";
      const auto result = write_any_rgb(name, img, ImageType::Jpeg);
      REQUIRE( std::remove(name) == 0 );
      REQUIRE_FALSE( result.has_value() );
    }

    SECTION("PNG format")
    {
      const auto name = "write_any_rgb.png";
      const auto result = write_any_rgb(name, img, ImageType::Png);
      REQUIRE( std::remove(name) == 0 );
      REQUIRE_FALSE( result.has_value() );
    }

    SECTION("Targa image format")
    {
      const auto name = "write_any_rgb.tga";
      const auto result = write_any_rgb(name, img, ImageType::Targa);
      REQUIRE( std::remove(name) == 0 );
      REQUIRE_FALSE( result.has_value() );
    }

    SECTION("unknown format")
    {
      const auto name = "write_any_rgb.unk";
      const auto result = write_any_rgb(name, img, ImageType::Unknown);
      REQUIRE_FALSE( std::remove(name) == 0 );
      // Write should fail and have an error message.
      REQUIRE( result.has_value() );
      // Error message should contain hint about unknown format.
      REQUIRE( result.value().find("unknown") != std::string::npos );
    }

    SECTION("failure to write to file")
    {
      const auto name = "/foo/bar/write_any_rgb.fail";
      const auto result = write_any_rgb(name, img, ImageType::Jpeg);
      REQUIRE_FALSE( std::remove(name) == 0 );
      // Write should fail and have an error message.
      REQUIRE( result.has_value() );
      bool contains_fail_or_error = (result.value().find("fail") != std::string::npos) || (result.value().find("error") != std::string::npos);
      REQUIRE( contains_fail_or_error );
    }
  }

  SECTION("write_any_grey")
  {
    gray8_image_t img(point_t(1, 1));
    view(img)(0, 0) = gray8_pixel_t(128);

    SECTION("Bitmap format")
    {
      const auto name = "write_any_grey.bmp";
      const auto result = write_any_grey(name, img, ImageType::Bitmap);
      REQUIRE( std::remove(name) == 0 );
      REQUIRE_FALSE( result.has_value() );
    }

    SECTION("JPEG format")
    {
      const auto name = "write_any_grey.jpeg";
      const auto result = write_any_grey(name, img, ImageType::Jpeg);
      REQUIRE( std::remove(name) == 0 );
      REQUIRE_FALSE( result.has_value() );
    }

    SECTION("PNG format")
    {
      const auto name = "write_any_grey.png";
      const auto result = write_any_grey(name, img, ImageType::Png);
      REQUIRE( std::remove(name) == 0 );
      REQUIRE_FALSE( result.has_value() );
    }

    SECTION("Targa image format")
    {
      const auto name = "write_any_grey.tga";
      const auto result = write_any_grey(name, img, ImageType::Targa);
      REQUIRE( std::remove(name) == 0 );
      REQUIRE_FALSE( result.has_value() );
    }

    SECTION("Targa image format, but with failure")
    {
      const auto name = "/foo/bar/write_any_grey_fail.tga";
      const auto result = write_any_grey(name, img, ImageType::Targa);
      REQUIRE_FALSE( std::remove(name) == 0 );
      // Write should fail and have an error message.
      REQUIRE( result.has_value() );
      bool contains_fail_or_error = (result.value().find("fail") != std::string::npos) || (result.value().find("error") != std::string::npos);
      REQUIRE( contains_fail_or_error );
    }

    SECTION("unknown format")
    {
      const auto name = "write_any_grey.unk";
      const auto result = write_any_grey(name, img, ImageType::Unknown);
      REQUIRE_FALSE( std::remove(name) == 0 );
      // Write should fail and have an error message.
      REQUIRE( result.has_value() );
      // Error message should contain hint about unknown format.
      REQUIRE( result.value().find("unknown") != std::string::npos );
    }

    SECTION("failure to write to file")
    {
      const auto name = "/foo/bar/write_any_grey.fail";
      const auto result = write_any_grey(name, img, ImageType::Jpeg);
      REQUIRE_FALSE( std::remove(name) == 0 );
      // Write should fail and have an error message.
      REQUIRE( result.has_value() );
      bool contains_fail_or_error = (result.value().find("fail") != std::string::npos) || (result.value().find("error") != std::string::npos);
      REQUIRE( contains_fail_or_error );
    }
  }
}
