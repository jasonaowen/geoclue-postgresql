CREATE TABLE IF NOT EXISTS location_history (
  "timestamp" TIMESTAMP WITH TIME ZONE PRIMARY KEY,
  longitude DECIMAL NOT NULL,
  latitude DECIMAL NOT NULL,
  accuracy DECIMAL NOT NULL,
  altitude DECIMAL NULL,
  speed DECIMAL NULL,
  heading DECIMAL NULL,
  description TEXT NULL
);
