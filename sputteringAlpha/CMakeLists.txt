project("sputteringAlpha")

# Set the plugin specific source files
set(${PROJECT_NAME}_SOURCES
  sputteringAlpha.cpp
  sputteringAlpha16.cpp
  sputteringAlpha32.cpp
  sputteringAlpha8.cpp
)

# Call the common plugin build function
build_ae_plugin(${PROJECT_NAME})
