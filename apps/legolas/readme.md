# Legolas - tests whether images are identical

`legolas` is a command-line program that checks whether images are identical.
Currently Bitmap, JPEG, PNG and Targa image files are supported.

## Usage

```
legolas [OPTIONS] [FILE]

Tests whether images are identical.

options:
  -? | --help      - Shows this help message.
  -v | --version   - Shows version information.
  FILE             - Sets the file name of an image to compare.
                     This option has to occur at least two times, because one
                     needs at least two images for a comparison.
```

A possible output for three hypothetical image files `/home/user/foo.jpg`,
`/home/user/image.png`, `/home/user/picture.jpg` and `/home/user/bar.png` could be:

```
Image /home/user/image.png has different dimensions than the reference image /home/user/foo.jpg.
Image /home/user/picture.jpg is different from the reference image /home/user/foo.jpg.
Image /home/user/bar.png is identical to the reference image /home/user/foo.jpg.
```

## History of changes

A changelog is provided as [separate file](./changelog.md).

## Copyright and Licensing

Copyright 2025  Dirk Stolle

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
