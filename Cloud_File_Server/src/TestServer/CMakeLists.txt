CMAKE_MINIMUM_REQUIRED(VERSION 3.2)
project(TestServer)
aux_source_directory(./src SOURCES)

add_executable(TestServer ${SOURCES})