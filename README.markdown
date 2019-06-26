# geoclue-postgresql

A simple service to listen for geoclue events and log them to PostgreSQL.

## Dependencies

In order to build this program,
the GeoClue development headers must be installed.

On Debian / Ubuntu, they are in the package `libgeoclue-2-dev`:

```ShellSession
$ sudo apt install libgeoclue-2-dev
```

## Building

This project uses the [CMake](https://cmake.org/) build system.

```ShellSession
$ mkdir build
$ cd build
$ cmake ..
$ make
$ ./geoclue-psql
```

[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)
