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

#include "../../../gimli/find_catch.hpp"
#include "../../../../apps/hobbit/hobbit.hpp"

TEST_CASE("parse_size")
{
  SECTION("no separator or wrong separator")
  {
    auto result = parse_size("123,456");
    REQUIRE_FALSE( result.has_value() );

    result = parse_size("123x");
    REQUIRE_FALSE( result.has_value() );

    result = parse_size("x456");
    REQUIRE_FALSE( result.has_value() );
  }

  SECTION("extra characters after width")
  {
    const auto result = parse_size("123 foo x456");
    REQUIRE_FALSE( result.has_value() );
    const auto error = result.error();
    REQUIRE( error.find("width is not a valid integer") != std::string::npos );
  }

  SECTION("extra characters after height")
  {
    const auto result = parse_size("123x456 bar");
    REQUIRE_FALSE( result.has_value() );
    const auto error = result.error();
    REQUIRE( error.find("height is not a valid integer") != std::string::npos );
  }

  SECTION("value out of range")
  {
    const auto result = parse_size("1844674407370955161500x456");
    REQUIRE_FALSE( result.has_value() );
    const auto error = result.error();
    REQUIRE( error.find("out of range") != std::string::npos );
  }

  SECTION("not a valid integer")
  {
    const auto result = parse_size("blaxblubb");
    REQUIRE_FALSE( result.has_value() );
    const auto error = result.error();
    REQUIRE( error.find("invalid") != std::string::npos );
  }

  SECTION("width is zero or negative")
  {
    auto result = parse_size("-5x123");
    REQUIRE_FALSE( result.has_value() );
    auto error = result.error();
    REQUIRE( error.find("positive integers only") != std::string::npos );

    result = parse_size("0x123");
    REQUIRE_FALSE( result.has_value() );
    error = result.error();
    REQUIRE( error.find("positive integers only") != std::string::npos );
  }

  SECTION("height is zero or negative")
  {
    auto result = parse_size("123x0");
    REQUIRE_FALSE( result.has_value() );
    auto error = result.error();
    REQUIRE( error.find("positive integers only") != std::string::npos );

    result = parse_size("123x-1");
    REQUIRE_FALSE( result.has_value() );
    error = result.error();
    REQUIRE( error.find("positive integers only") != std::string::npos );
  }

  SECTION("valid dimensions")
  {
    const auto result = parse_size("987x6543");
    REQUIRE( result.has_value() );
    const auto point = result.value();
    REQUIRE( point.x == 987 );
    REQUIRE( point.y == 6543 );
  }
}
