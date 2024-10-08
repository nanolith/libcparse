cmake_minimum_required(VERSION 3.22)
cmake_policy(SET CMP0048 NEW)
PROJECT(libcparse VERSION 0.0.1)

string(REPLACE "." ";" CPARSE_VERSION_LIST "${CMAKE_PROJECT_VERSION}")
list(GET CPARSE_VERSION_LIST 0 CPARSE_VERSION_MAJOR)
list(GET CPARSE_VERSION_LIST 1 CPARSE_VERSION_MINOR)
list(GET CPARSE_VERSION_LIST 2 CPARSE_VERSION_REL)

SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules")

#minunit package
find_package(minunit REQUIRED)

#Build config.h
configure_file(config.h.cmake include/libcparse/config.h)

#includes
INCLUDE_DIRECTORIES(include)
INCLUDE_DIRECTORIES(${CMAKE_BINARY_DIR}/include)

#source files
AUX_SOURCE_DIRECTORY(src/abstract_parser LIBCPARSE_ABSTRACT_PARSER_SOURCES)
AUX_SOURCE_DIRECTORY(src/comment_filter LIBCPARSE_COMMENT_FILTER_SOURCES)
AUX_SOURCE_DIRECTORY(src/comment_scanner LIBCPARSE_COMMENT_SCANNER_SOURCES)
AUX_SOURCE_DIRECTORY(src/event LIBCPARSE_EVENT_SOURCES)
AUX_SOURCE_DIRECTORY(src/event_copy LIBCPARSE_EVENT_COPY_SOURCES)
AUX_SOURCE_DIRECTORY(src/event_handler LIBCPARSE_EVENT_HANDLER_SOURCES)
AUX_SOURCE_DIRECTORY(src/event_reactor LIBCPARSE_EVENT_REACTOR_SOURCES)
AUX_SOURCE_DIRECTORY(
    src/file_position_cache LIBCPARSE_FILE_POSITION_CACHE_SOURCES)
AUX_SOURCE_DIRECTORY(src/input_stream LIBCPARSE_INPUT_STREAM_SOURCES)
AUX_SOURCE_DIRECTORY(src/line_wrap_filter LIBCPARSE_LINE_WRAP_FILTER_SOURCES)
AUX_SOURCE_DIRECTORY(src/message LIBCPARSE_MESSAGE_SOURCES)
AUX_SOURCE_DIRECTORY(src/message_handler LIBCPARSE_MESSAGE_HANDLER_SOURCES)
AUX_SOURCE_DIRECTORY(src/message_type LIBCPARSE_MESSAGE_TYPE_SOURCES)
AUX_SOURCE_DIRECTORY(
    src/newline_preserving_whitespace_filter
    LIBCPARSE_NEWLINE_PRESERVING_WHITESPACE_FILTER_SOURCES)
AUX_SOURCE_DIRECTORY(
    src/preprocessor_control_scanner
    LIBCPARSE_PREPROCESSOR_CONTROL_SCANNER_SOURCES)
AUX_SOURCE_DIRECTORY(
    src/preprocessor_scanner LIBCPARSE_PREPROCESSOR_SCANNER_SOURCES)
AUX_SOURCE_DIRECTORY(src/preproclexer LIBCPARSE_PREPROCLEXER_SOURCES)
AUX_SOURCE_DIRECTORY(src/raw_stack_scanner LIBCPARSE_RAW_STACK_SCANNER_SOURCES)
AUX_SOURCE_DIRECTORY(
    src/raw_file_line_override_filter
    LIBCPARSE_RAW_FILE_LINE_OVERRIDE_FILTER_SOURCES)
AUX_SOURCE_DIRECTORY(src/string_builder LIBCPARSE_STRING_BUILDER_SOURCES)
AUX_SOURCE_DIRECTORY(src/string_utils LIBCPARSE_STRING_UTILS_SOURCES)

SET(LIBCPARSE_SOURCES
    ${LIBCPARSE_ABSTRACT_PARSER_SOURCES}
    ${LIBCPARSE_COMMENT_FILTER_SOURCES}
    ${LIBCPARSE_COMMENT_SCANNER_SOURCES}
    ${LIBCPARSE_EVENT_SOURCES}
    ${LIBCPARSE_EVENT_COPY_SOURCES}
    ${LIBCPARSE_EVENT_HANDLER_SOURCES}
    ${LIBCPARSE_EVENT_REACTOR_SOURCES}
    ${LIBCPARSE_FILE_POSITION_CACHE_SOURCES}
    ${LIBCPARSE_INPUT_STREAM_SOURCES}
    ${LIBCPARSE_LINE_WRAP_FILTER_SOURCES}
    ${LIBCPARSE_MESSAGE_SOURCES}
    ${LIBCPARSE_MESSAGE_HANDLER_SOURCES}
    ${LIBCPARSE_MESSAGE_TYPE_SOURCES}
    ${LIBCPARSE_NEWLINE_PRESERVING_WHITESPACE_FILTER_SOURCES}
    ${LIBCPARSE_PREPROCESSOR_CONTROL_SCANNER_SOURCES}
    ${LIBCPARSE_PREPROCESSOR_SCANNER_SOURCES}
    ${LIBCPARSE_PREPROCLEXER_SOURCES}
    ${LIBCPARSE_RAW_STACK_SCANNER_SOURCES}
    ${LIBCPARSE_RAW_FILE_LINE_OVERRIDE_FILTER_SOURCES}
    ${LIBCPARSE_STRING_BUILDER_SOURCES}
    ${LIBCPARSE_STRING_UTILS_SOURCES})

#test source files
AUX_SOURCE_DIRECTORY(
    test/abstract_parser LIBCPARSE_TEST_ABSTRACT_PARSER_SOURCES)
AUX_SOURCE_DIRECTORY(
    test/comment_filter LIBCPARSE_TEST_COMMENT_FILTER_SOURCES)
AUX_SOURCE_DIRECTORY(
    test/comment_scanner LIBCPARSE_TEST_COMMENT_SCANNER_SOURCES)
AUX_SOURCE_DIRECTORY(test/event LIBCPARSE_TEST_EVENT_SOURCES)
AUX_SOURCE_DIRECTORY(test/event_copy LIBCPARSE_TEST_EVENT_COPY_SOURCES)
AUX_SOURCE_DIRECTORY(test/event_handler LIBCPARSE_TEST_EVENT_HANDLER_SOURCES)
AUX_SOURCE_DIRECTORY(test/event_include LIBCPARSE_TEST_EVENT_INCLUDE_SOURCES)
AUX_SOURCE_DIRECTORY(
    test/event_raw_character LIBCPARSE_TEST_EVENT_RAW_CHARACTER_SOURCES)
AUX_SOURCE_DIRECTORY(
    test/event_raw_float LIBCPARSE_TEST_EVENT_RAW_FLOAT_SOURCES)
AUX_SOURCE_DIRECTORY(
    test/event_raw_integer LIBCPARSE_TEST_EVENT_RAW_INTEGER_SOURCES)
AUX_SOURCE_DIRECTORY(test/event_reactor LIBCPARSE_TEST_EVENT_REACTOR_SOURCES)
AUX_SOURCE_DIRECTORY(
    test/file_position_cache LIBCPARSE_TEST_FILE_POSITION_CACHE_SOURCES)
AUX_SOURCE_DIRECTORY(test/input_stream LIBCPARSE_TEST_INPUT_STREAM_SOURCES)
AUX_SOURCE_DIRECTORY(
    test/line_wrap_filter LIBCPARSE_TEST_LINE_WRAP_FILTER_SOURCES)
AUX_SOURCE_DIRECTORY(test/message LIBCPARSE_TEST_MESSAGE_SOURCES)
AUX_SOURCE_DIRECTORY(
    test/newline_preserving_whitespace_filter
    LIBCPARSE_TEST_NEWLINE_PRESERVING_WHITESPACE_FILTER_SOURCES)
AUX_SOURCE_DIRECTORY(
    test/message_handler LIBCPARSE_TEST_MESSAGE_HANDLER_SOURCES)
AUX_SOURCE_DIRECTORY(test/preproclexer LIBCPARSE_TEST_PREPROCLEXER_SOURCES)
AUX_SOURCE_DIRECTORY(
    test/preprocessor_scanner LIBCPARSE_TEST_PREPROCESSOR_SCANNER_SOURCES)
AUX_SOURCE_DIRECTORY(
    test/raw_stack_scanner LIBCPARSE_TEST_RAW_STACK_SCANNER_SOURCES)
AUX_SOURCE_DIRECTORY(
    test/raw_file_line_override_filter
    LIBCPARSE_TEST_RAW_FILE_LINE_OVERRIDE_FILTER_SOURCES)
AUX_SOURCE_DIRECTORY(test/string_builder LIBCPARSE_TEST_STRING_BUILDER_SOURCES)

SET(LIBCPARSE_TEST_SOURCES
    ${LIBCPARSE_TEST_ABSTRACT_PARSER_SOURCES}
    ${LIBCPARSE_TEST_COMMENT_FILTER_SOURCES}
    ${LIBCPARSE_TEST_COMMENT_SCANNER_SOURCES}
    ${LIBCPARSE_TEST_EVENT_SOURCES}
    ${LIBCPARSE_TEST_EVENT_COPY_SOURCES}
    ${LIBCPARSE_TEST_EVENT_HANDLER_SOURCES}
    ${LIBCPARSE_TEST_EVENT_INCLUDE_SOURCES}
    ${LIBCPARSE_TEST_EVENT_RAW_CHARACTER_SOURCES}
    ${LIBCPARSE_TEST_EVENT_RAW_FLOAT_SOURCES}
    ${LIBCPARSE_TEST_EVENT_RAW_INTEGER_SOURCES}
    ${LIBCPARSE_TEST_EVENT_REACTOR_SOURCES}
    ${LIBCPARSE_TEST_FILE_POSITION_CACHE_SOURCES}
    ${LIBCPARSE_TEST_INPUT_STREAM_SOURCES}
    ${LIBCPARSE_TEST_LINE_WRAP_FILTER_SOURCES}
    ${LIBCPARSE_TEST_MESSAGE_SOURCES}
    ${LIBCPARSE_TEST_MESSAGE_HANDLER_SOURCES}
    ${LIBCPARSE_TEST_NEWLINE_PRESERVING_WHITESPACE_FILTER_SOURCES}
    ${LIBCPARSE_TEST_PREPROCLEXER_SOURCES}
    ${LIBCPARSE_TEST_PREPROCESSOR_SCANNER_SOURCES}
    ${LIBCPARSE_TEST_RAW_STACK_SCANNER_SOURCES}
    ${LIBCPARSE_TEST_RAW_FILE_LINE_OVERRIDE_FILTER_SOURCES}
    ${LIBCPARSE_TEST_STRING_BUILDER_SOURCES})

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

INSTALL(FILES ${CPARSE_INCLUDES} DESTINATION include/libcparse)
INSTALL(
    FILES ${CMAKE_BINARY_DIR}/include/libcparse/config.h
    DESTINATION include/libcparse)

#Install library
INSTALL(TARGETS cparse
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)

#Examples
ADD_SUBDIRECTORY(examples)

#Tools
ADD_SUBDIRECTORY(tools)
