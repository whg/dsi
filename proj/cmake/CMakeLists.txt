cmake_minimum_required( VERSION 3.0 FATAL_ERROR )
set( CMAKE_VERBOSE_MAKEFILE ON )

project( dsi )

get_filename_component( CINDER_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../../../../Code/Cinder" ABSOLUTE )
get_filename_component( APP_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../" ABSOLUTE )

include( "${CINDER_PATH}/proj/cmake/modules/cinderMakeApp.cmake" )

ci_make_app(
	SOURCES     ${APP_PATH}/src/dsiApp.cpp ${APP_PATH}/src/Order.cpp ${APP_PATH}/src/Order.hpp ${APP_PATH}/src/Image.cpp ${APP_PATH}/src/Image.hpp ${APP_PATH}/src/Audio.cpp ${APP_PATH}/src/Audio.hpp ${APP_PATH}/src/transform.cpp ${APP_PATH}/src/transform.hpp
	CINDER_PATH ${CINDER_PATH}
)
