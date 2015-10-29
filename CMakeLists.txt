# Main cmake file 

cmake_minimum_required(VERSION 2.6)

# Set main project name
project(ogamalBreakout)

# Find packages
FIND_PACKAGE(OpenGL REQUIRED)
FIND_PACKAGE(GLUT REQUIRED)

set(CMAKE_CXX_FLAGS "-g -Wall")

# Include dirs
include_directories(${OPENGL_INCLUDE_DIR})
include_directories(${GLUT_INCLUDE_DIR})

# Add all files to the configuration
file(GLOB ogamalBreakout_SRC
    "*.h"
    "*.cpp"
)

# Create an executable
add_executable(ogamalBreakout ${ogamalBreakout_SRC})

# Add libraries
target_link_libraries(ogamalBreakout ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})
