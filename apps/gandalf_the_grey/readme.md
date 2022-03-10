# Gandalf the Grey - produces greyscale versions of images

`gandalf_the_grey` is a command-line program that produces greyscale versions
of images. Currently JPEG, PNG and Targa image files are supported.

## Usage

```
gandalf-the-grey [OPTIONS] [FILE]

Produces greyscale versions of images.
The original images will not be changed, greyscale versions are saved as
separate files with a file name suffix (usually '_grey').

options:
  -? | --help     - Shows this help message.
  -v | --version  - Shows version information.
  FILE            - Sets the file name of image to convert to greyscale.
                    This option can occur multiple times, if multiple files
                    need to be processed.
```

## History of changes

A changelog is provided as [separate file](./changelog.md).

## Copyright and Licensing

Copyright 2022  Dirk Stolle

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
