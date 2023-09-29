cmake_minimum_required(VERSION 3.22)
cmake_policy(SET CMP0048 NEW)
PROJECT(libcparse VERSION 0.0.1)

SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules")

#minunit package
find_package(minunit REQUIRED)

#includes
INCLUDE_DIRECTORIES(include)

#source files
AUX_SOURCE_DIRECTORY(src/preproclexer LIBCPARSE_PREPROCLEXER_SOURCES)

SET(LIBCPARSE_SOURCES
    ${LIBCPARSE_PREPROCLEXER_SOURCES})

#test source files
AUX_SOURCE_DIRECTORY(test/preproclexer LIBCPARSE_TEST_PREPROCLEXER_SOURCES)

SET(LIBCPARSE_TEST_SOURCES
    ${LIBCPARSE_TEST_PREPROCLEXER_SOURCES})

ADD_LIBRARY(cparse STATIC ${LIBCPARSE_SOURCES})
TARGET_COMPILE_OPTIONS(
    cparse PRIVATE -fPIC -O2
    -Wall -Werror -Wextra -Wpedantic -Wno-unused-command-line-argument)


ADD_EXECUTABLE(testcparse
    ${LIBCPARSE_SOURCES} ${LIBCPARSE_TEST_SOURCES})

TARGET_COMPILE_OPTIONS(
    testcparse PRIVATE -g -O0 --coverage ${MINUNIT_CFLAGS}
                       -Wall -Werror -Wextra -Wpedantic
                       -Wno-unused-command-line-argument)
TARGET_LINK_LIBRARIES(testcparse PRIVATE -g -O0 --coverage ${MINUNIT_LDFLAGS})
set_source_files_properties(
    ${LIBCPARSE_TEST_SOURCES} PROPERTIES
    COMPILE_FLAGS "${STD_CXX_20}")

ADD_CUSTOM_TARGET(
    test
    COMMAND testcparse
    DEPENDS testcparse)

#Build a pkg-config file
SET(CPARSE_PC "${CMAKE_BINARY_DIR}/libcparse.pc")
FILE(WRITE  ${CPARSE_PC} "Name: libcparse")
FILE(APPEND ${CPARSE_PC} "\nDescription: C parser library")
FILE(APPEND ${CPARSE_PC} "\nVersion: ${CMAKE_PROJECT_VERSION}")
FILE(APPEND ${CPARSE_PC} "\nURL: https://github.com/nanolith/libcparse")
FILE(APPEND ${CPARSE_PC} "\nprefix=${CMAKE_INSTALL_PREFIX}")
FILE(APPEND ${CPARSE_PC} "\nlibdir=\${prefix}/lib")
FILE(APPEND ${CPARSE_PC} "\nincludedir=\${prefix}/include")
FILE(APPEND ${CPARSE_PC} "\nLibs: -L\${libdir} -lcparse")
FILE(APPEND ${CPARSE_PC} "\nCflags: -I\${includedir}")
INSTALL(FILES ${CPARSE_PC} DESTINATION lib/pkgconfig)

FILE(GLOB CPARSE_INCLUDES "${CMAKE_CURRENT_SOURCE_DIR}/include/libcparse/*.h")

INSTALL(FILES ${CPARSE_INCLUDES} DESTINATION include/rcpr)

#Install library
INSTALL(TARGETS cparse
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)
