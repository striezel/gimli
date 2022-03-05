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
#include "../../../src/gimli/numeric/hamming.hpp"

TEST_CASE("Hamming distance")
{
  using namespace gimli::numeric;

  SECTION("hamming_distance")
  {
    REQUIRE( hamming_distance(0, 0) == 0 );
    REQUIRE( hamming_distance(1, 1) == 0 );
    REQUIRE( hamming_distance(0x0123456789ABCDEF, 0x0123456789ABCDEF) == 0 );

    REQUIRE( hamming_distance(0b00001111, 0b00001001) == 2 );
    REQUIRE( hamming_distance(0b00001111, 0b00000000) == 4 );
    REQUIRE( hamming_distance(0b00001111, 0b11110000) == 8 );
    REQUIRE( hamming_distance(0b00000000, 0b11111111) == 8 );
    REQUIRE( hamming_distance(0b01010101, 0b10101010) == 8 );
    REQUIRE( hamming_distance(0xFFFFFFFFFFFFFFFF, 0xFF00FF00FF00FF00) == 32 );
    REQUIRE( hamming_distance(0xFFFFFFFFFFFFFFFF, 0x00000000FF00FF00) == 48 );
    REQUIRE( hamming_distance(0, 0xFFFFFFFFFFFFFFFF) == 64 );
  }
}
