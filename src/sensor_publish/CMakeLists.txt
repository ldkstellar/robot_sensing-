cmake_minimum_required(VERSION 3.8)
project(sensor_publish)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(sensor_interface REQUIRED)
find_package(std_srvs REQUIRED)

add_executable(leftTalker src/left_sensor_publish.cpp)
ament_target_dependencies(leftTalker rclcpp sensor_interface)

add_executable(rightTalker src/right_sensor_publish.cpp)
ament_target_dependencies(rightTalker rclcpp sensor_interface)

add_executable(subscriber src/sensor_subscriber.cpp)
ament_target_dependencies(subscriber rclcpp sensor_interface std_srvs)

add_executable(client src/sensor_client.cpp)
ament_target_dependencies(client rclcpp std_srvs)


install(TARGETS
  leftTalker
  rightTalker
  subscriber
  client
  DESTINATION lib/${PROJECT_NAME})
# uncomment the following section in order to fill in
# further dependencies manually.
# find_package(<dependency> REQUIRED)



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
