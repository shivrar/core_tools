cmake_minimum_required(VERSION 3.8)
project(base_classes)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

include_directories(include)

# Create the library
add_library(${PROJECT_NAME} include/base_classes/action_base.h)
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclcpp_lifecycle REQUIRED)
find_package(rclcpp_components REQUIRED)
find_package(rclcpp_action REQUIRED)
find_package(example_interfaces REQUIRED)
find_package(std_msgs REQUIRED)


# Specify include directories for the target
target_include_directories(${PROJECT_NAME}
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>)

ament_target_dependencies(${PROJECT_NAME}
        "rclcpp"
        "rclcpp_lifecycle"
        "rclcpp_action"
        "example_interfaces"
        "rclcpp_components"
        "std_msgs")

install(TARGETS
        ${PROJECT_NAME}
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin)


add_executable(my_action_server examples/action_server_example.cpp)
target_link_libraries(my_action_server ${PROJECT_NAME})

add_executable(my_action_client examples/action_client_example.cpp)
target_link_libraries(my_action_client ${PROJECT_NAME})

install(TARGETS
        my_action_server
        my_action_client
        DESTINATION lib/${PROJECT_NAME}
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
