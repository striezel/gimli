/*
 -------------------------------------------------------------------------------
    This file is part of the Generic Image Library (gimli) example applications.
    Copyright (C) 2024  Dirk Stolle

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

#ifndef GIMLI_APPS_VERSIONS_HPP
#define GIMLI_APPS_VERSIONS_HPP

#include <string_view>

/** \brief Prints versions of the used libraries to the standard output.
 */
void library_versions();

/** \brief Shows license information on standard output.
 *
 * \param years   the years to show in the copyright message, e.g. "2022, 2023";
 *                defaults to "2022 - 2024" if not specified
 */
void showLicenseInformation(const std::string_view years = "2022 - 2024");

#endif // GIMLI_APPS_VERSIONS_HPP
