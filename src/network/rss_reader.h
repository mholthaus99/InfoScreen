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

} // namespace RSS
