# Hobbit - produces resized versions of images

`hobbit` is a command-line program that resizes images.
Currently Bitmap, JPEG, PNG and Targa image files are supported.

## Usage

```
hobbit [OPTIONS] [FILE]

Resizes images.
The original images will not be changed, resized versions are saved as
separate files with a file name suffix (usually containing the size).

options:
  -? | --help         - Shows this help message.
  -v | --version      - Shows version information.
  --size WIDTHxHEIGHT - Sets the new image size in pixels (WIDTH pixels wide
                        and HEIGHT pixels high).
  FILE                - Sets the file name of the image to resize.
                        This option can occur multiple times, if multiple files
                        need to be processed.
```

## History of changes

A changelog is provided as [separate file](./changelog.md).

## Copyright and Licensing

Copyright 2022, 2024, 2025  Dirk Stolle

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
