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
#include "../../../lib/hash/minmax.hpp"

TEST_CASE("Hashing: mHash")
{
  using namespace gimli::hash;
  using namespace boost::gil;

  SECTION("hash::minmax")
  {
    SECTION("all zeroes")
    {
      rgb8_image_t img(point_t(8, 8));
      for (int i = 0; i < 8; ++i)
      {
        for (int j = 0; j < 8; ++j)
        {
          view(img)(j, i) = rgb8_pixel_t(0, 0, 0);
        }
      }

      const auto mHash = minmax(img);
      REQUIRE( mHash.has_value() );
      REQUIRE( mHash.value() == 0 );
    }

    SECTION("all ones")
    {
      rgb8_image_t img(point_t(8, 8));
      for (int i = 0; i < 8; ++i)
      {
        for (int j = 0; j < 8; ++j)
        {
          view(img)(j, i) = rgb8_pixel_t(255, 255, 255);
        }
      }

      const auto mHash = minmax(img);
      REQUIRE( mHash.has_value() );
      REQUIRE( mHash.value() == 0xFFFFFFFFFFFFFFFF );
    }

    SECTION("mixed")
    {
      rgb8_image_t img(point_t(8, 8));
      for (int i = 0; i < 8; ++i)
      {
        for (int j = 0; j < 8; ++j)
        {
          if (i % 2 == 0)
            view(img)(j, i) = rgb8_pixel_t(255, 255, 255);
          else
            view(img)(j, i) = rgb8_pixel_t(0, 0, 0);
        }
      }

      const auto mHash = minmax(img);
      REQUIRE( mHash.has_value() );
      REQUIRE( mHash.value() == 0x00FF00FF00FF00FF );
    }

    SECTION("ascending")
    {
      rgb8_image_t img(point_t(8, 8));
      uint8_t current_value = 0;
      for (int i = 0; i < 8; ++i)
      {
        for (int j = 0; j < 8; ++j)
        {
            view(img)(j, i) = rgb8_pixel_t(current_value, current_value, current_value);
            ++current_value;
        }
      }

      const auto mHash = minmax(img);
      REQUIRE( mHash.has_value() );
      REQUIRE( mHash.value() == 0x0000000000000000 );
    }

    SECTION("descending")
    {
      rgb8_image_t img(point_t(8, 8));
      uint8_t current_value = 255;
      for (int i = 0; i < 8; ++i)
      {
        for (int j = 0; j < 8; ++j)
        {
            view(img)(j, i) = rgb8_pixel_t(current_value, current_value, current_value);
            --current_value;
        }
      }

      const auto mHash = minmax(img);
      REQUIRE( mHash.has_value() );
      REQUIRE( mHash.value() == 0xFFFFFFFFFFFFFFFF );
    }
  }
}
