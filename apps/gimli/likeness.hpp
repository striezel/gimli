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
#include <functional>
#include <string>
#include <tuple>
#include <boost/gil/image.hpp>
#include <boost/gil/typedefs.hpp>
#include "../../third-party/nonstd/expected.hpp"

using likeness_entry = std::tuple<std::string, std::string, float>;

/** \brief Loads the given image and converts it to greyscale.
 *
 * \param file   path to the image file
 * \return Returns the loaded image, if operation was successful.
 *         Returns an exit code, if an error occurred.
 */
nonstd::expected<boost::gil::gray8_image_t, int> load_to_grey(const std::string& file);

/** \brief Calculates the hash of the given image.
 *
 * \param file    path to the image file
 * \param hashes  map to which the calculates hash will be added.
 * \return Returns zero, if operation was successful.
 *         Returns non-zero exit code, if an error occurred.
 */
int calculate_hash(const std::string& file, std::unordered_map<std::string, uint64_t>& hashes);

/** \brief Sorts hashed files by similarity.
 *
 * \param hashes   the files and their hash values
 * \return Returns a vector of tuples where the first two elements of a tuple
 *         are the file names and the third element is the similarity value in
 *         the range [0;1].
 */
std::vector<likeness_entry> sort_by_similarity(const std::unordered_map<std::string, uint64_t>& hashes);

/** \brief Converts a similarity value in the range [0;1] to a percentage.
 *
 * \param similarity   similarity value
 * \return Returns a string containing the percentage.
 */
std::string to_percentage(const float similarity);

#endif // GIMLI_GIMLI_LIKENESS_HPP
