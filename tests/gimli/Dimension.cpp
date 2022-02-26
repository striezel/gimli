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

#include <catch.hpp>
#include <cstring>
#include "../../src/gimli/Dimension.hpp"

TEST_CASE("Dimension")
{
  using namespace gimli;

  SECTION("constructor")
  {
    Dimension dim;

    REQUIRE( dim.width() == 0 );
    REQUIRE( dim.height() == 0 );
  }

  SECTION("width / setWidth")
  {
    Dimension dim;

    dim.setWidth(256);
    REQUIRE( dim.width() == 256 );
    REQUIRE( dim.height() == 0 );
    dim.setWidth(43210);
    REQUIRE( dim.width() == 43210 );
    REQUIRE( dim.height() == 0 );
  }

  SECTION("height / setHeight")
  {
    Dimension dim;

    dim.setHeight(2560);
    REQUIRE( dim.width() == 0 );
    REQUIRE( dim.height() == 2560 );
    dim.setHeight(43210);
    REQUIRE( dim.width() == 0 );
    REQUIRE( dim.height() == 43210 );
  }

  SECTION("equality operator")
  {
    Dimension a;
    Dimension b;

    SECTION("equal")
    {
      REQUIRE( a == b );
      REQUIRE( b == a );

      a.setWidth(12);
      a.setHeight(34);

      b.setWidth(12);
      b.setHeight(34);

      REQUIRE( a == b );
      REQUIRE( b == a );
    }

    SECTION("width does not match")
    {
      a.setWidth(12);
      REQUIRE_FALSE( a == b );
      REQUIRE_FALSE( b == a );
    }

    SECTION("height does not match")
    {
      a.setHeight(34);
      REQUIRE_FALSE( a == b );
      REQUIRE_FALSE( b == a );
    }

    SECTION("width and height do not match")
    {
      a.setWidth(567);
      a.setHeight(890);
      REQUIRE_FALSE( a == b );
      REQUIRE_FALSE( b == a );
    }
  }
}
