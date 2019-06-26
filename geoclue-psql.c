/*
 *  geoclue-psql: listen for geoclue events and log them to PostgreSQL
 *  Copyright (C) 2019 Jason Owen <jason@jasonaowen.net>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <geoclue.h>
#include <stdio.h>

static GClueAccuracyLevel accuracy_level = GCLUE_ACCURACY_LEVEL_EXACT;

int main(int argc, char* argv[]) {
  GError *error = NULL;
  GClueSimple *client = gclue_simple_new_sync(
    "geoclue-psql",
    accuracy_level,
    NULL,
    &error
  );
  if (error) {
    fprintf(stderr, "%s\n", error->message);
    return error->code;
  }
  return 0;
}
