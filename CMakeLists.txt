cmake_minimum_required(VERSION 3.16)

project(helloworld VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

qt_standard_project_setup()

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp)

qt_add_executable(helloworld
    src/mainwindow.ui
    ${SOURCES}
)

find_package(libzippp CONFIG REQUIRED)
find_package(pugixml CONFIG REQUIRED)

target_link_libraries(helloworld PRIVATE Qt6::Widgets libzippp::libzippp pugixml::pugixml)

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    set_target_properties(helloworld PROPERTIES
        # Set to TRUE for release builds, otherwise we want debug console output
        WIN32_EXECUTABLE ON
        MACOSX_BUNDLE ON
    )
endif()

add_custom_target(run
    COMMAND helloworld
    DEPENDS helloworld
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)
