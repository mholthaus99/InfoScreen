/**
 * @file rss_reader.h
 * @brief Provides functions for fetching and cycling through RSS headlines.
 *
 * This header declares the RSS namespace, which contains functions to fetch RSS headlines
 * from a server, cache them, and retrieve them one at a time. Intended for use in applications
 * that display or process RSS feed headlines.
 */
#pragma once

namespace RSS {

     /**
      * @brief Fetches and caches RSS headlines from the server.
      */
     void fetch();

     /**
      * @brief Returns the next cached headline, refreshing if needed.
      * @return Pointer to the current headline string.
      */
     const char* getNextHeadline();

}  // namespace RSS
