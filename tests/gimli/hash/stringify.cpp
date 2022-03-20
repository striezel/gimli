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
#include "../../../lib/hash/stringify.hpp"

TEST_CASE("hash to string")
{
  using namespace gimli::hash;

  SECTION("stringify: u16")
  {
    REQUIRE( stringify<uint16_t>(0) == "0000" );
    REQUIRE( stringify<uint16_t>(65535) == "ffff" );
    REQUIRE( stringify<uint16_t>(0x1234) == "1234" );
    REQUIRE( stringify<uint16_t>(0xFEDC) == "fedc" );
  }

  SECTION("stringify: u32")
  {
    REQUIRE( stringify<uint32_t>(0) == "00000000" );
    REQUIRE( stringify<uint32_t>(0x01) == "00000001" );
    REQUIRE( stringify<uint32_t>(0x12345678) == "12345678" );
    REQUIRE( stringify<uint32_t>(0x9ABCDEF0) == "9abcdef0" );
    REQUIRE( stringify<uint32_t>(0xFFFF0000) == "ffff0000" );
    REQUIRE( stringify<uint32_t>(0xFFFFFFFF) == "ffffffff" );
  }

  SECTION("similarity: u64")
  {
    REQUIRE( stringify<uint64_t>(0) == "0000000000000000" );
    REQUIRE( stringify<uint64_t>(0x0123456789ABCDEF) == "0123456789abcdef" );
    REQUIRE( stringify<uint64_t>(0xFF00FF00FF00FF00) == "ff00ff00ff00ff00" );
    REQUIRE( stringify<uint64_t>(0xFFFFFFFFFFFFFFFF) == "ffffffffffffffff" );
  }
}
