cmake_minimum_required(VERSION 3.21)


set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS " ${CMAKE_CXX_FLAGS} -static")

include(FetchContent)

set(FETCHCONTENT_UPDATES_DISCONNECTED TRUE)
FetchContent_Declare(ftxui
        GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui
        # Important: Specify a GIT_TAG XXXXX here.
        )

FetchContent_GetProperties(ftxui)
if(NOT ftxui_POPULATED)
    FetchContent_Populate(ftxui)
    add_subdirectory(${ftxui_SOURCE_DIR} ${ftxui_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

project(calendar)

add_executable(calendar
        main.cpp
        FileHandler.cpp FileHandler.h
        Month.cpp Month.h)

add_executable(tests tests.cpp
        FileHandler.cpp FileHandler.h
        Month.cpp Month.h
        doctest.h)

target_include_directories(calendar PRIVATE src)

target_link_libraries(calendar
        PRIVATE ftxui::screen
        PRIVATE ftxui::dom
        PRIVATE ftxui::component
        )
        # Important: Specify a GIT_TAG XXXXX here.