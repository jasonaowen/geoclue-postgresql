# geoclue-postgresql

A simple service to listen for geoclue events and log them to PostgreSQL.

## Dependencies

In order to build this program,
the GeoClue and GLib development headers must be installed.

On Debian / Ubuntu, they are in the packages `libgeoclue-2-dev` and `libglib2.0-dev`:

```ShellSession
$ sudo apt install libgeoclue-2-dev libglib2.0-dev
```

## GeoClue service permission

In order for the application to have access to the GeoClue service,
you must customize and install the desktop file:

```ShellSession
$ mkdir -p ~/.local/share/applications/
$ cp geoclue-psql.desktop.template ~/.local/share/applications/geoclue-psql.desktop
```

Then, edit the file to set the full path of the executable.

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
