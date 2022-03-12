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
#include "../../../lib/types/is_bitmap.hpp"

TEST_CASE("file format checks: Bitmap")
{
  using namespace gimli::types;

  SECTION("is_bitmap")
  {
    SECTION("valid Bitmap image data")
    {
      std::vector<uint8_t> data = { 0x42, 0x4D, 0x92, 0x00, 0x00, 0x00, 0x00,
          0x00, 0x00, 0x00, 0x7A, 0x00, 0x00, 0x00 };
      REQUIRE( is_bitmap(data) );
    }

    SECTION("data is too short")
    {
      std::vector<uint8_t> data = { 0x42, 0x4D };
      while (!data.empty())
      {
        data.pop_back();
        REQUIRE_FALSE( is_bitmap(data) );
      }
    }

    SECTION("data from a JPEG file is not a Bitmap image")
    {
      std::vector<uint8_t> data = { 0xFF, 0xD8, 0xFF, 0xE0, 0x00, 0x10, 0x4A,
          0x46, 0x49, 0x46, 0x00, 0x01, 0x01, 0x00, 0x00, 0x01, 0x00, 0x01 };
      REQUIRE_FALSE( is_bitmap(data) );
    }

    SECTION("data from a PNG file is not a Bitmap image")
    {
      std::vector<uint8_t> data = { 0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A,
          0x0A, 0x00, 0x00, 0x00, 0x0D, 0x49, 0x48, 0x44, 0x52, 0x00, 0x00 };
      REQUIRE_FALSE( is_bitmap(data) );
    }

    SECTION("data from a Targa image file is not a Bitmap image")
    {
      std::vector<uint8_t> data = { 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00,
          0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x06, 0xB0, 0x04, 0x18, 0x00 };
      REQUIRE_FALSE( is_bitmap(data) );
    }
  }
}
