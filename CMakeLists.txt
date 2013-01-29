CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(terra)

# Find source files
FILE(GLOB_RECURSE TERRA_HEADERS include/*.h)
FILE(GLOB_RECURSE TERRA_SOURCES src/*.cpp)

# Find dependencies
FIND_PACKAGE(PugiXML REQUIRED)

# Enforce dependencies
IF(NOT PugiXML_FOUND)
	MESSAGE(FATAL_ERROR "libpugixml required (pugixml.googlecode.com)")
ENDIF()

# Set libraries and include paths
SET(LIBS ${PugiXML_LIBRARY})
SET(INCLUDE ${PROJECT_SOURCE_DIR}/include ${PugiXML_INCLUDE_DIR})

SET(LIBRARY_OUTPUT_PATH lib/)
SET(EXECUTABLE_OUTPUT_PATH bin/)

# Define executable
ADD_LIBRARY(terra STATIC ${TERRA_SOURCES})
INCLUDE_DIRECTORIES(${INCLUDE})
TARGET_LINK_LIBRARIES(terra ${LIBS})
