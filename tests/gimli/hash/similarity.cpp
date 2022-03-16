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
#include "../../../lib/hash/similarity.hpp"

TEST_CASE("hash similarity")
{
  using namespace gimli::hash;

  SECTION("similarity: u16")
  {
    REQUIRE( similarity<uint16_t>(0, 0) == 1.0f );
    REQUIRE( similarity<uint16_t>(1, 1) == 1.0f );
    REQUIRE( similarity<uint16_t>(0x1234, 0x1234) == 1.0f );

    REQUIRE( similarity<uint16_t>(0b0000000011111111, 0b0000000011111100) == 0.875f );
    REQUIRE( similarity<uint16_t>(0b0000000011111111, 0b0000000011110000) == 0.75f );
    REQUIRE( similarity<uint16_t>(0b0000000011111111, 0b0000000000000000) == 0.5f );
    REQUIRE( similarity<uint16_t>(0b0000000011111111, 0b0000111100000000) == 0.25f );
    REQUIRE( similarity<uint16_t>(0b0000000011111111, 0b1111111100000000) == 0.0f );
  }

  SECTION("similarity: u32")
  {
    REQUIRE( similarity<uint32_t>(0, 0) == 1.0f );
    REQUIRE( similarity<uint32_t>(1, 1) == 1.0f );
    REQUIRE( similarity<uint32_t>(0x12345678, 0x12345678) == 1.0f );
    REQUIRE( similarity<uint32_t>(0x00000080, 0x00000000) == 0.96875f );
    REQUIRE( similarity<uint32_t>(0x00000090, 0x00000000) == 0.9375f );
    REQUIRE( similarity<uint32_t>(0x0000000F, 0x00000000) == 0.875f );
    REQUIRE( similarity<uint32_t>(0xFF000000, 0x00000000) == 0.75f );
    REQUIRE( similarity<uint32_t>(0xFFFF0000, 0x00000000) == 0.5f );
    REQUIRE( similarity<uint32_t>(0xFFFFFF00, 0x00000000) == 0.25f );
    REQUIRE( similarity<uint32_t>(0xFFFFFFFF, 0x00000000) == 0.0f );
  }

  SECTION("similarity: u64")
  {
    REQUIRE( similarity<uint64_t>(0, 0) == 1.0f );
    REQUIRE( similarity<uint64_t>(1, 1) == 1.0f );
    REQUIRE( similarity<uint64_t>(0x0123456789ABCDEF, 0x0123456789ABCDEF) == 1.0f );

    REQUIRE( similarity<uint64_t>(0b00001111, 0b00001001) == 0.96875f );
    REQUIRE( similarity<uint64_t>(0b00001111, 0b00000000) == 0.9375f );
    REQUIRE( similarity<uint64_t>(0b00001111, 0b11110000) == 0.875f );
    REQUIRE( similarity<uint64_t>(0b00000000, 0b11111111) == 0.875f );
    REQUIRE( similarity<uint64_t>(0b01010101, 0b10101010) == 0.875f );
    REQUIRE( similarity<uint64_t>(0xFFFFFFFFFFFFFFFF, 0xFF00FF00FF00FF00) == 0.5f );
    REQUIRE( similarity<uint64_t>(0xFFFFFFFFFFFFFFFF, 0x00000000FF00FF00) == 0.25f );
    REQUIRE( similarity<uint64_t>(0, 0xFFFFFFFFFFFFFFFF) == 0.0f );
  }
}
