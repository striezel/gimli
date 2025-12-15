/*
 -------------------------------------------------------------------------------
    This file is part of the Generic Image Library (gimli).
    Copyright (C) 2025  Dirk Stolle

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

#ifndef GIMLI_LEGOLAS_HPP
#define GIMLI_LEGOLAS_HPP

#include <filesystem>
#include <vector>

/** \brief Compares the given images.
 *
 * \param files   vector of paths to the image files
 * \return Returns zero, if operation was successful.
 *         Returns non-zero exit code, if an error occurred.
 */
int legolas(const std::vector<std::filesystem::path>& files);

#endif // GIMLI_LEGOLAS_HPP
