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
#include "../../src/gimli/Image.hpp"

TEST_CASE("Image")
{
  using namespace gimli;

  SECTION("constructor")
  {
    Image img;

    REQUIRE( img.dimension().width() == 0 );
    REQUIRE( img.dimension().height() == 0 );
    REQUIRE( img.layout() == PixelLayout::RGB );
    REQUIRE( img.data() == nullptr );
  }

  SECTION("load")
  {
    // Loading is currently not implemented, so it should throw.
    REQUIRE_THROWS( Image::load("none.jpg", Format::Jpeg) );
  }
}
