cmake_minimum_required(VERSION 3.8)
project(simple_relay)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(ament_cmake_python REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclpy REQUIRED)
find_package(std_msgs REQUIRED)

# Find Python packages
ament_python_install_package(${PROJECT_NAME})

install(PROGRAMS simple_relay/nodes/py_subscriber.py DESTINATION lib/${PROJECT_NAME})

# Install CPP files and modules
add_executable(cpp_publisher src/cpp_publisher.cpp)

ament_target_dependencies(
  cpp_publisher 
  rclcpp 
  std_msgs
)

install(TARGETS cpp_publisher DESTINATION lib/${PROJECT_NAME})

add_executable(intermediate_node src/intermediate.cpp)

ament_target_dependencies(
  intermediate_node
  rclcpp
  std_msgs
)

install(TARGETS intermediate_node DESTINATION lib/${PROJECT_NAME})

# Install launch files
install(DIRECTORY launch DESTINATION share/${PROJECT_NAME})

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