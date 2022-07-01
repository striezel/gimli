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
#include "../../../lib/io/WebpLoader.hpp"

TEST_CASE("WebpLoader")
{
  using namespace gimli;

  SECTION("load")
  {
    SECTION("missing file")
    {
      const auto result = WebpLoader::load("does-not-exist.webp");
      REQUIRE_FALSE( result.has_value() );
      /*const auto& error = result.error();
      REQUIRE( error.find("failed to open") != std::string::npos );*/
    }

    /*SECTION("existing file")
    {
      using namespace std::string_view_literals;

      const auto data = "RIFF\x36\0\0\0WEBPVP8L*\0\0\0/\x01\x80\0\0\x17 \x10H\xDA\xDFy\x0E\x02\x01\x8A\xE2\xFF\x65\x08\x04(\x0A\xFF/\x9B\xFF\x30\xD6\xFB\x03\x85m\xDB\xA0\xB0\x34\x8C\xE8\x7F\xE0\x0B"sv;
      // write WebP file
      const auto name = "rgb.webp";
      {
        std::ofstream file(name, std::ios::out | std::ios::binary);
        file.write(data.data(), data.size());
        file.close();
      }

      const auto result = WebpLoader::load(name);
      REQUIRE( std::remove(name) == 0 );
      REQUIRE( result.has_value() );
      const auto& img = result.value();
      REQUIRE( img.width() == 2 );
      REQUIRE( img.height() == 3 );
    }*/

    SECTION("given file is not a WebP")
    {
      using namespace std::string_view_literals;

      const auto data = "PNG1234"sv;
      const auto name = "not-a.webp";
      // write "WebP" file
      {
        std::ofstream file(name, std::ios::out | std::ios::binary);
        file.write(data.data(), data.size());
        file.close();
      }

      const auto result = WebpLoader::load(name);
      REQUIRE( std::remove(name) == 0 );
      REQUIRE_FALSE( result.has_value() );
      /*const auto& error = result.error();
      REQUIRE( error.find("invalid") != std::string::npos );*/
    }
  }
}
