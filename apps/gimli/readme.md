# gimli - general image likeness

`gimli` is a command-line program that compares images based in hashes.
Currently Bitmap, JPEG, PNG and Targa image files are supported.

## Usage

```
gimli [OPTIONS] [FILE]

Tests how much images look like each other.

options:
  -? | --help      - Shows this help message.
  -v | --version   - Shows version information.
  --hash=ALGORITHM - Sets the image hashing algorithm to ALGORITHM.
                     Allowed values for the algorithm are:
                         avg: Uses average hashing.
                         diff: Uses horizontal difference hashing.
                         minmax: Uses minimum-maximum hashing.
                         vdiff: Uses vertical difference hashing.
                     If no algorithm is set explicitly, then the program
                     behaves as if --hash=diff is specified.
  FILE             - Sets the file name of an image to compare.
                     This option has to occur at least two times, because one
                     needs at least two images for a comparison.
```

A possible output for three hypothetical image files `/home/user/foo.jpg`,
`/home/user/image.png` and `/home/user/picture.jpg` could be:

```
65.630000 % /home/user/image.png /home/user/foo.jpg
42.190000 % /home/user/image.png /home/user/picture.jpg
39.060000 % /home/user/picture.jpg /home/user/foo.jpg
```

## History of changes

A changelog is provided as [separate file](./changelog.md).

## Copyright and Licensing

Copyright 2022  Dirk Stolle

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
