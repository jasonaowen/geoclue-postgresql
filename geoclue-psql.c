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
#include <glib.h>
#include <libpq-fe.h>
#include <stdio.h>

static GClueAccuracyLevel accuracy_level = GCLUE_ACCURACY_LEVEL_EXACT;
static size_t max_float_str_len = 32;

gchar *timestamp_to_str(GVariant *timestamp) {
  GTimeVal time_val = {0};
  g_variant_get(timestamp, "(tt)", &time_val.tv_sec, &time_val.tv_usec);
  GDateTime *date_time = g_date_time_new_from_timeval_local(&time_val);
  return g_date_time_format(date_time, "%FT%T%z");
}

void on_location_updated(
    GClueSimple *simple,
    GParamSpec *spec,
    PGconn *connection
) {
  GClueLocation *location = gclue_simple_get_location(simple);
  char longitude[max_float_str_len];
  char latitude[max_float_str_len];
  char accuracy[max_float_str_len];
  char altitude[max_float_str_len];
  char speed[max_float_str_len];
  char heading[max_float_str_len];
  snprintf(longitude, max_float_str_len, "%f", gclue_location_get_longitude(location));
  snprintf(latitude, max_float_str_len, "%f", gclue_location_get_latitude(location));
  snprintf(accuracy, max_float_str_len, "%f", gclue_location_get_accuracy(location));
  snprintf(altitude, max_float_str_len, "%f", gclue_location_get_accuracy(location));
  snprintf(speed, max_float_str_len, "%f", gclue_location_get_speed(location));
  snprintf(heading, max_float_str_len, "%f", gclue_location_get_heading(location));
  char *timestamp = timestamp_to_str(gclue_location_get_timestamp(location));

  printf(
    "Location updated:\n  Longitude: %s\n  Latitude: %s\n  Accuracy: %s\n",
    longitude,
    latitude,
    accuracy
  );

  const char *params[8];
  params[0] = timestamp;
  params[1] = longitude;
  params[2] = latitude;
  params[3] = accuracy;
  params[4] = altitude;
  params[5] = speed;
  params[6] = heading;
  params[7] = gclue_location_get_description(location);

  PGresult *result = PQexecParams(
    connection,
    "INSERT INTO location_history( \
      \"timestamp\", longitude, latitude, accuracy, \
      altitude, speed, heading, description) \
      VALUES ($1, $2, $3, $4, $5, $6, $7, $8) \
      ON CONFLICT DO NOTHING;",
    8,
    NULL,
    params,
    NULL,
    NULL,
    0
  );

  if (PQresultStatus(result) != PGRES_COMMAND_OK) {
    fprintf(stderr, "Error inserting into database: %s", PQerrorMessage(connection));
    exit(2);
  }

  g_free(timestamp);
}

GClueSimple* connect_geoclue() {
  GError *error = NULL;
  GClueSimple *client = gclue_simple_new_sync(
    "geoclue-psql",
    accuracy_level,
    NULL,
    &error
  );
  if (error) {
    fprintf(stderr, "%s\n", error->message);
    exit(error->code);
  }

  return client;
}

PGconn* connect_postgresql() {
  char *database_url = getenv("DATABASE_URL");
  if (database_url == NULL) {
    fprintf(stderr, "Please set the DATABASE_URL environment variable.\n");
    exit(1);
  }

  PGconn *conn = PQconnectdb(database_url);
  if (PQstatus(conn) != CONNECTION_OK) {
    fprintf(stderr, "Could not connect to database: %s", PQerrorMessage(conn));
    exit(1);
  }

  return conn;
}

int main(int argc, char* argv[]) {
  GClueSimple *client = connect_geoclue();
  PGconn *connection = connect_postgresql();

  g_signal_connect(
    client,
    "notify::location",
    G_CALLBACK(on_location_updated),
    connection
  );

  GMainLoop *main_loop = g_main_loop_new(NULL, FALSE);
  g_main_loop_run(main_loop);

  return 0;
}
