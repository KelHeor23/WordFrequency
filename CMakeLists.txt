cmake_minimum_required(VERSION 3.5)

project(WordFrequency LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(WordFrequency main.cpp



    FileIO/FileIO.h FileIO/FileIO.cpp
    WordFrequency/CountingWordFrequency.h WordFrequency/CountingWordFrequency.cpp
    FileIO/FileIOError.h)

set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "freq")

include(GNUInstallDirs)
install(TARGETS WordFrequency
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
