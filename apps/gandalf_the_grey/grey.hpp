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

#ifndef GIMLI_GANDALF_GREY_HPP
#define GIMLI_GANDALF_GREY_HPP

#include <string>

/** \brief Converts the given image to greyscale and saves it.
 *
 * \param file   path to the image file
 * \return Returns zero, if operation was successful.
 *         Returns non-zero exit code, if an error occurred.
 */
int gandalf_the_grey(const std::string& file);

/** \brief Generates a file name for the greyscale version of an image.
 *
 * \param file   the original file name
 * \return Returns a suitable file name for the grey image.
 */
std::string grey_name(const std::string& file);

#endif // GIMLI_GANDALF_GREY_HPP
