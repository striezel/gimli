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

#ifndef GIMLI_TRANSFORM_RESIZE_HPP
#define GIMLI_TRANSFORM_RESIZE_HPP

#include <boost/gil/extension/numeric/resample.hpp>
#include <boost/gil/extension/numeric/sampler.hpp>
#include "../../../third-party/nonstd/expected.hpp"

namespace gimli
{

struct Resize
{
  public:
    /** \brief Resizes an image with the help of bi-linear sampling.
     *
     * \param source   the source image
     * \param new_size the new dimensions
     * \return Returns the transformation result, if successful.
     *         Returns an error message otherwise.
     */
    template<typename image_t>
    static nonstd::expected<image_t, std::string> transform(const image_t& source, const boost::gil::point_t& new_size)
    {
      using namespace boost::gil;

      try
      {
        image_t resized(new_size);
        resize_view(const_view(source), view(resized), bilinear_sampler());
        return resized;
      }
      catch (const std::exception& ex)
      {
        return nonstd::make_unexpected(ex.what());
      }
    }
};

} // namespace

#endif // GIMLI_TRANSFORM_RESIZE_HPP
