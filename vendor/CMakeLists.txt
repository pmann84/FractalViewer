# Cache internal here makes these variables visible in all cmake files after this has been called
set(SFML_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/SFML/include CACHE INTERNAL "")
# set(SFML_BINARY_DIR ${CMAKE_BINARY_DIR}/vendor/SFML/lib/${CMAKE_BUILD_TYPE}/ CACHE INTERNAL "")
# message( ${SFML_BINARY_DIR} )

add_subdirectory(SFML)