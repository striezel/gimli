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
#include "../../../lib/io/PngLoader.hpp"

TEST_CASE("PngLoader")
{
  using namespace gimli;

  SECTION("load")
  {
    SECTION("missing file")
    {
      const auto result = PngLoader::load("does-not-exist.png");
      REQUIRE_FALSE( result.has_value() );
      const auto& error = result.error();
      REQUIRE( error.find("failed to open") != std::string::npos );
    }

    SECTION("supported format and existing file")
    {
      using namespace std::string_view_literals;

      const auto data = "\x89PNG\x0D\x0A\x1A\x0A\0\0\0\x0D\x49\x48\x44\x52\0\0\0\x14\0\0\0\x1E\x08\x02\0\0\0\xA3p\xA9<\0\0\0\x09pHYs\0\0.#\0\0.#\x01x\xA5?v\0\0\0\x19tEXtComment\0Created with GIMPW\x81\x0E\x17\0\0\0%IDAT8\xCB\x63\xFC\xCF@>`b\x18\xD5<\xAAyT3u5320\xFC\x1F\x0D\xB0Q\xCD\xA3\x9A\x07\x8D\x66\0\x84\xF7\x02\x39v\x01\xB2\x02\0\0\0\0IEND\xAE\x42`\x82"sv;
      // write PNG file
      const auto name = "red-blue.png";
      {
        std::ofstream file(name);
        file.write(data.data(), data.size());
        file.close();
      }

      const auto result = PngLoader::load(name);
      REQUIRE( std::remove(name) == 0 );
      REQUIRE( result.has_value() );
      const auto& img = result.value();
      REQUIRE( img.width() == 20 );
      REQUIRE( img.height() == 30 );
    }

    SECTION("given file is not a PNG")
    {
      using namespace std::string_view_literals;

      const auto data = "PNG1234"sv;
      const auto name = "not-a.png";
      // write PNG file
      {
        std::ofstream file(name);
        file.write(data.data(), data.size());
        file.close();
      }

      const auto result = PngLoader::load(name);
      REQUIRE( std::remove(name) == 0 );
      REQUIRE_FALSE( result.has_value() );
      const auto& error = result.error();
      REQUIRE( error.find("invalid") != std::string::npos );
    }
  }
}
