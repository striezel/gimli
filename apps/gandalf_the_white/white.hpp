/*
 -------------------------------------------------------------------------------
    This file is part of the Generic Image Library (gimli).
    Copyright (C) 2023, 2024  Dirk Stolle

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

#ifndef GIMLI_GANDALF_WHITE_HPP
#define GIMLI_GANDALF_WHITE_HPP

#include <filesystem>
#include <string>
#include <boost/gil/image.hpp>
#include <boost/gil/typedefs.hpp>
#include "../../third-party/nonstd/expected.hpp"

/** \brief White-balances the given image and saves it.
 *
 * \param file   path to the image file
 * \return Returns zero, if operation was successful.
 *         Returns non-zero exit code, if an error occurred.
 */
int gandalf_the_white(const std::filesystem::path& file);

/** \brief White-balances an image.
 *
 * \param source   the source image
 * \return Returns the white-balanced image, if successful.
 *         Returns an error message otherwise.
 */
nonstd::expected<boost::gil::rgb8_image_t, std::string> white_balance(const boost::gil::rgb8_image_t& source);

/** \brief Generates a file name for the white-balanced version of an image.
 *
 * \param file   the original file name
 * \return Returns a suitable file name for the white-balanced image.
 */
std::filesystem::path white_name(std::filesystem::path file);

#endif // GIMLI_GANDALF_WHITE_HPP
