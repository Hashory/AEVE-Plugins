project("ColorMatKey")

# Set the plugin specific source files
set(${PROJECT_NAME}_SOURCES
  ColorMatKey.cpp
  ColorMatKeySub8.cpp
)

# Call the common plugin build function
build_ae_plugin(${PROJECT_NAME})
