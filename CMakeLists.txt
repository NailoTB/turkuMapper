# CMakeLists.txt

cmake_minimum_required(VERSION 3.12)

project(turkuMapper)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

set(CMAKE_PREFIX_PATH "/usr/lib/cmake/proj")

find_package(PROJ REQUIRED HINTS /usr/lib/cmake/proj)
find_package(Qt6 COMPONENTS Core Widgets REQUIRED)
qt_standard_project_setup()

include_directories(${Qt6Widgets_INCLUDE_DIRS})

set(SOURCES
src/main.cpp
src/MapMainWindow.cpp
src/MapScene.cpp
src/MapToolBar.cpp
src/MapBookmarks.cpp
include/MapMainWindow.h
include/MapScene.h
include/MapToolBar.h
include/MapBookmarks.h
)

SET(CMAKE_CXX_FLAGS "-O2")

# Add executable
add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} Qt6::Core)
target_link_libraries(${PROJECT_NAME} Qt6::Widgets)
target_link_libraries(${PROJECT_NAME} PROJ::proj)