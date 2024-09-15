cmake_minimum_required(VERSION 3.8)

project(melm_rviz_plugins)

# Default to C++17
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
  set(CMAKE_CXX_STANDARD_REQUIRED ON)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(pluginlib REQUIRED)
find_package(Qt5 REQUIRED COMPONENTS Core Gui Widgets Test Concurrent)
find_package(rclcpp REQUIRED)
find_package(rviz_common REQUIRED)
find_package(synapse_msgs REQUIRED)

set(melm_rviz_plugins_headers_to_moc
  include/melm_rviz_plugins/melm_panel.hpp
)

foreach(header "${melm_rviz_plugins_headers_to_moc}")
  qt5_wrap_cpp(melm_rviz_plugins_moc_files "${header}")
endforeach()

set(melm_rviz_plugins_source_files
  src/melm_panel.cpp
  )

add_library(melm_rviz_plugins SHARED
  ${melm_rviz_plugins_moc_files}
  ${melm_rviz_plugins_source_files}
)

ament_target_dependencies(melm_rviz_plugins synapse_msgs rviz_common Qt5)

target_include_directories(melm_rviz_plugins PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

# Causes the visibility macros to use dllexport rather than dllimport,
# which is appropriate when building the dll but not consuming it.
target_compile_definitions(melm_rviz_plugins PRIVATE "melm_RVIZ_PLUGINS_BUILDING_LIBRARY")

pluginlib_export_plugin_description_file(rviz_common plugins_description.xml)

# Export old-style CMake variables
ament_export_include_directories("include/${PROJECT_NAME}")

# Export modern CMake targets
ament_export_targets(melm_rviz_plugins HAS_LIBRARY_TARGET)

ament_export_dependencies(
  rclcpp
  rviz_common
)

install(
  TARGETS melm_rviz_plugins
  EXPORT melm_rviz_plugins
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
)

install(
  DIRECTORY include/
  DESTINATION include/${PROJECT_NAME}
)

ament_package(
  CONFIG_EXTRAS "melm_rviz_plugins-extras.cmake"
)
