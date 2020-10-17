cmake_minimum_required( VERSION 3.5 )

project( churn )

set( CMAKE_POSITION_INDEPENDENT_CODE ON )

list( APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/Modules )

# Make external libraries globally available.
add_subdirectory( external )

add_subdirectory( app )
