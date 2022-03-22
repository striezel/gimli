/*
 -------------------------------------------------------------------------------
    This file is part of the Generic Image Library (gimli).
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

#ifndef GIMLI_HASH_FACTORY_HPP
#define GIMLI_HASH_FACTORY_HPP

#include <cstdint>
#include <string>
#include "../../third-party/nonstd/expected.hpp"
#include "../Image.hpp"
#include "average.hpp"
#include "difference.hpp"
#include "minmax.hpp"
#include "vertical_difference.hpp"

namespace gimli::hash
{

/// Enumeration value for possible hashing algorithms.
enum class algorithm { average, difference, minmax, vertical_difference };

struct factory
{
  template<typename image_t>
  static nonstd::expected<uint64_t, std::string> calculate(const algorithm algo, const image_t& img)
  {
    switch (algo)
    {
      case algorithm::average:
           return gimli::hash::average(img);
      case algorithm::difference:
           return gimli::hash::difference(img);
      case algorithm::minmax:
           return gimli::hash::minmax(img);
      case algorithm::vertical_difference:
           return gimli::hash::vertical_difference(img);
      default:
           return nonstd::make_unexpected("Invalid hash algorithm specified for hash factory!");
    }
  }
};

} // namespace

#endif // GIMLI_HASH_FACTORY_HPP
