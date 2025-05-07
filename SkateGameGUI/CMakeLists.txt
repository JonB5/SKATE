cmake_minimum_required(VERSION 3.16)

project(SkateGameGUI LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Qt6 libraries
find_package(Qt6 COMPONENTS Core Widgets REQUIRED)

# The executable
add_executable(SkateGameGUI
    skate_gui_standalone_qt6.cpp
)

# Link against Qt6 libraries
target_link_libraries(SkateGameGUI PRIVATE Qt6::Core Qt6::Widgets)
