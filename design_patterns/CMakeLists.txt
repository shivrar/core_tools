cmake_minimum_required(VERSION 3.8)
project(design_patterns)

# Find dependencies
find_package(ament_cmake REQUIRED)

# Specify include directories
include_directories(include)

# Create the library
add_library(${PROJECT_NAME} include/Mediator.h)
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)

# Specify include directories for the target
target_include_directories(${PROJECT_NAME}
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>)

add_executable(mediator_example src/main.cpp)

# Install the library
install(TARGETS ${PROJECT_NAME}
  EXPORT export_${PROJECT_NAME}
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin)

# Install the header files
install(DIRECTORY include/
  DESTINATION include/${PROJECT_NAME})

# Export package information
ament_export_targets(export_${PROJECT_NAME})
ament_export_dependencies(ament_cmake)

ament_package()

