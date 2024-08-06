cmake_minimum_required(VERSION 3.8)
project(design_patterns)

# Find dependencies
find_package(ament_cmake REQUIRED)

# Specify include directories
include_directories(include)

# Create the library
add_library(${PROJECT_NAME} include/Mediator.h include/Singleton.h)
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)

# Specify include directories for the target
target_include_directories(${PROJECT_NAME}
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>)

add_executable(patterns_example src/main.cpp)
target_link_libraries(patterns_example ${PROJECT_NAME})

# Install the library
install(TARGETS ${PROJECT_NAME}
  EXPORT export_${PROJECT_NAME}
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin)

# Install the header files
install(DIRECTORY include/
  DESTINATION include/${PROJECT_NAME}
)

install(TARGETS
        patterns_example
        DESTINATION lib/${PROJECT_NAME}
        )

# Export package information
ament_export_targets(export_${PROJECT_NAME})
ament_export_dependencies(ament_cmake)

ament_package()

