cmake_minimum_required(VERSION 3.16)

project(helloworld VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets WebEngineWidgets)

qt_standard_project_setup()

qt_add_executable(helloworld
    src/mainwindow.ui
    src/main.cpp
)

target_link_libraries(helloworld PRIVATE Qt6::Widgets Qt6::WebEngineWidgets)

set_target_properties(helloworld PROPERTIES
    # Set to TRUE for release builds, FALSE for debug builds
    WIN32_EXECUTABLE ON
)

add_custom_target(run
    COMMAND helloworld
    DEPENDS helloworld
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)
