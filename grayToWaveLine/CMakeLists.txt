project("grayToWaveLine")

# Set the plugin specific source files
set(${PROJECT_NAME}_SOURCES
  grayToWaveLine.cpp
  grayToWaveLine16.cpp
  grayToWaveLine8.cpp
)

# Call the common plugin build function
build_ae_plugin(${PROJECT_NAME})
