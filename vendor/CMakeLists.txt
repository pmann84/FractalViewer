# Cache internal here makes these variables visible in all cmake files after this has been called
set(SFML_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/SFML/include CACHE INTERNAL "")

add_subdirectory(SFML)