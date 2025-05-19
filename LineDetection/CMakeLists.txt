project("LineDetection")

# Set the plugin specific source files
set(${PROJECT_NAME}_SOURCES
  LineDetect16.cpp
  LineDetect32.cpp
  LineDetect8.cpp
  LineDetection.cpp
)

# Call the common plugin build function
build_ae_plugin(${PROJECT_NAME})
