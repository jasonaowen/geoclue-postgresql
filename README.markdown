# geoclue-postgresql

A simple service to listen for geoclue events and log them to PostgreSQL.

## Dependencies

In order to build this program,
the GeoClue, GLib, and libpq development headers must be installed.

On Debian / Ubuntu, they are in the packages `libgeoclue-2-dev`,
`libglib2.0-dev`, and `libpq-dev`, respectively:

```ShellSession
$ sudo apt install libgeoclue-2-dev libglib2.0-dev libpq-dev
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
```

## Database

Create a PostgreSQL database, and run `schema.sql`.

For example, on Debian/Ubuntu, to prepare a database called `geoclue`:

```ShellSession
$ sudo -u postgres createdb --owner=$(whoami) geoclue
$ psql geoclue < schema.sql
```

## Running

The application looks at the `DATABASE_URL` environment variable,
which should be a
[libpq connection string](https://www.postgresql.org/docs/current/static/libpq-connect.html#LIBPQ-CONNSTRING),
such as `postgres:///geoclue`.

Copy the `.env.template` to `.env`, edit it, and source it:

```ShellSession
$ cp .env.template .env
$ vim .env
$ source .env
```

Then, run the built program:

```ShellSession
$ ./geoclue-psql
```

[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)
