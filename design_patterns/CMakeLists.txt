cmake_minimum_required(VERSION 3.5)
project(design_patterns)

# Default to C++14
set(CMAKE_CXX_STANDARD 14)

# Check if building within a ROS1 or ROS2 environment
if(DEFINED ENV{ROS_DISTRO})
  if("$ENV{ROS_DISTRO}" STREQUAL "noetic" OR "$ENV{ROS_DISTRO}" STREQUAL "melodic")
    # ROS 1 build
    find_package(catkin REQUIRED COMPONENTS)
    catkin_package(
      INCLUDE_DIRS include
      LIBRARIES ${PROJECT_NAME}
    )
    include_directories(${catkin_INCLUDE_DIRS})
    link_directories(${catkin_LIBRARY_DIRS})
  elseif("$ENV{ROS_DISTRO}" MATCHES "foxy|eloquent|dashing")
    # ROS 2 build
    find_package(ament_cmake REQUIRED)
    find_package(rclcpp REQUIRED)
    ament_export_include_directories(include)
    ament_export_libraries(${PROJECT_NAME})
  endif()
else()
  # Non-ROS build
  set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/install")
endif()

# Include directory
include_directories(${PROJECT_SOURCE_DIR}/include)

# Define the library
add_library(${PROJECT_NAME} include/Mediator.h)  # Assuming implementation is header-only
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)


# Define the executable
add_executable(mediator_example src/main.cpp)
target_link_libraries(mediator_example ${PROJECT_NAME})

if(DEFINED catkin_LIBRARIES)
  target_link_libraries(${PROJECT_NAME} ${catkin_LIBRARIES})
elseif(DEFINED ament_cmake)
  ament_target_dependencies(${PROJECT_NAME})
endif()

# Installation rules
install(TARGETS ${PROJECT_NAME} mediator_example
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
  ARCHIVE DESTINATION lib
  INCLUDES DESTINATION include
)

install(DIRECTORY include/
  DESTINATION include
)

# Conditional ament package call for ROS2
if(DEFINED ament_cmake)
  ament_package()
endif()

