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
#include "../../../lib/hash/factory.hpp"

TEST_CASE("Hashing: Factory methods")
{
  using namespace gimli::hash;
  using namespace boost::gil;

  SECTION("hash with rgb image")
  {
    rgb8_image_t img(point_t(8, 8));
    for (int i = 0; i < 8; ++i)
    {
      for (int j = 0; j < 8; ++j)
      {
        view(img)(j, i) = rgb8_pixel_t(0, 0, 0);
      }
    }

    SECTION("average")
    {
      const auto hash = factory::calculate(algorithm::average, img);
      REQUIRE( hash.has_value() );
      REQUIRE( hash.value() == 0 );
    }

    SECTION("difference")
    {
      const auto hash = factory::calculate(algorithm::difference, img);
      REQUIRE( hash.has_value() );
      REQUIRE( hash.value() == 0 );
    }

    SECTION("minmax")
    {
      const auto hash = factory::calculate(algorithm::minmax, img);
      REQUIRE( hash.has_value() );
      REQUIRE( hash.value() == 0 );
    }

    SECTION("vertical difference")
    {
      const auto hash = factory::calculate(algorithm::vertical_difference, img);
      REQUIRE( hash.has_value() );
      REQUIRE( hash.value() == 0 );
    }
  }

  SECTION("hash with greyscale image")
  {
    gray8_image_t img(point_t(8, 8));
    for (int i = 0; i < 8; ++i)
    {
      for (int j = 0; j < 8; ++j)
      {
        view(img)(j, i) = gray8_pixel_t(0);
      }
    }

    SECTION("average")
    {
      const auto hash = factory::calculate(algorithm::average, img);
      REQUIRE( hash.has_value() );
      REQUIRE( hash.value() == 0 );
    }

    SECTION("difference")
    {
      const auto hash = factory::calculate(algorithm::difference, img);
      REQUIRE( hash.has_value() );
      REQUIRE( hash.value() == 0 );
    }

    SECTION("minmax")
    {
      const auto hash = factory::calculate(algorithm::minmax, img);
      REQUIRE( hash.has_value() );
      REQUIRE( hash.value() == 0 );
    }

    SECTION("vertical difference")
    {
      const auto hash = factory::calculate(algorithm::vertical_difference, img);
      REQUIRE( hash.has_value() );
      REQUIRE( hash.value() == 0 );
    }
  }

  SECTION("hash with unknown / invalid algorithm value")
  {
    const algorithm algo = static_cast<algorithm>(68);

    SECTION("rgb")
    {
      rgb8_image_t img(point_t(8, 8));
      for (int i = 0; i < 8; ++i)
      {
        for (int j = 0; j < 8; ++j)
        {
          view(img)(j, i) = rgb8_pixel_t(0, 0, 0);
        }
      }

      const auto hash = factory::calculate(algo, img);
      REQUIRE_FALSE( hash.has_value() );
    }

    SECTION("grey")
    {
      gray8_image_t img(point_t(8, 8));
      for (int i = 0; i < 8; ++i)
      {
        for (int j = 0; j < 8; ++j)
        {
          view(img)(j, i) = gray8_pixel_t(0);
        }
      }

      const auto hash = factory::calculate(algo, img);
      REQUIRE_FALSE( hash.has_value() );
    }
  }
}
