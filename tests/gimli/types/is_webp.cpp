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
#include "../../../lib/types/is_webp.hpp"

TEST_CASE("file format checks: WebP")
{
  using namespace gimli::types;

  SECTION("is_webp")
  {
    SECTION("valid data")
    {
      std::vector<uint8_t> data = { 0x52, 0x49, 0x46, 0x46, 0x36, 0x00, 0x00,
                                    0x00, 0x57, 0x45, 0x42, 0x50, 0x56, 0x50,
                                    0x38, 0x4C };
      REQUIRE( is_webp(data) );

      data = { 0x52, 0x49, 0x46, 0x46, 0x36, 0, 0, 0, 0x57, 0x45, 0x42, 0x50 };
      REQUIRE( is_webp(data) );

      data = { 0x52, 0x49, 0x46, 0x46, 0xEE, 0x07, 0x06, 0x00, 0x57, 0x45, 0x42, 0x50, 0x56, 0x50, 0x38, 0x20 };
      REQUIRE( is_webp(data) );
    }

    SECTION("data is too short")
    {
      std::vector<uint8_t> data = { 0x52, 0x49, 0x46, 0x46, 0x36, 0x00, 0x00,
                                    0x00, 0x57, 0x45, 0x42, 0x50 };
      while (!data.empty())
      {
        data.pop_back();
        REQUIRE_FALSE( is_webp(data) );
      }
    }

    SECTION("data from a Bitmap file is not a WebP")
    {
      std::vector<uint8_t> data = { 0x42, 0x4D, 0x92, 0x00, 0x00, 0x00, 0x00,
          0x00, 0x00, 0x00, 0x7A, 0x00, 0x00, 0x00 };
      REQUIRE_FALSE( is_webp(data) );
    }

    SECTION("data from a JPEG file is not a WebP")
    {
      std::vector<uint8_t> data = { 0xFF, 0xD8, 0xFF, 0xE0, 0x00, 0x10, 0x4A,
          0x46, 0x49, 0x46, 0x00, 0x01, 0x01, 0x00, 0x00, 0x01 };
      REQUIRE_FALSE( is_webp(data) );
    }

    SECTION("data from Targa image file is not a WebP")
    {
      std::vector<uint8_t> data = { 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00,
          0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x06, 0xB0, 0x04, 0x18, 0x00 };
      REQUIRE_FALSE( is_webp(data) );
    }
  }
}
