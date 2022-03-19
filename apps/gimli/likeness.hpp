/*
 -------------------------------------------------------------------------------
    This file is part of the Generic Image Library (gimli).
    Copyright (C) 2022  Dirk Stolle

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

#ifndef GIMLI_GIMLI_LIKENESS_HPP
#define GIMLI_GIMLI_LIKENESS_HPP

#include <cstdint>
#include <string>
#include <boost/gil/image.hpp>
#include <boost/gil/typedefs.hpp>
#include "../../third-party/nonstd/expected.hpp"

/** \brief Loads the given image and converts it to greyscale.
 *
 * \param file   path to the image file
 * \return Returns the loaded image, if operation was successful.
 *         Returns an exit code, if an error occurred.
 */
nonstd::expected<boost::gil::gray8_image_t, int> load_to_grey(const std::string& file);

struct Hashes
{
  uint64_t avg_hash = 0; /**< hash value from average hashing ("aHash") */
  uint64_t diff_hash = 0; /**< hash value from difference hashing ("dHash") */
  uint64_t vertical_diff_hash = 0; /**< hash value from vertical difference hashing ("vdHash") */
};

/** \brief Calculates both hashes (aHash and dHash) of an image.
 *
 * \param img   the image
 * \return Returns the hash values, if calculation was successful.
 *         Returns an error message, if an error occurred.
 */
nonstd::expected<Hashes, std::string> calculate_hashes(const boost::gil::gray8_image_t& img);

/** \brief Checks the given image for likeness to given hash (aHash + dHash).
 *
 * \param file   path to the image file
 * \param ref_hash  hash values of the reference file to compare with
 * \return Returns zero, if operation was successful.
 *         Returns non-zero exit code, if an error occurred.
 */
int likeness(const std::string& file, const Hashes& ref_hash);

#endif // GIMLI_GIMLI_LIKENESS_HPP
