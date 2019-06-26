cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project("geoclue-psql")

add_executable(geoclue-psql geoclue-psql.c)

INCLUDE(FindPkgConfig)
PKG_SEARCH_MODULE(GEOCLUE REQUIRED libgeoclue-2.0)
INCLUDE_DIRECTORIES(
  ${GEOCLUE_INCLUDE_DIRS}
)
TARGET_LINK_LIBRARIES(
  ${PROJECT_NAME}
  ${GEOCLUE_LIBRARIES}
)
