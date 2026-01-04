cmake_minimum_required(VERSION 3.5)
project(proxy)

# Wymagane standardy C++
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()

# Znajdź zależności ROS2
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(image_transport REQUIRED)
find_package(cv_bridge REQUIRED)
find_package(OpenCV REQUIRED)

# Dodatkowe biblioteki (jeśli potrzebne)
# find_package(geometry_msgs REQUIRED)

# Tworzenie wykonywalnych programów

# camera_proxy – nowy program do odczytu z kamery
add_executable(camera_proxy src/camera_proxy.cpp)
ament_target_dependencies(camera_proxy
  rclcpp
  sensor_msgs
  image_transport
  cv_bridge
  OpenCV
)

# Instalacja binariów
install(TARGETS
  camera_proxy
  DESTINATION lib/${PROJECT_NAME}
)

# ament package
ament_package()

