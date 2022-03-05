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
#include "../../../src/gimli/transforms/Resize.hpp"

TEST_CASE("Resize")
{
  using namespace boost::gil;
  using namespace gimli;

  SECTION("transform")
  {
    Resize xform;

    SECTION("resize RGB image")
    {
      using namespace std::string_view_literals;

      const auto data = "\x89PNG\x0D\x0A\x1A\x0A\0\0\0\x0D\x49\x48\x44\x52\0\0\0\x14\0\0\0\x1E\x08\x02\0\0\0\xA3p\xA9<\0\0\0\x09pHYs\0\0.#\0\0.#\x01x\xA5?v\0\0\0\x19tEXtComment\0Created with GIMPW\x81\x0E\x17\0\0\0%IDAT8\xCB\x63\xFC\xCF@>`b\x18\xD5<\xAAyT3u5320\xFC\x1F\x0D\xB0Q\xCD\xA3\x9A\x07\x8D\x66\0\x84\xF7\x02\x39v\x01\xB2\x02\0\0\0\0IEND\xAE\x42`\x82"sv;
      // write PNG file
      const auto name = "red-blue-for-resize-shrink.png";
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

      auto transformed = Resize::transform<rgb8_image_t>(source, point_t(10, 12));
      REQUIRE( transformed.has_value() );
      const auto& shrink_image = transformed.value();

      REQUIRE( point_t(10, 12) == shrink_image.dimensions() );

      boost::gil::write_view("/tmp/test_resized.png", const_view(shrink_image), boost::gil::png_tag());

      auto shrink_view = const_view(shrink_image);
      auto locator = shrink_view.xy_at(0, 0);
      // check first half of image (i. e. red pixels)
      for (int y = 0; y < shrink_image.height() / 2; ++y)
      {
        for (int x = 0; x < shrink_image.width(); ++x)
        {
          locator = shrink_view.xy_at(x, y);
          const auto red_value = get_color(*locator, red_t());
          // Red component is sometimes 254, although it should be 255, but the
          // difference is hardly noticeable by the human eye.
          const bool red_matches = (255 == red_value) || (254 == red_value);
          REQUIRE( red_matches );
          REQUIRE( 0 == get_color(*locator, green_t()) );
          REQUIRE( 0 == get_color(*locator, blue_t()) );
        }
      }
      // check second half of image (i. e. blue pixels)
      for (int y = shrink_image.height() / 2; y < shrink_image.height(); ++y)
      {
        for (int x = 0; x < shrink_image.width(); ++x)
        {
          locator = shrink_view.xy_at(x, y);
          REQUIRE( 0 == get_color(*locator, red_t()) );
          REQUIRE( 0 == get_color(*locator, green_t()) );
          const auto blue_value = get_color(*locator, blue_t());
          // Blue component is sometimes 254, although it should be 255, but the
          // difference is hardly noticeable by the human eye.
          const bool blue_matches = (blue_value == 255) || (blue_value == 254);
          REQUIRE( blue_matches );
        }
      }
    }

    SECTION("resize fails")
    {
      rgb8_image_t source(point_t(128, 128));
      // Use an insanely huge size to trigger allocation failure.
      const auto insane_size = point_t(100000000, 120000000);
      auto transformed = Resize::transform<rgb8_image_t>(source, insane_size);
      REQUIRE_FALSE( transformed.has_value() );
    }
  }
}
