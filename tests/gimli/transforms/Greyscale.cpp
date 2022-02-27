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
#include <cstdio> // for std::remove
#include <fstream>
#include <string_view>
#include "../../../src/gimli/loaders/PngLoader.hpp"
#include "../../../src/gimli/transforms/Greyscale.hpp"

TEST_CASE("Greyscale")
{
  using namespace gimli;

  SECTION("transform")
  {
    Greyscale xform;

    SECTION("image is already greyscale")
    {
      Dimension dim;
      dim.setWidth(1);
      dim.setHeight(1);
      std::uint8_t* data = new uint8_t[1];
      data[0] = 128;
      Image source(dim, PixelLayout::Grey, data);

      auto transformed = Greyscale::transform(source);

      REQUIRE( transformed.has_value() );
      const auto& transformed_image = transformed.value();

      REQUIRE( source.dimension() == transformed_image.dimension() );
      REQUIRE( transformed_image.layout() == PixelLayout::Grey );
      // Pointer address is different.
      REQUIRE( transformed_image.data() != source.data() );
      // But content is the same.
      REQUIRE( transformed_image.data()[0] == source.data()[0] );
    }

    SECTION("transform RGB to greyscale")
    {
      using namespace std::string_view_literals;

      const auto data = "\x89PNG\x0D\x0A\x1A\x0A\0\0\0\x0D\x49\x48\x44\x52\0\0\0\x14\0\0\0\x1E\x08\x02\0\0\0\xA3p\xA9<\0\0\0\x09pHYs\0\0.#\0\0.#\x01x\xA5?v\0\0\0\x19tEXtComment\0Created with GIMPW\x81\x0E\x17\0\0\0%IDAT8\xCB\x63\xFC\xCF@>`b\x18\xD5<\xAAyT3u5320\xFC\x1F\x0D\xB0Q\xCD\xA3\x9A\x07\x8D\x66\0\x84\xF7\x02\x39v\x01\xB2\x02\0\0\0\0IEND\xAE\x42`\x82"sv;
      // write PNG file
      const auto name = "red-blue-for-greyscale.png";
      {
        std::ofstream file(name);
        file.write(data.data(), data.size());
        file.close();
      }

      PngLoader loader;
      const auto loaded = loader.load(name, Format::Png);
      REQUIRE( loaded.has_value() );
      const auto& source = loaded.value();
      REQUIRE( std::remove(name) == 0 );

      REQUIRE( source.layout() == PixelLayout::RGB );

      auto transformed = Greyscale::transform(source);
      REQUIRE( transformed.has_value() );
      const auto& transformed_image = transformed.value();

      REQUIRE( source.dimension() == transformed_image.dimension() );
      REQUIRE( transformed_image.layout() == PixelLayout::Grey );
      REQUIRE( transformed_image.data() != nullptr );

      const std::uint8_t expected_red = 0.2126 * 255;
      const std::uint8_t expected_blue = 0.0722 * 255;

      const auto grey_data = transformed_image.data();
      REQUIRE( expected_blue == grey_data[0] );
      REQUIRE( expected_red == grey_data[20*30-1] );
    }
  }
}
