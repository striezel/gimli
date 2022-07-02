# Building for Windows with MSYS2

Currently, gimli does not support native Windows builds with Microsoft Visual
Studio. However, it can be built on Windows systems with
[MSYS2](https://www.msys2.org/). MSYS2 provides some typical GNU / Linux tools
on Windows operating systems. Those can be used to build gimli.

## Prerequisites

### MSYS2

First, download the MSYS2 installer from <https://www.msys2.org/#installation>
and run it. After that is done, open "MSYS2 MinGW x64" from the start menu. This
will open a command prompt window. All following steps are done there.

If you haven't done it yet, update any existing base packages by typing

```bash
pacman -Syu
```

into the prompt, then press enter.

### Build tools

To build the gimli from source you need a C++ compiler, CMake, the Ninja build
system, the Boost libraries, the libjpeg library and the libpng library.
pkg-config is required to make it easier to find compiler options for the
installed libraries. Additionally, the program uses Catch (C++ Automated Test
Cases in Headers) to perform some tests.

It also helps to have Git, a distributed version control system, on your build
system to get the latest source code directly from the Git repository.

All of that can usually be installed be typing

```bash
pacman -S git mingw-w64-x86_64-boost mingw-w64-x86_64-catch mingw-w64-x86_64-cmake mingw-w64-x86_64-gcc mingw-w64-x86_64-libjpeg-turbo mingw-w64-x86_64-libpng mingw-w64-x86_64-ninja mingw-w64-x86_64-pkg-config
```

into the MSYS2 command prompt.

### Getting the source code

Get the source directly from Git by cloning the Git repository and change to
the directory after the repository is completely cloned:

```bash
git clone https://gitlab.com/striezel/gimli.git
cd gimli
```

That's it, you should now have the current source code on your machine.

### Build process

The build process is relatively easy, because CMake does all the preparations.
Starting in the root directory of the source, you can do the following steps:

```bash
mkdir build
cd build
cmake ../
cmake --build . --parallel
```

It may take a while to build.

The executables of the example applications will be located at
`apps/gandalf_the_grey/gandalf-the-grey.exe`, `apps/gimli/gimli.exe` and
`apps/hobbit/hobbit.exe` inside the `build` directory.
