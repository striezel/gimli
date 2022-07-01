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
#include <cstdio> // for std::remove
#include <fstream>
#include <string_view>
#include "../../../lib/io/TargaLoader.hpp"

TEST_CASE("TargaLoader")
{
  using namespace gimli;

  SECTION("load")
  {
    SECTION("missing file")
    {
      const auto result = TargaLoader::load("does-not-exist.tga");
      REQUIRE_FALSE( result.has_value() );
      const auto& error = result.error();
      REQUIRE( error.find("failed to open") != std::string::npos );
    }

    SECTION("existing file")
    {
      using namespace std::string_view_literals;

      const auto data = "\0\0\x0A\0\0\0\0\0\0\0\0\0\x02\0\x03\0\x18\0\x81\xFF\x01\x01\x81\x03\xFF\0\x81\0\0\xFE\0\0\0\0\0\0\0\0TRUEVISION-XFILE.\0"sv;
      // write Targa file
      const auto name = "rgb.tga";
      {
        std::ofstream file(name, std::ios::out | std::ios::binary);
        file.write(data.data(), data.size());
        file.close();
      }

      const auto result = TargaLoader::load(name);
      REQUIRE( std::remove(name) == 0 );
      REQUIRE( result.has_value() );
      const auto& img = result.value();
      REQUIRE( img.width() == 2 );
      REQUIRE( img.height() == 3 );
    }

    /*SECTION("given file is not a Targa image")
    {
      using namespace std::string_view_literals;

      const auto data = "PNG1234"sv;
      const auto name = "not-a.tga";
      // write "Targa" file
      {
        std::ofstream file(name, std::ios::out | std::ios::binary);
        file.write(data.data(), data.size());
        file.close();
      }

      const auto result = TargaLoader::load(name);
      REQUIRE( std::remove(name) == 0 );
      REQUIRE_FALSE( result.has_value() );
      const auto& error = result.error();
      REQUIRE( error.find("invalid") != std::string::npos );
    }*/
  }
}
