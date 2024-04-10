/*
 -------------------------------------------------------------------------------
    This file is part of the Generic Image Library (gimli).
    Copyright (C) 2022, 2024  Dirk Stolle

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 -------------------------------------------------------------------------------
*/

#ifndef GIMLI_HOBBIT_HPP
#define GIMLI_HOBBIT_HPP

#include <string>
#include <boost/gil/point.hpp>
#include "../../third-party/nonstd/expected.hpp"

/** \brief Resizes the given image and saves it.
 *
 * \param file   path to the image file
 * \param new_size  new size of the image
 * \return Returns zero, if operation was successful.
 *         Returns non-zero exit code, if an error occurred.
 */
int hobbit(const std::string& file, const boost::gil::point_t& new_size);

/** \brief Parses a string into a point / dimension data.
 *
 * \param data   string containing the data in the form "123x456"
 * \return Returns a point containing the dimension, if parsing succeeds.
 *         Returns an error message otherwise.
 */
nonstd::expected<boost::gil::point_t, std::string> parse_size(const std::string& data);

/** \brief Generates a file name for the resized version of an image.
 *
 * \param file   the original file name
 * \param dims  dimensions of the image
 * \return Returns a suitable file name for the resized image.
 */
std::string sized_name(const std::string& file, const boost::gil::point_t& dims);

#endif // GIMLI_HOBBIT_HPP
