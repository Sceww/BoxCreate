cmake_minimum_required( VERSION 3.16...4.2 FATAL_ERROR )

# PROJECT
# set( APPNAME "BoxCreator" )
set( SOURCES 
    "vendor/glad/src/gl.c"
    "src/main.cpp"
    "src/class/shader.cpp"
    "src/class/shaderProgram.cpp"
)

project("BoxCreator")

# OPTIONS
set( GLFW_BUILD_DOCS OFF CACHE BOOL "GFLW lib only" )
set( GLFW_INSTALL OFF CACHE BOOL "GLFW lib only" )

# EXECUTABLE
add_executable( ${PROJECT_NAME} "src/main.cpp" )
target_sources( ${PROJECT_NAME} 
    PRIVATE
        ${SOURCES} 
)
target_include_directories( ${PROJECT_NAME}
    PRIVATE
        "${PROJECT_SOURCE_DIR}/src/include"
        "${PROJECT_SOURCE_DIR}/vendor/glad/include"
        "${PROJECT_SOURCE_DIR}/vendor/glfw/include"
        "${PROJECT_SOURCE_DIR}/vendor/glm"
)

# VENDOR
add_subdirectory( vendor/glfw )
target_link_libraries( ${PROJECT_NAME} glfw )

