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
#include "../../../lib/gimli/loaders/PngLoader.hpp"
#include "../../../lib/gimli/transforms/Greyscale.hpp"

TEST_CASE("Greyscale")
{
  using namespace gimli;

  SECTION("transform")
  {
    SECTION("transform RGB to greyscale")
    {
      using namespace std::string_view_literals;
      using namespace boost::gil;

      const auto data = "\x89PNG\x0D\x0A\x1A\x0A\0\0\0\x0D\x49\x48\x44\x52\0\0\0\x14\0\0\0\x1E\x08\x02\0\0\0\xA3p\xA9<\0\0\0\x09pHYs\0\0.#\0\0.#\x01x\xA5?v\0\0\0\x19tEXtComment\0Created with GIMPW\x81\x0E\x17\0\0\0%IDAT8\xCB\x63\xFC\xCF@>`b\x18\xD5<\xAAyT3u5320\xFC\x1F\x0D\xB0Q\xCD\xA3\x9A\x07\x8D\x66\0\x84\xF7\x02\x39v\x01\xB2\x02\0\0\0\0IEND\xAE\x42`\x82"sv;
      // write PNG file
      const auto name = "red-blue-for-greyscale.png";
      {
        std::ofstream file(name);
        file.write(data.data(), data.size());
        file.close();
      }

      PngLoader loader;
      const auto loaded = loader.load(name);
      REQUIRE( loaded.has_value() );
      const auto& source = loaded.value();
      REQUIRE( std::remove(name) == 0 );

      auto transformed = Greyscale::transform(source);
      REQUIRE( transformed.has_value() );
      const auto& grey_image = transformed.value();

      REQUIRE( source.dimensions() == grey_image.dimensions() );

      const gray8_pixel_t expected_red(76); // ca. 30 %
      const gray8_pixel_t expected_blue(28); // ca. 11 %

      auto grey_view = const_view(grey_image);
      auto locator = grey_view.xy_at(0, 0);
      // check first half of image (i. e. formerly red pixels)
      for (int y = 0; y < source.height() / 2; ++y)
      {
        for (int x = 0; x < source.width(); ++x)
        {
          locator = grey_view.xy_at(x, y);
          REQUIRE( expected_red == *locator );
        }
      }
      // check second half of image (i. e. formerly blue pixels)
      for (int y = source.height() / 2; y < source.height(); ++y)
      {
        for (int x = 0; x < source.width(); ++x)
        {
          locator = grey_view.xy_at(x, y);
          REQUIRE( expected_blue == *locator );
        }
      }
    }
  }
}
