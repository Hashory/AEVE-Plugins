project("ScreenShakeDir")

# Set the plugin specific source files
set(${PROJECT_NAME}_SOURCES
  ScreenShakeDir.cpp
)

# Call the common plugin build function
build_ae_plugin(${PROJECT_NAME})
