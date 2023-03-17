#!/bin/sh

# Script to test executable when file is valid.
#
#  Copyright (C) 2022, 2023  Dirk Stolle
#
#  This program is free software: you can redistribute it and/or modify
#  it under the terms of the GNU Lesser General Public License as published by
#  the Free Software Foundation, either version 3 of the License, or
#  (at your option) any later version.
#
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU Lesser General Public License for more details.
#
#  You should have received a copy of the GNU Lesser General Public License
#  along with this program.  If not, see <http://www.gnu.org/licenses/>.

# 1st parameter = executable path
if [ -z "$1" ]
then
  echo "First parameter must be executable file!"
  exit 1
fi

# 2nd parameter = current directory
if [ -z "$2" ]
then
  echo "Second parameter must be current directory!"
  exit 1
fi

EXECUTABLE="$1"
"$EXECUTABLE" "$2"/rgb.jpeg
if [ $? -ne 0 ]
then
  echo "Executable did not exit with code 0."
  exit 1
fi

if [ ! -f "$2"/rgb_white.jpeg ]
then
  echo "File rgb_white.jpeg was not created!"
  exit 1
fi

rm "$2"/rgb_white.jpeg

exit 0
