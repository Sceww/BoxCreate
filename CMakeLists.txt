cmake_minimum_required( VERSION 3.16...4.2 FATAL_ERROR )

# PROJECT
set( APPNAME "BoxCreator" )
set( SOURCES 
    "vendor/glad/src/gl.c"
    "src/main.cpp"
)

project(${APPNAME})

# OPTIONS
set( GLFW_BUILD_WAYLAND OFF )
set( GLFW_BUILD_X11 OFF )
set( GLFW_BUILD_DOCS OFF CACHE BOOL "GFLW lib only" )
set( GLFW_INSTALL OFF CACHE BOOL "GLFW lib only" )

# EXECUTABLE
add_executable( ${APPNAME} ${SOURCES} )
target_include_directories( ${APPNAME}
    PRIVATE
        "${PROJECT_SOURCE_DIR}/include"
        "${PROJECT_SOURCE_DIR}/vendor/glad/include"
        "${PROJECT_SOURCE_DIR}/vendor/glfw/include"
)

# VENDOR
add_subdirectory( vendor/glfw )
target_link_libraries( ${APPNAME} glfw )

