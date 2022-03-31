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

#include <cstdio> // for std::remove
#include <fstream>
#include <sstream>
#include <string_view>
#include "../find_catch.hpp"
#include "../../../lib/types/get_type.hpp"

TEST_CASE("image type detection")
{
  using namespace gimli::types;

  SECTION("stream operator for ImageType")
  {
    SECTION("Bitmap")
    {
      std::ostringstream stream;
      stream << ImageType::Bitmap;
      REQUIRE( stream.str() == "Bitmap" );
    }

    SECTION("Jpeg")
    {
      std::ostringstream stream;
      stream << ImageType::Jpeg;
      REQUIRE( stream.str() == "JPEG" );
    }

    SECTION("Png")
    {
      std::ostringstream stream;
      stream << ImageType::Png;
      REQUIRE( stream.str() == "PNG" );
    }

    SECTION("Targa")
    {
      std::ostringstream stream;
      stream << ImageType::Targa;
      REQUIRE( stream.str() == "Targa image" );
    }

    SECTION("WebP")
    {
      std::ostringstream stream;
      stream << ImageType::WebP;
      REQUIRE( stream.str() == "WebP" );
    }

    SECTION("Unknown")
    {
      std::ostringstream stream;
      stream << ImageType::Unknown;
      REQUIRE( stream.str() == "unknown" );
    }
  }

  SECTION("get_type with data vector")
  {
    SECTION("Bitmap")
    {
      std::vector<uint8_t> data = { 0x42, 0x4D, 0x92, 0x00, 0x00, 0x00, 0x00,
          0x00, 0x00, 0x00, 0x7A, 0x00, 0x00, 0x00 };
      REQUIRE( get_type(data) == ImageType::Bitmap );
    }

    SECTION("JPEG")
    {
      std::vector<uint8_t> data = { 0xFF, 0xD8, 0xFF, 0xE0, 0x00, 0x10, 0x4A, 0x46, 0x49, 0x46 };
      REQUIRE( get_type(data) == ImageType::Jpeg );
    }

    SECTION("PNG")
    {
      std::vector<uint8_t> data = { 0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A, 0x00 };
      REQUIRE( get_type(data) == ImageType::Png );
    }

    SECTION("Targa image")
    {
      std::vector<uint8_t> data = { 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00,
          0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x06, 0xB0, 0x04, 0x18, 0x00 };
      REQUIRE( get_type(data) == ImageType::Targa );
    }

    SECTION("WebP image")
    {
      std::vector<uint8_t> data = { 0x52, 0x49, 0x46, 0x46, 0x36, 0x00, 0x00,
                                    0x00, 0x57, 0x45, 0x42, 0x50 };
      REQUIRE( get_type(data) == ImageType::WebP );
    }

    SECTION("unknown format")
    {
      std::vector<uint8_t> data = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H' };
      REQUIRE( get_type(data) == ImageType::Unknown );
    }
  }

  SECTION("get_type from a file path")
  {
    using namespace std::string_view_literals;

    SECTION("file does not exist")
    {
      const auto img_type = get_type("does-not-exist.jpeg");
      REQUIRE_FALSE( img_type.has_value() );
    }

    SECTION("file is too short")
    {
      const auto data = "PNG1234"sv;
      const auto name = "not-a-valid.jpeg";
      // write "image" file
      {
        std::ofstream file(name);
        file.write(data.data(), data.size());
        file.close();
      }

      const auto img_type = get_type(name);
      REQUIRE( std::remove(name) == 0 );
      REQUIRE_FALSE( img_type.has_value() );
      const auto& error = img_type.error();
      REQUIRE( error.find("short") != std::string::npos );
    }

    SECTION("Bitmap file")
    {
      const auto data = "BM\x92\0\0\0\0\0\0\0\x7A\0\0\0\x6C\0\0\0\x02\0\0\0\x03\0\0\0\x01\0\x18\0\0\0\0\0\x18\0\0\0#.\0\0#.\0\0\0\0\0\0\0\0\0\0BGRs\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x02\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\xFF\0\0\xFF\0\0\0\0\0\xFF\0\0\xFF\0\0\0\0\0\xFF\0\0\xFF\0\0"sv;
      const auto name = "get_type.bmp";
      // write file
      {
        std::ofstream file(name);
        file.write(data.data(), data.size());
        file.close();
      }

      const auto img_type = get_type(name);
      REQUIRE( std::remove(name) == 0 );
      REQUIRE( img_type.has_value() );
      REQUIRE( img_type.value() == ImageType::Bitmap );
    }

    SECTION("JPEG file")
    {
      const auto data = "\xFF\xD8\xFF\xE0\0\x10JFIF\0\x01\x01\x01\x01,\x01,\0\0\xFF\xDB\0C\0\x03\x02\x02\x03\x02\x02\x03\x03\x03\x03\x04\x03\x03\x04\x05\x08\x05\x05\x04\x04\x05\x0A\x07\x07\x06\x08\x0C\x0A\x0C\x0C\x0B\x0A\x0B\x0B\x0D\x0E\x12\x10\x0D\x0E\x11\x0E\x0B\x0B\x10\x16\x10\x11\x13\x14\x15\x15\x15\x0C\x0F\x17\x18\x16\x14\x18\x12\x14\x15\x14\xFF\xDB\0C\x01\x03\x04\x04\x05\x04\x05\x09\x05\x05\x09\x14\x0D\x0B\x0D\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\xFF\xC0\0\x11\x08\0\x03\0\x02\x03\x01\x11\0\x02\x11\x01\x03\x11\x01\xFF\xC4\0\x14\0\x01\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x08\xFF\xC4\0\x1B\x10\0\0\x07\x01\0\0\0\0\0\0\0\0\0\0\0\0\0\x04\x05\x06\x17S\x95\xD3\xFF\xC4\0\x15\x01\x01\x01\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x06\x08\xFF\xC4\0\x1D\x11\0\0\x05\x05\0\0\0\0\0\0\0\0\0\0\0\0\0\x04U\x94\xD3\x02\x05\x07\x15\x17\xFF\xDA\0\x0C\x03\x01\0\x02\x11\x03\x11\0?\0\x17\xCD\x0E\xAB\xD3\x31Iq\x16\xA7\x06\xC7\x89\xF5\x38\x33\x30\x39\xBA\xBE\xAB\x1CxjQ\xFF\xD9"sv;
      const auto name = "get_type.jpeg";
      // write file
      {
        std::ofstream file(name);
        file.write(data.data(), data.size());
        file.close();
      }

      const auto img_type = get_type(name);
      REQUIRE( std::remove(name) == 0 );
      REQUIRE( img_type.has_value() );
      REQUIRE( img_type.value() == ImageType::Jpeg );
    }

    SECTION("PNG file")
    {
      const auto data = "\x89PNG\x0D\x0A\x1A\x0A\0\0\0\x0D\x49\x48\x44\x52\0\0\0\x14\0\0\0\x1E\x08\x02\0\0\0\xA3p\xA9<\0\0\0\x09pHYs\0\0.#\0\0.#\x01x\xA5?v\0\0\0\x19tEXtComment\0Created with GIMPW\x81\x0E\x17\0\0\0%IDAT8\xCB\x63\xFC\xCF@>`b\x18\xD5<\xAAyT3u5320\xFC\x1F\x0D\xB0Q\xCD\xA3\x9A\x07\x8D\x66\0\x84\xF7\x02\x39v\x01\xB2\x02\0\0\0\0IEND\xAE\x42`\x82"sv;
      const auto name = "get_type.png";
      // write file
      {
        std::ofstream file(name);
        file.write(data.data(), data.size());
        file.close();
      }

      const auto img_type = get_type(name);
      REQUIRE( std::remove(name) == 0 );
      REQUIRE( img_type.has_value() );
      REQUIRE( img_type.value() == ImageType::Png );
    }

    SECTION("Targa image file")
    {
      const auto data = "\0\0\x0A\0\0\0\0\0\0\0\0\0\x02\0\x03\0\x18\0\x81\xFF\x01\x01\x81\x03\xFF\0\x81\0\0\xFE\0\0\0\0\0\0\0\0TRUEVISION-XFILE.\0"sv;
      const auto name = "get_type.tga";
      // write file
      {
        std::ofstream file(name);
        file.write(data.data(), data.size());
        file.close();
      }

      const auto img_type = get_type(name);
      REQUIRE( std::remove(name) == 0 );
      REQUIRE( img_type.has_value() );
      REQUIRE( img_type.value() == ImageType::Targa );
    }

    SECTION("WebP image file")
    {
      const auto data = "RIFF\x36\0\0\0WEBPVP8L*\0\0\0/\x01\x80\0\0\x17 \x10H\xDA\xDFy\x0E\x02\x01\x8A\xE2\xFF\x65\x08\x04(\x0A\xFF/\x9B\xFF\x30\xD6\xFB\x03\x85m\xDB\xA0\xB0\x34\x8C\xE8\x7F\xE0\x0B"sv;
      const auto name = "get_type.webp";
      // write file
      {
        std::ofstream file(name);
        file.write(data.data(), data.size());
        file.close();
      }

      const auto img_type = get_type(name);
      REQUIRE( std::remove(name) == 0 );
      REQUIRE( img_type.has_value() );
      REQUIRE( img_type.value() == ImageType::WebP );
    }

    SECTION("unknown format")
    {
      const auto data = "ABCDEFGHIJKLMNOPQRSTUVWXYZ\0Something something alphabet.\0"sv;
      const auto name = "get_type.unk";
      // write file
      {
        std::ofstream file(name);
        file.write(data.data(), data.size());
        file.close();
      }

      const auto img_type = get_type(name);
      REQUIRE( std::remove(name) == 0 );
      REQUIRE( img_type.has_value() );
      REQUIRE( img_type.value() == ImageType::Unknown );
    }
  }
}
