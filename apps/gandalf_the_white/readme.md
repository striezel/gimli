# Gandalf the White - produces white-balanced versions of images

`gandalf_the_white` is a command-line program that performs white-balancing on
images. Currently Bitmap, JPEG, PNG and Targa image files are supported.

## Usage

```
gandalf-the-white [OPTIONS] [FILE]

Produces white-balanced versions of images.
The original images will not be changed, white-balanced versions are saved as
separate files with a file name suffix (usually '_white').

options:
  -? | --help     - Shows this help message.
  -v | --version  - Shows version information.
  FILE            - Sets the file name of image to be white-balanced.
                    This option can occur multiple times, if multiple files
                    need to be processed.
```

## History of changes

A changelog is provided as [separate file](./changelog.md).

## Copyright and Licensing

Copyright 2023, 2024, 2025  Dirk Stolle

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
