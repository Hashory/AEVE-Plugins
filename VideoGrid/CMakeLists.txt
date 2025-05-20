project("VideoGrid")

# Set the plugin specific source files
set(${PROJECT_NAME}_SOURCES
  VideoGrid.cpp
  GridSub16.cpp
  GridSub32.cpp
  GridSub8.cpp
)

# Call the common plugin build function
build_ae_plugin(${PROJECT_NAME})
